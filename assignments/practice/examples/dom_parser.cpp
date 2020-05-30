/**
 * @defgroup   DOM_PARSER dom parser
 *
 * @brief      This file implements DOM style JSON parser.
 *
 * @author     Yogesh
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

        /* Declare an object to store the value 
         * and assign the document "ethernet" "status" value to eStatus
         */
        Value& eStatus = d["ethernet"]["status"];

        /* Print the string value */
        std::cout << "Ethernet Status = " << eStatus.GetString() << std::endl;

        /* Modify the string value */
        eStatus.SetString("off");

        /* Declare an object to store the value 
         * and assign the document "cloud" "provider" value to amazon
         * Since the "cloud" object is an Array object in JSON 
         * at 0 it contains "AWS" and at 1 it contains "Google" 
         */
        Value& amazon = d["cloud"][0]["provider"];

        /* Print the string value */
        std::cout << "Cloud 0 Provider = " << amazon.GetString() << std::endl;

        Value& google = d["cloud"][1]["provider"];

        /* Print the string value */
        std::cout << "Cloud 1 Provider = " << google.GetString() << std::endl;

        /* Declare an object to store the value 
         * and assign the document "cloud" "provider" value to amazon
         * Since the "cloud" object is an Array object in JSON 
         * at 0 it contains "AWS" and at 1 it contains "Google" 
         */
        Value& amazonPort = d["cloud"][0]["port"];

        /* Print the Integer value */
        std::cout << "AWS Port = " << amazonPort.GetInt() << std::endl;

        /* Modify the Integer value */
        amazonPort.SetInt(443);

        /* Declare write buffer */ 
        char writeBuffer[65536];

        /* Declare stream for writing the output stream */
        FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));

        /* Make the output easier to read for Humans (Pretty) */
        PrettyWriter<FileWriteStream> writer(os);

        /* Write the JSON document `d` into the file `output.json`*/
        d.Accept(writer);

        return 0;

}
