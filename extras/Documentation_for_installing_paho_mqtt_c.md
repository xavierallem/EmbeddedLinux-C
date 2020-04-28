# Installing Paho MQTT_C on ubuntu 16.04

## Download source by running in command line: 

   git clone https://github.com/eclipse/paho.mqtt.c
   
## Installation by going in paho.mqtt.c directory : 

   make

   Before proceeding we need to install **Doxygen** : 

   ### Download source : 
       
       git clone https://github.com/doxygen/doxygen.git
       
   ### Install doxygen by : 
   
      cd doxygen
      mkdir build
      cd build
      
   ### Now before proceeding we need to install **flex** and **bison**:
   
   #### Install flex by running command : 
       
        sudo apt-get install flex
            
   #### Install bison by running command : 
       
        sudo apt-get install bison
            
   ### Now run :
   
      cmake -G "Unix Makefiles" ..
      
   ### Now finally we can proceed to install paho mqtt_c library : 
   
      make<br>
      sudo make install<br>
            
    
   