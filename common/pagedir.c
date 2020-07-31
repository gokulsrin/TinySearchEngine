//need to create inside this file my pagesave function 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pagesave(char * url, int depth, char * content, int id){
    
    if(url != NULL && depth >= 0 && content != NULL && id >= 0){
         //do the math to concatonate the id with the directory
        int length = snprintf( NULL, 0, "%d", id);
        char* str = malloc(sizeof(char*));
        snprintf(str, length + 100000, "./crawldir/%d", id);

        //create file pointer and print to the file 
        FILE *fp = fopen(str, "w");
        fprintf(fp, "%s \n %d \n %s \n", url, depth, content);
        
        //close file and free pointer
        fclose(fp);
        free(str);
    }
    //some error has occoured and because this function is void per the specifications, I need to print instead of return.
    else{
        printf("Something has gone wrong; incorrect input; Overwriting Error Code 0!");
    }
}
