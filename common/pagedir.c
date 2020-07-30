//need to create inside this file my pagesave function 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pagesave(char * url, int depth, char * content, int id){
    
    if(url != NULL && depth >= 0 && content != NULL && id >= 0){
         //do the math to concatonate the id with the directory
        int length = snprintf( NULL, 0, "%d", id);
        char* str = malloc(sizeof(char*));
        snprintf(str, length + 12, "./crawldir/%d", id);

        //create file pointer and print to the file 
        FILE *fp = fopen(str, "w");
        fprintf(fp, "%s \n %d \n %s \n", url, depth, content);
        
        //close file and free pointer
        fclose(fp);
        free(str);
        
    }
    else{
        perror("Something has gone wrong; incorrect input");
    }
}
