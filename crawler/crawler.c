//This is the crawler.c file... it's going yo do the crawling
#include "../libcs50/bag.h"
#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "unistd.h";

int main(const int argc, const char *argv[]){
    // ./crawler seedURL pageDirectory maxDepth`
    //there are four arguments
    if(argc == 4){
        char *seedURL = argv[1];
        char *pageDirectory = argv[2];
        char *maxDepth = argv[3];
        webpage_t *webpage = webpage_new(seedURL, pageDirectory, maxDepth);
        //there was no error
        if(webpage != NULL){
            crawler(webpage);
        }
        else{
            printf("Error");
        }

    }
}

//this is the crawler function where all of the magic happens
void crawler(webpage_t *webpage){
    //begin with the first webpage 
    bag_t bag = bag_new()
}
