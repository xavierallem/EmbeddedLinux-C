# Problem 2

### Goal : Write code to parse a JSON configuration file and configure hostname and timezone  parameters in Linux.


### Output
Ouptut should be a code which 
- Parses the given JSON file
- Configure hostname and timezone according to the parameters given in the JSON file

### Inputs (Reading Materials for the Task)

- For parsing the JSON file use the [RapidJSON library](examples/RapidJson.md).

- For configuration of hostname and timezone, Please use the documentation below
    - Change Hostname - https://www.tecmint.com/set-hostname-permanently-in-linux/
    - Change Timezone - https://linuxize.com/post/how-to-set-or-change-timezone-in-linux/

- Example JSON file
```json
{
  "hostname": "raspberrypi",
  "timezone": "Pacific/Kolkata"
}
```


### Acceptance Criteria
These are the criteria for accepting the assignment.

- You can use either C or CPP for the code whichever you feel comfortable.
- You need to use the RapidJSON library for parsing JSON file. 
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the given Coding Standards.


#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.