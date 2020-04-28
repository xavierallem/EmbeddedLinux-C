#!/bin/bash

#****************************************************************************
#* @file         bluetooth.sh
#* @author       Nishant Poorswani
#* @brief        A script which simplifies the bluetooth usage on devices
#		 supported by ShunyaOS.   
#*         
#@verbatim
#-----------------------------------------------------------------------------
                        ## Function Description ## 
#-----------------------------------------------------------------------------
# run_root() - This function checks if the script is run with root permissions
# do_enable() - This function is actually responsible to turn on the BT. Board
#		specific initialiazation is done here.
# check_bt_status() - Used to check if BT is turned on or not
# connect_bt_interface() - This function gives the devices available for pairing
#			   using a TUI and actually pairs to the selected device	
# 
# connect_bt_interface_cli() - This function pairs the device with the mac_id mentioned
#				by the user
 
# ready_system() - This function is used to prepare the system to transfer the files.
#		   It starts the obex daemon.
# transfer_file() - This function transfer the file to the mac_id selected by the user
#		    using TUI	

# transfer_file_cli() - This function is responsible for transfering the file to the 
#			device whose mac_id is mentioned by the user
#-----------------------------------------------------------------------------

#This function checks if the command is run with sudo. If not it terminates the program.
run_root()
{
# Exit the code if user doesn't run with root permissionss
	if [[ "$EUID" -ne 0 ]]
		then echo "Please run as root"
		exit
	fi
}
#This function turns on bluetooth. Need to add more boards here.
do_enable()
{
#Use board specific commands to turn on and activate the bluetooth
	if [[ $1 == 'NanoPi-M4' ]]; then
		rfkill unblock all
		/usr/bin/hciattach /dev/ttyS0 bcm43xx 115200 > /dev/null
# For Rock960 use hciattach to initialize bluetooth
	elif [[ $1 == 'ROCK960-C' ]] || [[ $1 == 'ROCK960-AB' ]]; then
		rfkill unblock all
		hciattach /dev/ttyS0 bcm43xx > /dev/null
        else 
		rfkill unblock all
	fi
}
#This function is used to check if bluetooth is enable by checking hciconfig
check_bt_status()
{
# Check hciconfig for status of BT. If it is enable, one can see UP
	if [[ $(hciconfig -a | grep UP) ]]; then
		echo "Bluetooth is enabled"
		exit
	fi
}
#This function is used to pair using tui. It gives the user a choice for available bluetooth devices.
function connect_bt_interface ()
{
# Scan for available pairable devices. Code is partly borrowed from https://github.com/armbian/config/blob/167e0dc2d81a2327c05740c5abfc6fa1fd99f9d9/debian-config-functions-network(line 698 onwards)
		IFS=$'\r\n'
		GLOBIGNORE='*'
		whiptail --title "Please wait" --msgbox "Discovering Bluetooth devices ... " 0 0
		BT_INTERFACES=($(hcitool scan | sed '1d'))

		local LIST=()
		for i in "${BT_INTERFACES[@]}"
		do
			local a=$(echo ${i[0]//[[:blank:]]/} | sed -e 's/^\(.\{17\}\).*/\1/')
			local b=${i[0]//$a/}
			local b=$(echo $b | sed -e 's/^[ \t]*//')
# Store all the available BT devices in the LIST(Array)
			LIST+=( "$a" "$b")
		done
# Find no of available devices
		LIST_LENGHT=$((${#LIST[@]}/2));
# If List is empty display No bluetooth devices were found. 
		if [ "$LIST_LENGHT" -eq 0 ]; then
			BT_ADAPTER=${WLAN_INTERFACES[0]}
			whiptail --title "Bluetooth" --msgbox "No nearby Bluetooth devices were found!" 0 0
# Display available device for user to select
		else
			exec 3>&1
			BT_ADAPTER=$(whiptail --title "Select interface" \
			--menu "" $((6+${LIST_LENGHT})) 0 0 "${LIST[@]}" 2>&1 1>&3)
			exec 3>&-
			if [[ $BT_ADAPTER != "" ]]; then
				whiptail --title "Please wait" --msgbox "Connecting to $BT_ADAPTER " 0 0
#BT_EXEC holds the entire output of the command below. The command below spawns an bluetoothctl shell and then pairs to the device you selected.
				BT_EXEC=$(
				expect -c 'set prompt "#";set address '$BT_ADAPTER';spawn bluetoothctl;expect -re $prompt;send "disconnect $address\r";
				sleep 1;send "remove $address\r";sleep 1;expect -re $prompt;send "scan on\r";sleep 8;send "scan off\r";
				expect "Controller";send "trust $address\r";sleep 2;send "pair $address\r";sleep 10;send "yes\r";
				send_user "\nShould be paired now.\r";sleep 10;send "quit\r";expect eof')
				echo "$BT_EXEC" > /tmp/bt-connect-debug.log
#Display status of pairing to the user
					if [[ $(echo "$BT_EXEC" | grep "Paired: yes" ) != "" ]]; then
						whiptail --title "Bluetooth" --msgbox "Your device is ready to use!" 0 0
					else
						whiptail --title "Bluetooth" --msgbox "Error connecting. Try again!" 0 0
					fi
			fi
		fi

}
# This function is responsible for pairing to the device whose mac_id is given by the user
function connect_bt_interface_cli ()
{
	echo "Scanning for the device you entered. Please be patient!"
#Scan to check if the mac id entered by user is available
	if [[ $( hcitool scan | grep $1 ) ]]; then
		echo "" 			
		echo "Pairing with your device. Be prepared to click ok on the phone if you are trying to pair to it"	

#BT_EXEC holds the entire output of the command below. The command below spawns an bluetoothctl shell and then pairs to the device you gave through the cli.
				BT_EXEC=$(
				expect -c 'set prompt "#";set address '$1';spawn bluetoothctl;expect -re $prompt;send "disconnect $address\r";
				sleep 1;send "remove $address\r";sleep 1;expect -re $prompt;send "scan on\r";sleep 8;send "scan off\r";
				expect "Controller";send "trust $address\r";sleep 2;send "pair $address\r";sleep 10;send "yes\r";
				send_user "\nShould be paired now.\r";sleep 10;send "quit\r";expect eof')
				echo "$BT_EXEC" > /tmp/bt-connect-debug.log
#Display status of pairing to the user
					if [[ $(echo "$BT_EXEC" | grep "Paired: yes" ) != "" ]]; then
						echo "Your device is ready to use!"
					else
						echo "Error connecting. Try again!"
					fi
	else
		echo "Device with MAC-ID you entered was not found"
	fi
}
#This function is used to prepare the system to transfer the files. It starts the obex daemon.
ready_system()
{
	#Checks if obexd is running. 
	if [[ $( ps -e | grep obexd ) ]]; then
# Obtain the PID of the old obexd
		pids=$( ps -e | grep obexd | awk '{print $1}' )
# Kills the old obexd using the pid obtained
		kill $pids
	fi	 
# Start a fresh obexd
	sudo systemctl --global enable obex
	/usr/libexec/bluetooth/obexd &
}
#This function is used to send a file to a device whose mac_id is selected by the user using a tui. It gives the user a choice for available bluetooth devices.
transfer_file()
{
# Scan for available devices. Code is partly borrowed from https://github.com/armbian/config/blob/167e0dc2d81a2327c05740c5abfc6fa1fd99f9d9/debian-config-functions-network(line 698 onwards)
		IFS=$'\r\n'
		GLOBIGNORE='*'
		whiptail --title "Please wait" --msgbox "Discovering Bluetooth devices ... " 0 0
		BT_INTERFACES=($(hcitool scan | sed '1d'))
#BT_INTERFACES contains the list of all nearby devices
		local LIST=()
		for i in "${BT_INTERFACES[@]}"
		do
			local a=$(echo ${i[0]//[[:blank:]]/} | sed -e 's/^\(.\{17\}\).*/\1/')
			local b=${i[0]//$a/}
			local b=$(echo $b | sed -e 's/^[ \t]*//')
			LIST+=( "$a" "$b")
		done
#LIST_LENGTH contains the number of nearby devices
		LIST_LENGHT=$((${#LIST[@]}/2));
#If LIST_LENGTH is 0 display no nearby devices. If list length is non-zero display the list nearby devices for user to choose.
		if [ "$LIST_LENGHT" -eq 0 ]; then
			BT_ADAPTER=${WLAN_INTERFACES[0]}
			whiptail --title "Bluetooth" --msgbox "No nearby Bluetooth devices were found!" 0 0
		else
			exec 3>&1
			BT_ADAPTER=$(whiptail --title "Select interface" \
			--menu "" $((6+${LIST_LENGHT})) 0 0 "${LIST[@]}" 2>&1 1>&3)
			exec 3>&-
			if [[ $BT_ADAPTER != "" ]]; then
				whiptail --title "Please wait" --msgbox "Connecting to $BT_ADAPTER " 0 0
#BT_EXEC holds the entire output of the command below. The command below spawns an obexctl shell and then connects to the device you selected and then transfers the file.
				BT_EXEC=$(
				expect -c 'set prompt "#";set address '$BT_ADAPTER';set name '$1';set time '$2';spawn sudo obexctl;sleep 5;expect -re $prompt;send "connect $address\r";sleep 8;expect -re $prompt;send "send $name\r";sleep $time;expect -re "Status: complete";send "quit\r";expect eof')	
				echo "$BT_EXEC" > /tmp/bt-file-transfer.log
#Display status of file transfer to the user
				if [[ $(echo "$BT_EXEC" | grep "complete" ) != "" ]]; then
						whiptail --title "Bluetooth" --msgbox "Your file is successfully sent!" 0 0
					else
						whiptail --title "Bluetooth" --msgbox "Error while sending the file. Try again!" 0 0
					fi
			fi
		fi


}
# This function is actually responsible for transfer the file to the mac_id mentioned by the user in the commandline arguments
transfer_file_cli()
{
	echo "Scanning for the device you entered. Please be patient!"
	#Scan to check if the mac id entered by user is available
	if [[ $( hcitool scan | grep $2 ) ]]; then
		echo "" 			
		echo "Sending the file to your device"	
#BT_EXEC holds the entire output of the command below. The command below spawns an obexctl shell and then connects to the device you gave using cli  and then transfers the file.
				BT_EXEC=$(
				expect -c 'set prompt "#";set address '$2';set name '$1';set time '$3';spawn sudo obexctl;sleep 5;expect -re $prompt;send "connect $address\r";sleep 8;expect -re $prompt;send "send $name\r";sleep $time;expect -re "Status: complete";send "quit\r";expect eof')	
				echo "$BT_EXEC" > /tmp/bt-file-transfer.log
#Display status of file transfer to the user on cli
			if [[ $(echo "$BT_EXEC" | grep "complete" ) != "" ]]; then
				echo "Your file is successfully sent!"
			else
				echo "Error while sending the file. Try again!"
			fi
	else
		echo "Device with MAC-ID you entered was not found"
	fi
}

# First check if user has run with root permissions
run_root
#Checks if user wants to turn on bluetooth
if [[ $1 == on ]]; then
	check_bt_status
# The command for activating each bt on each board is different. Hence, by looking at the board name in config.scfg, we use the appropriate command
	BOARD=$( cat /shunya/config.scfg | grep BOARD | cut -d ':' -f 2 )
	do_enable ${BOARD}
	hciconfig hci0 up
	check_bt_status
elif [[ $1 == pair ]]; then
#Check if user wants to use tui or cli
	if [[ "$#" -eq 2 ]]; then
		connect_bt_interface_cli $2
	elif [[ "$#" -eq 1 ]]; then
		connect_bt_interface
	else
		echo "Invalid number of arguments"
	fi
elif [[ $1 == send ]]; then
# Ready the system for transferring the file by starting the obex daemon
	ready_system
#Check if user wants to use tui or cli
	if [[ -f $2 ]]; then
# Get size of the file user wants to transmit
		size=$( wc -c $2 | awk '{print $1}' )
# Convert the size the user wants to transmit to MB
		sizemb=$((size / 1000))
# If Size of file is less than equal to 30Mb, default timeout of the spawned shell will be 10 secs. Average transfer speed is about 10 Mbps.
		if [[ $sizemb -le 30 ]]; then
			time=10
# If size is above 30Mb, time = (size_in_mb)/(Average transfer rate) + 10 secs(buffer time)
		else
			transfer=$((sizemb / 10))
			time=$((transfer + 10))
		fi
#For cli we pass both the filename(i.e $2) and mac_id(i.e $3)
		if [[ "$#" -eq 3 ]]; then
			transfer_file_cli $2 $3 $time
		elif [[ "$#" -eq 2 ]]; then
#For tui we pass only the filename(i.e with path)
			transfer_file $2 $time
		else
			echo "Invalid number of arguments"
		fi
	else
		echo "File not found"
		exit
	fi
#Checks if user wants to turn off bluetooth
elif [[ $1 == off ]]; then
	hciconfig hci0 down
	if [[ $(hciconfig -a | grep DOWN) ]]; then
		echo "Bluetooth is disabled"
		exit
	fi
#Checks if user wants help and provides a help page
elif [[ $1 == '-h' ]] || [[ $1 == '--help' ]]; then
	echo ""
	echo "Usage: sudo bluetooth flag_name parameter .."
	echo ""
	echo "on					To turn on bluetooth"
	echo "pair					To pair using tui"
	echo "pair mac_id_of_device_to_pair		To pair using cli & known mac id"
	echo "send filepath				To send a file using tui"
	echo "send filepath mac_id_of_device_to_send	To send a file using cli to a mac id"
	echo "off 					To turn off bluetooth"
else
	echo "For help please use sudo bluetooth --help or sudo bluetooth -h"
fi
