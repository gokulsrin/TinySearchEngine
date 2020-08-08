//this is the file that created our index_t data structure 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../libcs50/hashtable.h"
#include "./index.h"
#include "../libcs50/memory.h"
#include "../libcs50/counters.h"
#include "../libcs50/set.h"



typedef struct index{
    hashtable_t *ht;
}index_t;

index_t* index_new(const int size){
    if(size > 0){
        index_t *index = count_malloc(sizeof(index_t));
        //verify that memory allocation happened successfully 
        // if index is null, just print error and return null
        if(index == NULL){
            fprintf(stderr, "The memory allocation for index has failed");
            return NULL;
        }
        index->ht = hashtable_new(size);
        //if the hashtable is null, just rewind everything and free index and print the error and return null
        if(index->ht == NULL){
            fprintf(stderr, "The memory allocation for index->ht has failed, so index will we deleted");
            count_free(index);
            return NULL;
        }
        //if everything went well return the pointer
        // printf("\nSuccess");
        return index;
    }
  return NULL;
}

//here we need to create set at some unique position in the hashtable
//return false and print error if there is some error
bool index_insert(index_t * index, char * word, char * id){
    if(index == NULL || word == NULL || id == NULL){
        fprintf(stderr, "Either index was null, word was null, or id was null");
        return false;
    }
    //determine whether or not the word exists by trying to hash NULL
    bool word_exists = (hashtable_find(index->ht,(const char*)word) != NULL);
    //if the word has not been hashed, meaning the above hash returned false
    if(!word_exists){
        //we need to create counters object and do 
        counters_t *counter = counters_new();
        //if creation fails
        if(counter == NULL){
            fprintf(stderr, "Creation of counters set failed");
            return false;
        }
        //we need to add a a counter to counters that has our page id as the key
        //if the addition fails, free the memory and return false
        if(counters_add(counter, atoi(id)) == 0){
            fprintf(stderr, "Creation of counter failed");
            counters_delete(counter);
            return false;
        }
        //if it works, insert the counter into it's hash position 
        //attempt the insert, if it has failed we need to print that, and free all memory
        bool status = hashtable_insert(index->ht,(const char*)word, counter);
        if(!status){
            fprintf(stderr, "failed hashtable insert");
            counters_delete(counter);
            return false;
        }
    }
    //if the word has been hashed 
    else{
        //find the set in the hashed index, find the counters set, increment the counter of file id
        counters_t *counter = hashtable_find(index->ht, (const char*)word);
        if(counter == NULL){
            fprintf(stderr, "counter is null");
            return false;
        }
        //attempt to icnrement counter, return false if failed, else proceed
        if(counters_add(counter, atoi(id)) == 0){
            fprintf(stderr,"counter addition failed");
            return false;
        }
        
    }
    //testing
    // printf("\nSuccessful Insert\n");
    return true;
}
//we want to obliterate this index, meaning we need to first delete the hashtable, and then free the index pointer
bool index_delete(index_t *index, void (*itemdelete)(void *item)){
    //verify that everything is non-null
    if(index == NULL || itemdelete == NULL){
        fprintf(stderr,"Either the index is null or the itemdelete is null");
        return false;
    }
    //we simply have to assume this works
    hashtable_delete(index->ht, itemdelete);
    //index is non-null so we free it
    count_free(index);
    // printf("\nsuccessfully freed\n");
    return true;
}
//we want to save the index to a file in a specific way such that we can recreate it
//this the format (word docID count docID count ...)
bool index_save(index_t *index, FILE *fp){
    //make sure args are valid
    if(index == NULL || fp == NULL){
        fprintf(stderr, "The index was null or the file pointer was null");
        return false;
    }
    //this should iterate through every set, calling item print, which calls counter_print to print every counter in counters
    hashtable_iterate(index->ht, fp, &item_print);
    return true;
}
//this a helper method to save, with arg being the file and item being the counters set
void item_print(void *arg, const char *key, void *item){
    //check that args are valid
    if(arg == NULL || key == NULL || item == NULL){
        fprintf(stderr, "Error in item_print");
    }
    //print the word with a line skip before it
    fprintf(arg, "\n%s ", key);
    //now we need to print through the counters 
    counters_iterate(item, arg, &counter_print);
}
void counter_print(void *arg, const int key, const int count){
    //check args
    if(arg == NULL){
        fprintf(stderr, "Error in counter_print");
    }    
    //print every counter to the file 
    fprintf(arg, "%d %d ", key, count);
}
//we need to load the output from index save 
index_t* index_load(FILE *fp){
    //check args 
    if(fp == NULL){
        fprintf(stderr, "File points to NULL value");
        return false;
    }
    //create new index and make sure it is valid
    index_t *index = index_new(1000);
    assert(index != NULL);

    //begin to traverse file
    char * str = count_malloc(sizeof(char*));
    //each string is being read one at a time until the EOF is reached 
    // int idx = 0;
    char * key = count_malloc(sizeof(char*));
    while(fscanf(fp, "%s", str)!=EOF){
        // printf("\n%s\n",str);
        //identify if the scanned word is a word or a number, thus the key word or fileid/count
        if(atoi(str) == 0 && str[0] != '0'){
            strcpy(key, str);
        }
        //this is the id/count pair, specifically the word read must be the id
        else{
            //save the id 
            char *id = count_malloc(sizeof(char*));
            assert(id != NULL);
            strcpy(id, str);
            //read the next string until EOF
            if(fscanf(fp, "%s", str) != EOF){
                char *count = count_malloc(sizeof(char*));
                assert(count != NULL);
                strcpy(count, str);
                //so long as key exists and it is non-null, we can begin adding to the counterset identified by key 
                if(key != NULL && index != NULL){
                    //now we simply need to insert (key, fileid) enough times to make the new index match the count
                    int c = 0;
                    while(c < atoi(count)){
                        index_insert(index, key, id);
                        c++;
                    }
                }
                count_free(count);
            }
            count_free(id);
        }
    }
    count_free(str);
    count_free(key);
    return index;
}