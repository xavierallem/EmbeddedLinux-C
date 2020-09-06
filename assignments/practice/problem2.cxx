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

/* --- Project Includes --- */
#include <errno.h>


using namespace rapidjson;


/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/** 
 *  @brief Description on Fopen,unix_error
 *  
 *  Error Handling
 *
 *  @return fp
 */
 void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

FILE *Fopen(const char *filename, const char *mode) 
{
    FILE *fp;

    if ((fp = fopen(filename, mode)) == NULL)
    unix_error((char*)"Fopen error");

    return fp;
}
/** 
 *  @brief Description on function_2
 *  
 *  Contains code to connect Ethernet connection
 *
 *  @return void
 */

void function_2 (Document& jsonDocument)
{



	/* Open the interfaces file in write mode */
     FILE*	fp = Fopen("/etc/network/interfaces", "wb"); 
    /* Parsing device */
	Value& edevice = jsonDocument["ethernet"][0]["device"];
	/* variable to store  */
	char device[100];
	/* Copying parsed data to variable */
    strcpy(device,edevice.GetString());
    /* Parsing allocation data */
	Value& ealloc = jsonDocument["ethernet"][0]["allocation"];
	/* Variable to store */
	char alloc[100];
	/* Copying the parsed data to variable */
    strcpy(alloc,ealloc.GetString());
    /* Parsing Ip */
	Value& eIp = jsonDocument["ethernet"][0]["ipAddress"];
	/* Variable to store */
	char ip[100];
	/* Coping parsed data into variable */
    strcpy(ip,eIp.GetString());
    /* Parsing subnet mask */
	Value& esm = jsonDocument["ethernet"][0]["subnetMask"];
	/* Variable to store */
	char sm[100];
	/* Copying parsed data into variable  */
    strcpy(sm,esm.GetString());
    /* Parsing router address */
	Value& erout = jsonDocument["ethernet"][0]["routerAddress"];
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
	strcpy(c,"        gateway ");
    /* Append the command */
	strcat(c,rout);
	/* Put in file */
	puts(c);
	
	
    /* Close file stream */
	fclose(fp);
	
}
/** 
 *  @brief Description on function_1
 *  
 *  Contains code to execute wifi
 *
 *  @returnvoid 
 */
void function_1 (Document& jsonDocument)
{   
    /*copying  nmcli command */
	char nm[100]="nmcli d wifi connect ";
	/* parsing ssid from json file */
    Value& essid = jsonDocument["wireless"]["ssid"];
    /* variable to copy ssid  */
    char ssid[100];
    /* Copying the parsed string to variable */
    strcpy(ssid,essid.GetString());
    /* Parsing password */
	Value& epass = jsonDocument["wireless"]["password"];
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
    /* System command */
	system(nm);
}
/** 
 *  @brief Description on initialize
 *  
 *  Code containing for Host and Time
 *
 *  @return List all Function returns 
 */
void initialize(Document& jsonDocument)
{
    /* Parsing host */
    Value& ehost = jsonDocument["hostname"];
    /* Parsing time */
    Value& etime = jsonDocument["timezone"];
    /* variable to store the command  */
    char host[100]="sudo hostname ";
    /* Copying hostname */
    strcpy(host,ehost.GetString());
    /* System command */
    system(host);
    /* variable to store the command */
    char time[100]="sudo timedatectl set-timezone ";
    /* Copy the time details */
    strcpy(time,etime.GetString());
    /* System command */
    system(time);



}

/** 
 *  @brief Description on main
 *  
 * Initializes the startup messages and function call
 *  
 *
 *  @return p
 */

int main (void)

{
    
    puts("Getting Started/Initializing.............");
    
/* Open the example.json file in read mode */
     FILE* fp = Fopen("example.json", "rb"); 

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
        
/*---------------Initializing----------------*/    
    initialize(d);
    
        
    puts("-----Starting Wfifi------");

/*----------------------wifi function---------------------*/
    function_1(d);

    puts("Getting Ethernet data.............");
    puts("-----Starting Ethernet connection------");
/*-------------Ethernet--------------*/
    function_2(d);

	

        return 0;
        
}

