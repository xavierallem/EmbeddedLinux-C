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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* --- Project Includes --- */


/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/**
 * @brief      Search the given string in the file
 *
 * @param      fname  The file name
 * @param      str    The string to search
 *
 * @return     Returns -1 on Error and 0 on not found and 1 on SUCCESS
 */
int searchInFile(char *fname, char *str) {
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    //Changed size to be equal
    int n=strlen(str);
    char temp[n];
    

    if((fp = fopen(fname, "r")) == NULL) {
        printf("Error: Opening the file.\n");
        
      return(-1);
    }

    while(fgets(temp, n, fp) != NULL) {
        if((strstr(temp, str)) != NULL) {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result++;
           
            return (1);
        }
        line_num++;
    }
    // Free the heap
    free(str);
    free(fname);
    
    

    if(find_result == 0) {
        printf("\nSorry, couldn't find a match.\n");
        
    }
    
// Free the stream
        fclose(fp);
   
    return(0);
}

int main (void)
{

        /*Make sure you comment every line */
        searchInFile("db.txt", "iotiot");
        searchInFile("db.txt", "iotiot");
        return 0;
        
}
