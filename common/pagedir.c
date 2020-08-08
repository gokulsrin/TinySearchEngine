//need to create inside this file my pagesave function 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"

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
//given some set filepath of webpage file, i will try to extract webpage
webpage_t* pageload(char * filepath){
    //validate args
    if(filepath == NULL){
        fprintf(stderr, "The filepath is null");
        return NULL;
    }
    //attempt to open file 
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL){
        fprintf(stderr, "The file pointer passes was null");
        return NULL;
    }
    //assume webpage is non-null and defined per the reqs
    //read the first line as the url of the file
    
    // given the tse cralwer output 0, when cpy the page source, it seems that this program indeed works 
    int bufferLength = 255;
    char buffer[bufferLength];

    //the first two lines correspond to url and depth
    char *temp = fgets(buffer, bufferLength, fp);
    assert(temp != NULL);
    char * url = count_malloc(bufferLength);
    assert(url != NULL);
    strcpy(url, temp);
    // printf("\nUrl:%s", url);

    temp = fgets(buffer, bufferLength, fp);
    assert(temp != NULL);
    char *depth = count_malloc(bufferLength);
    assert(depth != NULL);
    strcpy(depth, temp);
    // printf("\nDepth:%s", depth);

    //now we simply need to create a webpage that has all of this information
    webpage_t *webpage = webpage_new(url, atoi(depth), NULL);
    //we can't free url/html because webpage uses them -- need to free outside 
    if(webpage == NULL){
        fprintf(stderr, "The instantiation of a webpage failed");
        return NULL;
    }
    fclose(fp);
    // count_free(url);
    count_free(depth);
    // count_free(filepath);
    return webpage;
}
