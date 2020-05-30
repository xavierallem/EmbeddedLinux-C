/**
 * @defgroup   DOM_WRITER dom writer
 *
 * @brief      This file implements DOM style JSON document writer.
 *
 * @author     Yogesh (yh42)
 */

/* Standard Includes */
#include <cstdio>
#include <iostream>

/* RapidJSON Includes */
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;

int main() 
{

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

        /* Declare AWS object and fill in its members */
        Value aws(kObjectType);
        aws.AddMember("provider", "AWS", d.GetAllocator());
        aws.AddMember("endpoint", "djsflkjsdlfjalsdkf", d.GetAllocator());
        aws.AddMember("port", 8886, d.GetAllocator());
        aws.AddMember("certLocation", "/home/yogesh/.aws/", d.GetAllocator());

        /* Declare Google object and fill in its members */
        Value google(kObjectType);
        google.AddMember("provider", "Google", d.GetAllocator());
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

        /* Open the output.json file in write mode */
        FILE *out = fopen("output.json", "wb");

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

        /* Print Done */
        std::cout << "Done!, check the output.json file. "<< std::endl;

        return 0;

}
