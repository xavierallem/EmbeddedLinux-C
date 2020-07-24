# Problem 2

### Goal : Write code to parse a JSON configuration file and configure Wifi and Ethernet parameters in Linux.


### Output
Ouptut should be a code which 
- Parses the given JSON file
- Configure Ethernet and Wifi according to the parameters given in the JSON file

### Inputs (Reading Materials for the Task)

- For parsing the JSON file use the [RapidJSON library](examples/RapidJson.md).

- For configuration of Wifi & Ethernet, Please use the documentation below
    - Wifi configuration using wpa_supplicant - https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md
    - Ethernet configuration - https://raspberrypi.stackexchange.com/a/74428

- For configuration of hostname and timezone, Please use the documentation below
    - Change Hostname - https://www.tecmint.com/set-hostname-permanently-in-linux/
    - Change Timezone - https://linuxize.com/post/how-to-set-or-change-timezone-in-linux/


- Example JSON file
```json
{
  "wireless": {
    "device": "wlan0",
    "status": "on",
    "ssid": "Hegde-Jio",
    "password": "secretpassword"
  },
  "ethernet": [
      {
        "device": "eth0",
        "status": "on",
        "allocation": "static",
        "ipAddress": "192.168.0.100",
        "subnetMask": "255.255.255.0",
        "routerAddress": "192.168.0.1"
      },
      {
        "device": "eth1",
        "status": "on",
        "allocation": "dhcp",
        "ipAddress": null,
        "subnetMask": null,
        "routerAddress": null
      },
  ],
  "hostname": "raspberrypi",
  "timezone": "Pacific/Kolkata"

}
```

#### Explanation of the JSON file 

1. The "status" property for Wifi and ethernet can be use to turn on/off the 
Wifi or ethernet.
2. For Ethernet `allocation` property is used for setting "dhcp" or "static"
In case of "dhcp" the ethernet is configured in dhcp mode and in case of static
the ethernet is configured in static mode.


### Acceptance Criteria
These are the criteria for accepting the assignment.

- You can use either C or CPP for the code whichever you feel comfortable.
- You need to use the RapidJSON library for parsing JSON file. 
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the given Coding Standards.
- Code **Must** handle all the errors for the system calls that it is using.


#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.