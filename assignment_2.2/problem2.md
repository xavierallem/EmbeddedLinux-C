# Problem 2

### Goal : Remote Configuration of Wifi and Ethernet in Linux on an Embedded device

### Architecture of communication

![arch](/extras/arch.png)


### Description

Write an MQTT Client that Subscribes to one topic "config/ble" and when commands are received on these MQTT topics it communicates with devices over bluetooth.


- [Paho MQTT Client installation Document](/extras/Documentation_for_installing_paho_mqtt_c.md)
- [MQTT Client example code](/extras/MQTTPub-Sub.c)

#### Commands being received

| Command | Description | Example |
|--------------------------------------|-------------------------------------------------------------|-------------------------------------------------|
| bluetooth on | Turn on Bluetooth | bluetooth on |
| bluetooth off | Turns off Bluetooth | bluetooth off |
| bluetooth pair MAC_address | Pairs the device given the MAC_address of the device | bluetooth pair ac:d1:b8:cb:56:93 |
| bluetooth send file_path MAC_address | Sends the file to the bluetooth device with the mac_address | bluetooth send /home/file.txt ac:d1:b8:cb:56:93 |
| bluetooth show gatt-services | Shows all the available GATT services of the BLE device | bluetooth show gatt-services |
| bluetooth read gatt/service/ | Reads from the GATT services of the BLE device | bluetooth read gatt/service1/ |
| bluetooth write gatt/service/ value | Writes a value to the GATT service | bluetooth write gatt/service2/ 40 |


- You can use either C or CPP for the code whichever you feel comfortable. 

- We already have a script for  
    - Turning Bluetooth on and off
    - Paring Bluetooth devices
    - Send file using Bluetooth
[link to the script](/extras/bluetooth.sh) please run commands in the script for pairing and sending files

- For script on 
    - Access GATT services from BLE, use your own script that you have written 
    in assignment 2.1 Problem 2.

### For Example: 

Lets say 

#### Given (Input)
the MQTT Client subscribed to topic "config/ble" receives message/command
`bluetooth pair ac:d1:b8:cb:56:93` 

#### Then (output)
the client should run shell commands on the device 
to pair the bluetooth to the `ac:d1:b8:cb:56:93` device.

Similarly for all the commands above tables.

### Acceptance Criteria 
This is the criteria to accept the assignment.
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Each action like Pairing or Sending file etc must be made into individual 
functions
- All functions must be properly documented with Doxygen.

#### Note: Please do not hard code variables such as MAC_address or File path in your code.