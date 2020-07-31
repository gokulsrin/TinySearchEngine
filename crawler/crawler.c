//This is the crawler.c file... it's going yo do the crawling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libcs50/bag.h"
#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../common/pagedir.h"
#include "unistd.h"


void crawl(char *su, char *pd, const int md);
void stringdelete(void *arg, const char *key, void *item);

int main(const int argc, const char *argv[]){
    // ./crawler seedURL pageDirectory maxDepth`
    //there are four arguments
    if(argc == 4){
        char *seedURL = (char*)argv[1];
        char *pageDirectory = (char*)argv[2];
        const int maxDepth = atoi(argv[3]);
        if(strlen(seedURL) < 32){
            printf("Error 2; Invalid input: Please enter valid inputs");

        }
        //there was no error
        if(seedURL != NULL && access(pageDirectory, F_OK) != -1 && maxDepth >= 0){
            crawl(seedURL, pageDirectory, maxDepth);
        }
        else{
            printf("Error 2; Invalid input: Please enter valid inputs");
        }

    }
    else{
        printf("Error 1; Invalid Input: Not enough input");
    }
}

//this is the crawler function where all of the magic happens
void crawl(char *su, char *pd, const int md){
    //create the bag
    bag_t *bag = bag_new();
    // bag_t *trash = bag_new();
    //create the hashtable 
    const int num_slots = 1000;
    hashtable_t *ht = hashtable_new(num_slots);
    //begin with the first webpage 
    int depth = 0;
    //initialize the id 
    int id = 0;
    webpage_t *webpage = webpage_new(su, (const int)depth, NULL);
    if(webpage != NULL){
        //insert into bag 
        bag_insert(bag, webpage);
        //insert the url into hashtable hashing using the url itself
        hashtable_insert(ht, (const char*)su, su);
        //create the temp webpage, and the pointer 
        webpage_t *twp;
        webpage_t *pointer;
        //while there is always something else in the bag
        twp = bag_extract(bag);
        while(twp!= NULL){
            //pause for one second
            //fetch the html 
            webpage_fetch(twp);
            //url, depth, content, id
            pagesave(webpage_getURL(twp), webpage_getDepth(twp), webpage_getHTML(twp), id);
            //increment id 
            id++;
            //here we look to extract links given that the depth is less than the max depth
            if(webpage_getDepth(twp) < md){
                //extract all the links from the webpage and add them as webpage objects to the bag
                int pos = 0;
                char *result;
                while ((result = webpage_getNextURL(twp, &pos)) != NULL) {
                    //here we need to normalize each url passing url pointer
                    NormalizeURL(result);
                    //we only proceed if it is an internal url 
                    if(IsInternalURL(result)){
                        //attempt to hash - if it isnt there and non null
                        if(hashtable_insert(ht, (const char*)result, result)){
                            //create new webpage and add it to bag
                            //may need to free this pointer
                            pointer = webpage_new(result, (const int)(webpage_getDepth(twp) + 1), NULL);
                            //provided the creation happened succesfully
                            if(pointer != NULL){
                                bag_insert(bag, pointer);
                            }
                        }
                    }
                    // free(result);
                }
            
            }
            //we have used the old twp, so now we can free the webpage pointed to
            // if(twp != NULL){
            //     bag_insert(trash,twp);
            // }
            // webpage_delete(twp);
            twp = bag_extract(bag);
        }
        //at this point, in theory, all of the important processes have been run, and we can begin to free mem
        //need to free hashtable and bag 
        bag_delete(bag,webpage_delete);
        // bag_delete(trash, webpage_delete);
        //free hashtable 
        hashtable_iterate(ht, NULL, stringdelete);
        // count_report(stdout, "Report");
        printf("0: Successful");
    }
    else{
        printf("Error 3: null webpage");
    }
}

void stringdelete(void *arg, const char *key, void *item){
    //the use case here is that we free all of the strings in the hashtable
    if(arg == NULL){
        if(key != NULL){
            count_free((char*)key);
        }
    }
}
