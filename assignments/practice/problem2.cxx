/** @file <file_name>.c
 *  @brief Give a description of the file 
 *  
 *  Give full description of the file 
 *  
 *  @author Full name of the author 
 *  @bug List Any bugs found in the file  
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

/* --- Standard Includes --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>

/* RapidJSON Includes */
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;


/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/** 
 *  @brief Description on function_1
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

void function_1 (char *ptr)
{


system(ptr);

        /*Make sure you comment every line */
	
}

/** 
 *  @brief Description on main
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

int main (void)

{/* Open the example.json file in read mode */

/*----------------------wifi---------------------*/


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
	char nm[1000]="nmcli d wifi connect ";
       Value& essid = d["wireless"]["ssid"];
       char ssid[100];
       strcpy(ssid,essid.GetString());
	Value& epass = d["wireless"]["password"];
	char pass[100];
	strcpy(pass,epass.GetString());

	strcat(nm,ssid);
	strcat(nm," password");
	strcat(nm,pass);
	system(nm);
/*-------------Ethernet--------------*/
	
	 fp = fopen("/etc/network/interfaces", "wb"); 

	Value& edevice = d["ethernet"][0]["device"];
	char device[100];
        strcpy(device,edevice.GetString());
	Value& ealloc = d["ethernet"][0]["allocation"];
	char alloc[100];
        strcpy(alloc,ealloc.GetString());
	Value& eIp = d["ethernet"][0]["ipAddress"];
	char ip[100];
        strcpy(ip,eIp.GetString());
	Value& esm = d["ethernet"][0]["subnetMask"];
	char sm[100];
        strcpy(sm,esm.GetString());
	Value& erout = d["ethernet"][0]["routerAddress"];
	char rout[100];
        strcpy(rout,erout.GetString());

	char c[100]="auto ";
	strcat(c,device);
	puts(c);
	strcpy(c,"iface ");

	strcat(c,device);
	strcat(c," inet ");
	strcat(c,alloc);
	puts(c);
	strcpy(c,"        address ");
	
	strcat(c,ip);
	puts(c);
	strcpy(c,"        netmask ");
	
	strcat(c,sm);
	puts(c);
	strcpy(c,"        gatewat ");
	
	strcat(c,rout);
	puts(c);
	
	

	fclose(fp);

	
	
	






        /*Make sure you comment every line */
        return 0;
        
}

