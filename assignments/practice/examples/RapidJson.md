# RapidJSON 

This document explains the use of RapidJSON library for parsing and writing 
purposes. This document explains the DOM style of the library (because it is the easiest).


**Note**: This document is bare minimum document for parsing and writing a 
decent JSON document, for more depth checkout the [original document](https://rapidjson.org/index.html)

1. [JSON Parser](#json-parser)
2. [JSON Writer](#json-writer)


## JSON Parser

1. Want to parse a json document you only need these lines of code 

```cpp
/* 1. Parse a JSON string into DOM. */

/* Open the example.json file in read mode */
FILE* fp = fopen("example.json", "rb"); 

/* Declare read buffer */
char readBuffer[65536];

/* Declare stream for reading the example stream */
FileReadStream is(fp, readBuffer, sizeof(readBuffer));

/* Declare a JSON document. JSON document parsed will be stored in this variable */
Document d;

/* Parse example.json and store it in `d` */
d.ParseStream(is);

/* Close the example.json file*/
fclose(fp);
```

2. Read the values inside the example.json file 

For example.json contains
```json
{
  "wireless": {
    "status": "on",
    "ssid": "Hegde-Jio",
    "password": "secretpassword"
  },
  "ethernet": {
    "status": "on",
    "allocation": "dhcp",
    "ipAddress": "192.168.0.100",
    "subnetMask": "255.255.255.0",
    "routerAddress": "192.168.0.1"
  },
  "cloud": [
        {
            "provider": "AWS",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 8886,
            "certLocation": "/home/yogesh/.aws/"
        },
        {
            "provider": "Google",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 9096,
            "certLocation": "/home/yogesh/.gcp/"
        }
    ]
}
```

3. To read the `ethernet` `status` value by this snippet   


```cpp
/* Declare an object to store the value 
 * and assign the document "ethernet" "status" value to eStatus
 */
Value& eStatus = d["ethernet"]["status"];

/* Print the string value */
std::cout << eStatus.GetString() << std::endl;

/* Modify the string value */
eStatus.SetString("off");
```

4. To read the `cloud` `provider` value in the example.json you can use this snippet


```cpp
/* Declare an object to store the value 
 * and assign the document "cloud" "provider" value to amazon
 * Since the "cloud" object is an Array object in JSON 
 * at 0 it contains "AWS" and at 1 it contains "Google" 
 */
Value& amazon = d["cloud"][0]["provider"];

/* Print the string value */
std::cout << amazon.GetString() << std::endl;

Value& google = d["cloud"][1]["provider"];

/* Print the string value */
std::cout << google.GetString() << std::endl;
```

5. To read the `cloud` `port` value for AWS in the example.json you can use this snippet


```cpp
/* Declare an object to store the value 
 * and assign the document "cloud" "provider" value to amazon
 * Since the "cloud" object is an Array object in JSON 
 * at 0 it contains "AWS" and at 1 it contains "Google" 
 */
Value& amazonPort = d["cloud"][0]["port"];

/* Print the Integer value */
std::cout << amazonPort.GetInt() << std::endl;

/* Modify the Integer value */
amazonPort.SetInt(443);
```

6. To read a float number you can use this snippet


```cpp

/* Declare an object to store the value 
 * and assign the document "cloud" "provider" value to amazon
 * Since the "cloud" object is an Array object in JSON 
 * at 0 it contains "AWS" and at 1 it contains "Google" 
 */
Value& anyFloat number = d["float"];

/* Print the Float/Double value */
std::cout << anyFloat.GetDouble() << std::endl;


/* Modify the Float/Double value */
anyFloat.SetDouble(443.235);

```

This should cover all the JSON parsing needs. Please refer to the RapidJSON docs
if the document does not satisfy your needs.

For full details on the implementation, checkout the `dom_parser.cpp`

## JSON Writer

To learn JSON writing, Let's Create a JSON file similar to the example.json given below 

For example.json contains
```json
{
  "wireless": {
      "status": "on",
      "ssid": "Hegde-Jio",
      "password": "secretpassword"
  },
  "cloud": [
        {
            "provider": "AWS",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 8886,
            "certLocation": "/home/yogesh/.aws/"
        },
        {
            "provider": "Google",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 9096,
            "certLocation": "/home/yogesh/.gcp/"
        },
    ]
}
```

1. Lets create the wireless object

Let's start by creating document variables for storing the JSON file

```cpp

/* Declare an object to store the JSON document in  */
Document d;

/* Declare the First JSON object */
d.SetObject();

/* Declare new JSON object called as wireless */
Value wireless(kObjectType);

/* Lets store the JSON object members for wireless */
wireless.AddMember("status", "on", d.GetAllocator());
wireless.AddMember("ssid", "Hegde-Jio", d.GetAllocator());
wireless.AddMember("password", "secretpassword", d.GetAllocator());

/* Add this object as a member to the JSON  document `d`*/
d.AddMember("wireless", wireless, d.GetAllocator());
```

After this you should have this output
```json
{
  "wireless": {
      "status": "on",
      "ssid": "Hegde-Jio",
      "password": "secretpassword"
  }
}
```

2. Now lets create the "cloud" array object 

```cpp
/* Declare AWS object and fill in its members */
Value aws(kObjectType);
aws.AddMember("provider", "AWS", d.GetAllocator());
aws.AddMember("endpoint", "djsflkjsdlfjalsdkf", d.GetAllocator());
aws.AddMember("port", 8886, d.GetAllocator());
aws.AddMember("certLocation", "/home/yogesh/.aws/", d.GetAllocator());

/* Declare Google object and fill in its members */
Value google(kObjectType);
google.AddMember("provider", "google", d.GetAllocator());
google.AddMember("endpoint", "djsflkjsdlfjalsdkf", d.GetAllocator());
google.AddMember("port", 9096, d.GetAllocator());
google.AddMember("certLocation", "/home/yogesh/.gcp/", d.GetAllocator());

/* Declare the Cloud JSON array object*/
Value cloud(kArrayType);

/* Add AWS and Google Entries to the cloud JSON array object*/
cloud.PushBack(aws, d.GetAllocator());
cloud.PushBack(google, d.GetAllocator());

/* Add cloud JSON array object to the document `d`*/
d.AddMember("cloud", cloud, d.GetAllocator());

```

Combined with 1. & 2. you should have this output
```json
{
  "wireless": {
      "status": "on",
      "ssid": "Hegde-Jio",
      "password": "secretpassword"
  },
  "cloud": [
        {
            "provider": "AWS",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 8886,
            "certLocation": "/home/yogesh/.aws/"
        },
        {
            "provider": "Google",
            "endpoint": "djsflkjsdlfjalsdkf",
            "port": 9096,
            "certLocation": "/home/yogesh/.gcp/"
        },
    ]
}
```
3. Writing it all into an `output.json` document 

```cpp
/* Open the output.json file in write mode */
FILE* out = fopen("output.json", "wb");

/* Declare write buffer */ 
char writeBuffer[65536];

/* Declare stream for writing the output stream */
FileWriteStream os(out, writeBuffer, sizeof(writeBuffer));

/* Make the output easier to read for Humans (Pretty) */
PrettyWriter<FileWriteStream> writer(os);

/* Write the JSON document `d` into the file `output.json`*/
d.Accept(writer);

/* Close the output.json file*/
fclose(out);
```
This should cover all the JSON writing needs. Please refer to the RapidJSON docs
if the document does not satisfy your needs.

For full details on the implementation, checkout the `dom_writer.cpp`

