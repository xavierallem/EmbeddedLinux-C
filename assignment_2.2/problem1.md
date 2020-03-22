# Problem 1

Design a data structure to store a list of known sensors segregated into different types.

List of known Sensors, 

Type : Temperature sensors   
List - BME280, SHT3x, DHT11, DHT22.

Type : Humidity 
List - BME280, DHT11

Please use the given Sensors and their types only, and not take input from the user. 

Instead the user will input the Sensor Name and the output should be the Type of sensor.

For Example:

User Input:
```
BME280
```

Ideal output:
```
Temperature sensors
Humidity
```


Design considerations:
1. The data structure must consume very small amount of memory, O(n) is ideal.
2. The time needed to search the data structure must be very small, O(1) is ideal. 

Constraints:
1. Only use C programming 
2. All the data structures used must be supported by C.