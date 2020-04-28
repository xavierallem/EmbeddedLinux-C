/** @file MQTTPub-Sub.c
 *  @brief MQTT Publisher-Subscription system 
 *  
 *  MQTT Client publishes a message to RabbitMQ 
 *  broker which directs the published messages 
 *  to the MQTT Clients which have subscribed 
 *  to the topic on which publisher has published
 *  message.
 *  
 *  @author Sumeet Kumar Rai 
 *  @bug    No known bugs. 
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */
   /*Host address to connect to broker which sets on port 1883*/
   #define ADDRESS     "tcp://localhost:1883"

   /*ClientId is required for device creation*/
   #define CLIENTID    "sumslim-369"

   /*Account username on RabbitMQ broker*/
   #define USERNAME    "sumslim"

   /*Account password on RabbitMQ broker*/
   #define PASSWORD    "astrophy77$"

   /*Topic to which publisher will publish message*/
   #define TOPIC       "iotiot"

   /*Payload (message1) for initiation*/
   #define PAYLOAD1    "RabbitMQ Operation successful"

   /*Payload (message2) for testing purpose*/
   #define PAYLOAD2    "IOTIOT is hiring" 

   /*Quality of Security set to 1 means client publish message until acknowledged*/
   #define QOS          1

   /*Timeout*/
   #define TIMEOUT      10000L
   

/* --- Standard Includes --- */
    #include "stdlib.h"
    #include "string.h"
    #include "unistd.h"

/* --- Project Includes --- */
    #include "MQTTClient.h"

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

    /* MQTTClient_deliveryToken instance*/
   volatile MQTTClient_deliveryToken deliveredtoken;

/** 
 *  @brief Function to publish message as 
 *         a MQTT client to the server/broker.
 *  
 *  Takes argument of cient instance, topic to which it 
 *  publish message to and payload(the message).
 *  Create a new MQTT message and set a payload.
 *  Publish message via MQTT protocol.
 *  Wait maximum 1 second for a message delivered ACK from the server.
 *
 *  @return void, just prints the output. 
 */

    void publish(MQTTClient client, char* topic, char* payload) {

	/*Initializes new message*/
	MQTTClient_message pubmsg = MQTTClient_message_initializer;

	/*sets the payload*/
	pubmsg.payload = payload;
	pubmsg.payloadlen = strlen(pubmsg.payload);

        /*sets the quality of security*/
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

	/*creates deliverytoken variable*/
	MQTTClient_deliveryToken token;

	/*finally publishes message*/
	MQTTClient_publishMessage(client, topic, &pubmsg, &token);
	MQTTClient_waitForCompletion(client, token, TIMEOUT);

	/*prints the delivery message*/
	printf("Message '%s' with delivery token %d delivered\n", payload, token);

    }

/** 
 *  @brief Function gives a delivery confirmation
 *  
 *  Gives a delivery confirmation with token value
 *
 *  @return void, just prints the output. 
 */

    void delivered(void *context, MQTTClient_deliveryToken dt){
	
	/*prints the delivery message confirmation*/
	printf("Message with token value %d delivery confirmed\n", dt);
	deliveredtoken = dt;

    }

/** 
 *  @brief Function gives a receive confirmation
 *  
 *  Gives a receive confirmation, sets the payload
 *
 *  @return int, prints the output and returns 1. 
 */

    int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
	
	/*sets the payload message*/
	char* payload = message->payload;
        
        /*prints received message acknowledgment*/
	printf("Received operation %s\n", payload);

	/*free unwanted memory*/
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;

    }

/** 
 *  @brief Function gets called when there is
 *         loss in connectivity.
 *  
 *  Also gives the reason of loss in connectivity.
 *
 *  @return void, just prints the output. 
 */

    void connlost(void *context, char *cause){
	
	printf("\nConnection lost\n");

	/*prints the reason*/
	printf("     cause: %s\n", cause);

    }


/** 
 *  @brief To perform I/O operations 
 *         make function call.
 *  
 *  Perform function calls to publish and 
 *  subscribe message to the server/broker 
 *  and also give back ack message.
 *
 *  @return int 
 */

int main(int argc, char* argv[]) {

	/*MQTT Client object*/
	MQTTClient client;

	/*creates client instance*/
	MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	/*initiates connections with username and alive session*/
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	conn_opts.username = USERNAME;
	conn_opts.password = PASSWORD;
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;

	/*callback for every message published*/
	MQTTClient_setCallbacks(client, NULL, connlost, on_message, delivered);

	/*check if connection is successful or not*/
	int rc;
	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
	printf("Failed to connect, return code %d\n", rc);
	exit(-1);
	}

	/* if successful publishes message with topic and payload*/
	publish(client, TOPIC, PAYLOAD1);
	//set information
	publish(client, TOPIC, PAYLOAD2);

	/*subscribe to topic and give back ack message*/
	printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
	   "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
	MQTTClient_subscribe(client, TOPIC, QOS);

	/*message publication every 3 sec*/
	for (;;) {

	    //send information
	    publish(client, TOPIC, PAYLOAD2);

	    /*every 3 seconds*/
	    sleep(3);

	}

	char ch; 
	do
	{
	ch = getchar();
	} while(ch!='Q' && ch != 'q');

	/* dsiconnect if no ack that client is alive within timeout*/
	MQTTClient_disconnect(client, 1000);
	MQTTClient_destroy(&client);
	return rc;

}
