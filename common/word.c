/*
* This is the file that implements word.h 
*
*As of now only normalize word is implemented :)
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../libcs50/memory.h"

//bear in mind, each pointer to a word has been malloc'd
char* normalize_word(char* word){
    // int l = strlen(word);
    char *w = count_malloc(strlen(word));
    //check args
    if(word == NULL){
        fprintf(stderr, "The word passes is null");
        return NULL;
    }
    //if small word, return NULL
    if(strlen(word) < 3){
        return NULL;
    }
    else{
        printf("\nHere");
        // normalize the word
        int j=0;
        for(int i=0; word[i]; i++)
        {   //either char is uppercase
            if(word[i]>=65 && word[i]<=90)
            {
                    w[j] = word[i] + 32;    
                    j++;        
            }
            //lowercase
            else if(word[i]>=65+32 && word[i]<=90+32){
                w[j] = word[i];
                j++;
            }  
            //or end char  
            else if(word[i] == '\0'){
                return w;
            }        
            //if none of these, we don't add it
        }
        //free the current pointer (in the actual case)
        // count_free(word);
        return w;
    }
}