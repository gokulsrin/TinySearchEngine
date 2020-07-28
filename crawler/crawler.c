//This is the crawler.c file... it's going yo do the crawling
#include <stdio.h>
#include "../libcs50/bag.h"
#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "unistd.h"

void crawl(char *su, char *pd, const int md);

int main(const int argc, const char *argv[]){
    // ./crawler seedURL pageDirectory maxDepth`
    //there are four arguments
    if(argc == 4){
        char *seedURL = (char*)argv[1];
        char *pageDirectory = (char*)argv[2];
        const int maxDepth = atoi(argv[3]);
        //there was no error
        if(seedURL != NULL && access(pageDirectory, F_OK) != -1 && maxDepth >= 0){
            crawl(seedURL, pageDirectory, maxDepth);
        }
        else{
            printf("Error");
        }

    }
}

//this is the crawler function where all of the magic happens
void crawl(char *su, char *pd, const int md){
    //create the bag
    bag_t *bag = bag_new();
    //create the hashtable 
    const int num_slots = 1000;
    hashtable_t *ht = hashtable_new(num_slots);
    //begin with the first webpage 
    int depth = 0;
    webpage_t *webpage = webpage_new(su, (const int)depth, NULL);
    if(webpage != NULL){
        //insert into bag 
        bag_insert(bag, webpage);
        //insert the url into hashtable hashing using the url itself
        hashtable_insert(ht, (const char*)su, su);
        //create the temp webpage 
        webpage_t *twp;
        //while there is always something else in the bag
        twp = bag_extract(bag);
        while(twp!= NULL){
            //pause for one second

            //fetch the html 
            webpage_fetch(twp);

        }
    }
    else{
        printf("Error: null webpage");
    }
}
