# Problem 1

## Description 

Write a shell script that "Access GATT services from BLE Device" using 
bluetoothctl commands.


### Acceptance Criteria 

- The script must connect to a BLE device and show all its available services
- The script must then be able to read a service from the device.
- The script must then be able to write values to a service.

### For example:

Lets say
#### Given that there is a BLE device in range and paired
#### When the shell script `./script show gatt` is run the script should print all the available GATT services on the device.

### Reference links
1. Accessing GATT services - https://docs.ubuntu.com/core/en/stacks/bluetooth/bluez/docs/reference/gatt-services
2. Script which Pairs and sends files using Bluetooth - [link to the script](/extras/bluetooth.sh)