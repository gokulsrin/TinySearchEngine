//1. essentially I first want to parse the command line so that I can search a propper index file
//2. I want to read the arguments of the command line and find the words there
//3. I need to account for and/or operators 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "../libcs50/webpage.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"
#include "../common/index.h"


bool process_arguments(const int argc, const char *argv[], char* p, char* i);
bool process_querey(index_t *index, int filenum);
int count_files(char *pageDirectory);
bool score_documents(char *line, index_t *index, int filenum);
bool tokenize_string(char *line, char *words[]);
bool validate_token(char *words[], int query_size);
int orsequence(char *words[], int size, int fileID, index_t *index);
int andsequence(index_t *index, char *words[], int fileID, int pos, int size);
int getscore(index_t *index, char*word, int fileID);

//maybe some confusion here
void deleteitem(void *item);
void deletewebpage(void *item);

int main(const int argc, const char *argv[]){
    char *pageDirectory = count_malloc(sizeof(char*));
    char *indexFilename = count_malloc(sizeof(char*));
    assert(pageDirectory != NULL);
    assert(indexFilename != NULL);
    //verify arguments work;
    if(!process_arguments(argc, argv, pageDirectory, indexFilename)){
        fprintf(stderr, "Invalid initial arguments");
        count_free(pageDirectory);
        count_free(indexFilename);
        return -1;
    }
    //figure out the number of files we are reading across 
    int filenum = count_files(pageDirectory);
    printf("Num files:%d", filenum);
    //load a given index file into an index 
    FILE *fp = fopen(indexFilename, "r");
    index_t *index; 
    index = index_load(fp);
    //test the query stuff
    process_querey(index, filenum);

    fclose(fp);
    index_delete(index, &deleteitem);
    // printf("%s; %s", pageDirectory, indexFilename);


    count_free(pageDirectory);
    count_free(indexFilename);
    return 0;
}

//./querier pageDirectory indexFilename
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
            fprintf(stderr, "Directory (argument 1) does not exist\n");
            return false;
        }
        if (ENOTDIR == errno) {
            // not a directory
            fprintf(stderr, "Argument 1 is not a directory\n");
            return false;
        }
        //is a directory
    }
    //check if the indexFileName is readable
    FILE *fp;
    if( (fp = fopen(i, "r")) == NULL){
        fprintf(stderr, "Failed to read to file specified by argument 2\n");
        return false;
    }
    fclose(fp);
    return true;
}
//here we want to count the number of files inside of the pageDirectory and return that number
int count_files(char *pageDirectory){
    int size = 0;
    //start may be 0 or 1 -- CHECK HERE FOR BUG
    int i = 0;

    //find file id
    char *fileID = count_malloc(sizeof(char*));
    sprintf(fileID, "%d", i);
    assert(fileID != NULL);
    //do the math to concatonate the id with the directory
    char *filename = count_malloc(strlen(pageDirectory) + strlen(fileID) + 1); 
    assert(filename != NULL);
    strcpy(filename,pageDirectory );
    strcat(filename, fileID);
    
    FILE *fp;
    while((fp = fopen(filename, "r")) != NULL){
        size++;
        i++;
        //reallocate
        count_free(fileID);
        fileID = count_malloc(sizeof(char*));
        assert(fileID != NULL);
        sprintf(fileID, "%d", i);
        
        count_free(filename);
        filename = count_malloc(strlen(pageDirectory) + strlen(fileID) + 1); 
        assert(filename != NULL);
        strcpy(filename,pageDirectory );
        strcat(filename, fileID);
    }
    count_free(fileID);
    count_free(filename);
    return size;
}

