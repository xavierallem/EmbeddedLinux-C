## @file <file_name>.sh
 #  @brief Bluetooth Tool 
 #  
 #  Connecting to a bluetooth device in linux using shell
 #  
 #  @author Allen Xavier
 #  @bug None 
 #

#
 ######################################################################
 #  Initialization block
 #  ---------------------
 #  This block contains initialization code for this particular file.
 #  It typically contains Includes, constants or global variables used
 #  throughout the file.
 ######################################################################
 #

#!/bin/bash

#
 ######################################################################
 #  Process block
 #  -------------
 #  Solve all your problems here 
 ######################################################################
 #

## 
 #  @brief Description on function_1
 #  
 # the function_1 block will scan the devices and take input and connect 
 # to the respected device
 #

function_1
{   # Display message
    echo "-----------------"
    echo "Bluetooth Tool Starting"
    echo "-----------------"
    # scan your bluetooth device and get MAC Address
    hcitool dev
    echo "Enter the device from which you want to scan "
    # input
    read $name 
    # get the target device
    hcitool -i $name scan
    echo "Enter the MAC Address pf the device you want to conenct "
    # input
    read $device
    # Connect 
    bluetoothctl
    trust $device
    connect $device
    

        
	
}




#
 ######################################################################
 #  Main callback
 #  -------------
 #  All your function callbacks and shell commands go below
 ######################################################################
 #
# Welcome messgage
echo "Welcome Press 1 to start"
# input
read $cond
# conitions
if [cond=='1' ]
then
# true
  function_1
else
# false
  echo "Wrong input"
fi
# Make sure you comment every line #