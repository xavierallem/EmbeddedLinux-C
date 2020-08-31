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

void function_2 (void)
{



	/* Open the interfaces file in write mode */
     FILE*	fp = fopen("/etc/network/interfaces", "wb"); 
    /* Parsing device */
	Value& edevice = d["ethernet"][0]["device"];
	/* variable to store  */
	char device[100];
	/* Copying parsed data to variable */
    strcpy(device,edevice.GetString());
    /* Parsing allocation data */
	Value& ealloc = d["ethernet"][0]["allocation"];
	/* Variable to store */
	char alloc[100];
	/* Copying the parsed data to variable */
    strcpy(alloc,ealloc.GetString());
    /* Parsing Ip */
	Value& eIp = d["ethernet"][0]["ipAddress"];
	/* Variable to store */
	char ip[100];
	/* Coping parsed data into variable */
    strcpy(ip,eIp.GetString());
    /* Parsing subnet mask */
	Value& esm = d["ethernet"][0]["subnetMask"];
	/* Variable to store */
	char sm[100];
	/* Copying parsed data into variable  */
    strcpy(sm,esm.GetString());
    /* Parsing router address */
	Value& erout = d["ethernet"][0]["routerAddress"];
	/* Variable to store */
	char rout[100];
	/* Copying the parsed data */
    strcpy(rout,erout.GetString());
    /*  Commands for interface file   */
    
    /* variable to store first command string */
	char c[100]="auto ";
	/* append to command  */
	strcat(c,device);
	/* Put in file */
	puts(c);
	/* Copy next command */
	strcpy(c,"iface ");
    /* Append in command */
	strcat(c,device);
	/* Append for  command */
	strcat(c," inet ");
	/* Append for command */
	strcat(c,alloc);
	/* Put in file */
	puts(c);
	/* Copy the command */
	strcpy(c,"        address ");
	/* Append the command */
	strcat(c,ip);
	/* Put in file */
	puts(c);
	/* Copy the command */
	strcpy(c,"        netmask ");
	/* Append the command */
	strcat(c,sm);
	/* Put in file */
	puts(c);
	/* Copy the command */
	strcpy(c,"        gatewat ");
    /* Append the command */
	strcat(c,rout);
	/* Put in file */
	puts(c);
	
	
    /* Close file stream */
	fclose(fp);
	
}
void function_1 (void)
{   /* Open the example.json file in read mode */
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
        /*copying  nmcli command */
	   char nm[100]="nmcli d wifi connect ";
	    /* parsing ssid from json file */
       Value& essid = d["wireless"]["ssid"];
       /* variable to copy ssid  */
       char ssid[100];
       /* Copying the parsed string to variable */
       strcpy(ssid,essid.GetString());
       /* Parsing password */
	   Value& epass = d["wireless"]["password"];
	   /* variable to copy ssid */
	   char pass[100];
	   /*Copying the parsed string to variable */
	   strcpy(pass,epass.GetString());

        /* Appending to command */
    	strcat(nm,ssid);
	    /* Appending to command */
	    strcat(nm," password");
	    /* Appending to command */
    	strcat(nm,pass);
	    system(nm);
}

/** 
 *  @brief Description on main
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

int main (void)

{
    
    puts("Getting Started.............");
    puts("-----Starting Wfifi------");

/*----------------------wifi function---------------------*/
function_1();

   puts("Getting Ethernet data.............");
    puts("-----Starting Ethernet connection------");
/*-------------Ethernet--------------*/
function_2();

	

        return 0;
        
}

