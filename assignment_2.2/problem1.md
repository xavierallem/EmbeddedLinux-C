# Problem 1

### Goal : Remote Configuration of Wifi and Ethernet in Linux on an Embedded device

### Architecture of communication

![arch](/extras/arch.png)


### Description

Write an MQTT Client that Subscribes to 2 different topics "config/wifi" & "config/eth"
and configures Wifi and Ethernet when commands are received on these MQTT topics.

- [Paho MQTT Client installation Document](/extras/Documentation_for_installing_paho_mqtt_c.md)
- [MQTT Client example code](/extras/MQTTPub-Sub.c)

#### Commands being received on these Topics

- For Wifi

| Command | Description | Example |
|----------------------------|----------------------------------------|---------------------------------------|
| wifi on | Turns on wifi | wifi on |
| wifi off | Turns off wifi | wifi off |
| wifi connect ssid password | Connects to Wifi given SSID & password | wifi connect Jio-wifi secret-password |

- For Ethernet

| Command | Description | Example |
|---------------------------------------------------------|-------------------------------------------|-------------------------------------------------------------------|
| ethernet on | Turns on ethernet | ethernet on |
| ethernet off | Turns off ethernet | ethernet off |
| ethernet connect dhcp | Connect to Internet via DHCP address | ethernet connect dhcp |
| ethernet connect static static_ip subnet_mask router_ip | Connect to internet via Static IP address | ethernet connect static 192.168.0.100 255.255.255.254 192.168.0.1 |


- You can use either C or CPP for the code whichever you feel comfortable. 

- For configuration of Wifi & Ethernet, Please use the documentation below
    - Wifi configuration using wpa_supplicant - https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md
    - Ethernet configuration - https://raspberrypi.stackexchange.com/a/74428

- MQTT Client Publishes back to the same topic the Success or the Error of the 
  wifi or ethernet configuration.


### For Example: 

Lets say 
#### Given (Input)
the MQTT Client subscribed to topic "config/wifi" receives message/command
`wifi connect jio-wifi password` 
#### Then (output)
the client should configure the wifi on the device 
to connect to the jio-wifi AP with the password.

Similarly for all the commands above tables.

### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.