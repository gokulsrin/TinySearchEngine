/**This is the file where I need to essentially parse all of the webpage files created by crawler
I need components to 
1) given a directory with webpage files, open the files and reconstruct a webpage_t from them
    1b) Handle all file stuff
2) Within each valid webpage, search examine word of the html text and add the word to our index_t data struct 
    2b) make sure all checks and mem allocation and freeing is present

 **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>


#include "../libcs50/bag.h"
#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../common/index.h"
#include "../common/word.h"
#include "../common/pagedir.h"

bool process_arguments(const int argc, const char *argv[], char* p, char* i);

index_t* index_build(char *filedir, int size);

bag_t* directory_parse(char *filedir, int *len);

void deleteitem(void *item);

void deletewebpage(void *item);

int main(const int argc, const char *argv[]){
    // testing normalize word-confirmed it works 
    // char *word = "MMMMMEO";    
    // printf("\n%s", word);
    // word = normalize_word(word);
    // printf("\n%s", word);
    
    //testing that the name of the file is printed 
    // webpage_t *webpage = pageload("../crawler/crawldir/1");
    //we get the html so it works
    // if(webpage_fetch(webpage)) {
    //     // char *html = webpage_getHTML(webpage);
    //     // printf("Found html: %s\n", html);
    // }
    //test if we can get word - we can 
    // int pos = 0;
    // char *word = webpage_getNextWord(webpage, &pos);
    // for(int i = 0; i < 20; i++){
    //      printf("\n%s\n", word);
    //      word = webpage_getNextWord(webpage, &pos);
    // }

    // webpage_delete(webpage);
    // if(webpage == NULL){
    //     return -2;
    // }
    //create pointers that we will use later on
    char *pageDir = count_malloc(sizeof(char*));
    char *indexFile = count_malloc(sizeof(char*));
    //ensure that all of the arguments passed are valid
    if(!process_arguments(argc, argv, pageDir, indexFile)){
        fprintf(stderr,"\nmission failed; we'll get 'em next time\n");
        count_free(pageDir);
        count_free(indexFile);
        return -1;
    }
    //build the index 
    index_t *index = index_build(pageDir, 100);
    assert(index != NULL);
    //this is the difference
    FILE *fp = fopen(indexFile, "w");
    index_save(index, fp);
    
    //close file free index
    fclose(fp);
    index_delete(index, &deleteitem);

    //free everything
    count_free(pageDir);
    count_free(indexFile);
    return 0;
}
bool process_arguments(const int argc, const char *argv[], char* p, char* i){
    if(argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL){
        fprintf(stderr, "Inapropriate initial arguments");
        return false;
    }
    strcpy(p,(char*)argv[1]);
    // printf("\n%s\n", p);
    strcpy(i,(char*)argv[2]);

    //now we need to check the access conditions of pageDir path given
    //by the way, credit to stackoverflow user To1ne for providing me the outline for this check
    //The original answer can be viewed here: https://stackoverflow.com/a/15274698/12665395
    if (access(p, F_OK) != 0) {
        if (ENOENT == errno) {
            // does not exist
            fprintf(stderr, "Directory (argument 1) does not exist");
            return false;
        }
        if (ENOTDIR == errno) {
            // not a directory
            fprintf(stderr, "Argument 1 is not a directory");
            return false;
        }
        //is a directory
    }
    //check if the indexFileName is writeable
    FILE *fp;
    if( (fp = fopen(i, "w")) == NULL){
        fprintf(stderr, "failed to write to file specified by argument 2");
        return false;
    }
    fclose(fp);
    return true;
}
//need to build an index by reading line by line from the saved webpages
index_t* index_build(char *filedir, int size){
    //create our index here 
    index_t *index = index_new(size);
    //create bag with all of the webpages in the directory 
    int *len = count_malloc(sizeof(int*));
    bag_t *webpages = directory_parse(filedir, len);
    //little trick here. I don't want to track file id so instead I'll find the exit of my looping varibale
    //that corresponds to num files + 1. Because we can assume the directory is propper, then the file ids start at 
    //1 and increase. Hence the last one is num files. and bag extract takes them out in reverse insert order.
    int k = *len - 1;
    // printf("\n%d\n", k);
    if(webpages == NULL){
        fprintf(stderr, "Error creating bag of webpages");
        return NULL;
    }
    //little test to make sure webpages are there are being created-so it seems theyre being created.
    webpage_t *wp = bag_extract(webpages);
    while(wp != NULL){
        //fetch html
        if(!webpage_fetch(wp)){
            fprintf(stderr, "\nFailed to fetch html");
            return NULL;
        }
        //go through each word in the page 
        int i = 0;
        char *word = webpage_getNextWord(wp, &i);
        while(word != NULL){
            //operations here
            // printf("\nBefore:%s ", word);
            // word = normalize_word(word);
            // printf("\nAfter:%s ", word);
            // if(word != NULL){
                //turn the current k into string corresponding to id
                char id[10];
                sprintf(id, "%d", k);
                //need to insert each word into index (*word, *id)
                index_insert(index, word, id);
                //may need to null check 
                count_free(word);
            // }
            word = webpage_getNextWord(wp, &i);
        }
        // printf("\n");
        //delete the wp
        webpage_delete(wp);
        //get the next
        wp = bag_extract(webpages);
        //decrement k 
        k--;
    }
    //bag delete 
    //only delete in the evet that it is not null
    assert(webpages != NULL);
    bag_delete(webpages, &webpage_delete);
    assert(len != NULL);
    count_free(len);
    return index;
}
bag_t* directory_parse(char *filedir, int *len){
    //we also want to store all of our webpages in a bag
    bag_t *webpages = bag_new();
    assert(webpages != NULL);
    bag_insert(webpages, NULL);
    // printf("made it past");
    //we can assume that every file in the dir is some /filedir/1, /filedir/2, ... ,and so on 
    //what we want to do is add /2 to the end of /filedir
    char *filepath = count_malloc(100);
    assert(filepath != NULL);
    //copy just the right hand side
    strcpy(filepath, filedir);
    //concatonate
    strcat(filepath, "/1");
    // printf("\n%s\n", filepath);
    //loop over all such files in the dir and stop once we arrive at a file we can't open
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL){
        fprintf(stderr,"There was some error opening the files in the directory");
        return NULL;
    }
    int i = 1;
    while(fp != NULL){
        i++;
        //we did our check so we close the file
        fclose(fp);
        //now we send the file url off to be loaded into a webpage 
        webpage_t *webpage = pageload(filepath);
        if(webpage == NULL){
            fprintf(stderr, "There was an error creating a webpage");
            return NULL;
        }
        //given a clean webpage we can add it to the bag 
        // assert(bag_extract == NULL);
        bag_insert(webpages, webpage);        
        //copy to file path the orignal directory
        strcpy(filepath, filedir);
        //turn the current number into a string 'i'
        char it[50] = "/";
        char buffer[20];
        sprintf(buffer, "%d", i);
        // printf("\n%s\n", buffer);
        strcat(it, buffer);
           
        //concatonate
        strcat(filepath, it);
        assert(filepath != NULL);
        //test whether the file exits 
        fp = fopen(filepath, "r");
    }
    *len = i;
    //at this point either all of the files have been checked or theres been an error but either way irrelabvent
    count_free(filepath);
    return webpages;
}
//need webpage delete function to rid them out of the bag
void deleteitem(void *item){
    //each item should be a counters type
    // printf("\ndeleting...\n");
    if(item != NULL){
        counters_delete(item);
    }
    // return NULL;
}
void deletewebpage(void *item){
    //each item should be a counters type
    // printf("\ndeleting...\n");
    if(item != NULL){
        webpage_delete(item);
    }
}