//here we need to process our users input from stdin 
bool process_querey(index_t *index, int filenum){
    //test here
    // counters_t* counters = index_retrieve(index, "Algorithm");
    // counters_print(counters, stdout);
    //we will save each query into this line 
    char *line;
    //read the first line from stdin
    line = freadlinep(stdin);
    //keep reading until error or eof reached
    while(line != NULL){
        printf("in pq\n");
        score_documents(line, index, filenum);
        //free the memory
        count_free(line);
        line = freadlinep(stdin);
    }
    return true;
}
//here is where the bulk of the logic occours
bool score_documents(char *line, index_t *index, int filenum){
    //first we need to tokenize our string 
    // printf("in sd\n");
    //allocate char **words = calloc();
    char *words[100];
    //initialize array to null
    for(int i = 0; i < 100; i++){
       words[i] = NULL;
    }
    //works
    tokenize_string(line, words);
    //find out the size of the query
    int query_size = 0;
    for(int i = 0; i < 100; i++){
        if(words[i] != NULL){
            printf("%s\n", words[i]);
            query_size++;
        }
    }
    // transfer the words to another words**
    // char **words2 = count_calloc(query_size,sizeof(char*));
    // for(int i = 0; i < query_size; i++){
    //     strcpy(words2[i], words[i]);
    //     // printf("\n%s",)
    // }
    // bool test = strcmp(words2[0], "and") == 0;
    // printf("\nbool test:%d",test);
    //ensure that all of the tokens are valid
    if(validate_token(words, query_size)){
        //first off, we have to run the querey across all of the documents 
        //second, we need to create a score array that essentially determines the score of thr query in each of the documents
        //take some arbitary 
        printf("\nInside here\n");
        //test the logic 
        //we need to run the query for every file...
        int scores[filenum];
        for(int i = 1; i <= filenum; i++){
            int score = orsequence(words, query_size, i, index);
            scores[i-1] = score;
            printf("\nfileID:%d; score:%d",i,scores[i-1]);
        }
        
    }
    //now we need to run the logic
    
    return true;
}
//here we need to take our line and chop them up into individual words and store them into an array 
//just going to over allocate
//also memory for line has already been allocated
bool tokenize_string(char *line, char *words[]){
    int i = 0;
    char *p = strtok(line, " ");
    while(p != NULL) {
        // printf("%s\n", p);
        //copy the string 
        char *word = count_calloc(1,sizeof(char*));
        strcpy(word, p);
        //lowercase the string
        int len = strlen(word);
        for(int i = 0; i < len; i++){
            word[i] = tolower(word[i]);
        }
        //add the copied string to array 
        words[i] = word;
        //retrieve next token
        p = strtok(NULL, " ");
        i++;
    }
    return true;
}
//ensure that there aren't and/ors in the wrong places
bool validate_token(char *words[], int query_size){
    for(int i = 0; i < query_size; i++){
        if(words[i] != NULL){
            //make sure and/or not first 
            if(i == 0 && (strcmp(words[i],"and") == 0 || strcmp(words[i],"or") == 0)){
                fprintf(stderr, "\nInvalid query: and/or in first position\n");
                return false;
            }
            // if(i == 0 && words[i] == NULL){
            //     fprintf(stderr, "Invalid query: please enter input");
            //     return false;
            // }
            //make sure not last
            if(i == query_size && (strcmp(words[i],"and") == 0 || strcmp(words[i],"or") == 0)){
                fprintf(stderr, "\nInvalid query: and/or in last position\n");
                return false;
            }
            //make sure no duplicates
            if((strcmp(words[i-1],"and") == 0 || strcmp(words[i-1],"or") == 0) && (strcmp(words[i],"and") == 0 || strcmp(words[i],"or") == 0)){
                fprintf(stderr, "\nInvalid query: and/or sequentially\n");
                return false;
            }
            //traverse every character in the word and make sure there is no dumb character
            int len = strlen(words[i]);
            for(int j = 0; j < len; j++){
                //if any non alpha char
                if(isalpha(words[i][j]) == 0){
                    fprintf(stderr, "\nInvalid query: extraneous characters\n");
                    return false;
                }
            }
        }
    }
    return true;
}
//this checks how well a given sequences matches a query 
int orsequence(char *words[], int size, int fileID, index_t *index){
    int sum = 0;
   //start at 0, work left to right
    printf("\nInside or sequence\n");
    printf("\nWord:%s", words[0]);
    printf("\nsize:%d", size);

   for(int i = 0; i < size; i++){
       printf("\nor i:%d", i);
        //start the and sequence at index i 
        sum += andsequence(index, words, fileID, i, size);
        //the and sequence ends when an or is encountered, or the end is reached, so we need to push index to the or
        while( i < size && strcmp(words[i], "or") != 0){
            printf("\nInside while");
            i++;
        }
   }
   printf("\n End of or sequence: %d", sum);
   return sum;
}
int andsequence(index_t *index, char *words[], int fileID, int pos, int size){
    //run the and sequence until an or is enountered
    //be careful with the out of bounds stuff 
    //we know the first index always must be a word, so we can set sum = to the score of the first word
        printf("\nInside and sequence\n");

    int sum = getscore(index, words[pos], fileID);
    // printf("\nscore:%d", sum);
    for(int i = pos; i < size; i++){
        //if the current index is neither and nor or, it is a word
        //this is redundant but we'll keep it 
        printf("\ni inside and:%d", i);
       if(strcmp(words[i], "and") != 0 && strcmp(words[i], "or") != 0){
           //retreive score for the word in s1 
            printf("\nInside and: for loop");
            //add an aditional check concering whether words[i] is the last word
            if(i < size - 2){            
                //case 1: w1 and w2
                //we treat score of w1 as the sum, and we neet to retrieve w2
                if(strcmp(words[i+1], "and") == 0){
                    //score of word at pos i+2
                    int w2 = getscore(index, words[i+2], fileID);
                    //get the minimum
                    if(w2 < sum){
                        sum = w2;
                    }
                    //we need to move i up to spot, but loop will iterate so only add 1 to i i+2
                    i++;
                }
                //case 2: w1 w2 
                else if(strcmp(words[i+1], "and") != 0 && strcmp(words[i+1], "or") != 0){
                    //in pos i+1
                    int w2 = getscore(index, words[i+1], fileID);
                    //get the minimum
                    if(w2 < sum){
                        sum = w2;
                    }
                }
                //case 3: w1 or ...
                else if(strcmp(words[i+1], "or") == 0){
                    //we simply return our accumulated sum 
                    return sum;
                }
            }
            //an aditional check concering whether words[i] is the last word
            else if (i < size - 1){
                //case 2: w1 w2 
                if(strcmp(words[i+1], "and") != 0 && strcmp(words[i+1], "or") != 0){
                    //in pos i+1
                    int w2 = getscore(index, words[i+1], fileID);
                    //get the minimum
                    if(w2 < sum){
                        sum = w2;
                    }
                }
                //case 3: w1 or ...
                else if(strcmp(words[i+1], "or") == 0){
                    //we simply return our accumulated sum 
                    return sum;
                }
            }
            //when words[i] is the last word
            else if(i == size -1){
                printf("\ninside i = size -1");
                int w2 = getscore(index, words[i], fileID);
                printf("\nw2:%d", w2);
                printf("\nsum:%d", sum);

                //get the minimum
                if(w2 < sum){
                    printf("\nhello1");

                    sum = w2;
                }
                printf("\nhello2");
                // printf("\nsum:%d", sum);
                return sum;
            }
       }
    }
    printf("\nreached end");

    //if we reach here we've failed somewhere
    return -1;
}
//to make getting score easier
int getscore(index_t *index, char*word, int fileID){
    // printf("\n Inside score\n");
    if(index == NULL || word == NULL || fileID < 0){
        fprintf(stderr, "Failure to getscore");
        return -1;
    }
    int score = 0; 
    //get counters set
    counters_t *counters = index_retrieve(index, word);
    // counters_print(counters, stdout);
    //get the counter of specific fileID
    score = counters_get(counters, (const int)fileID);
    printf("\nScore:%d", score);
    return score;
}

//need delete index function
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