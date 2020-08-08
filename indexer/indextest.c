

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../common/index.h"


// Process and validate command-line parameters
// Initialize data structure index
// index_build(directory, index)
// index_save(file, index);
// clean up data structures
void deleteitem(void *item);

int main(const int argc, const char *argv[]){
    //TEST 1: Index creation
    index_t *index;
    //successful
    index = index_new(20);
    //TEST 2: Index insertion
    index_insert(index, "thing", "1");
    index_insert(index, "thing", "2");
    index_insert(index, "thing", "2");
    index_insert(index, "nothing", "2");
    //successful

    //TEST 3: Index Save
    FILE *fp = fopen("./test.txt", "w");
    index_save(index, fp);
    fclose(fp);
    //successful

    //TEST 4: Index Delete
    index_delete(index, &deleteitem);
    //succrssful 

    //TEST 5: Save index, load index from saved index, and save it again to verify they are identical 
    fp = fopen("./test.txt", "r");
    index_t *i = index_load(fp);
    fclose(fp);
    fp = fopen("./test2.txt", "w");
    index_save(i, fp);
    fclose(fp);
    index_delete(i, &deleteitem);
    //success

}
//this is our helper delete item method
void deleteitem(void *item){
    //each item should be a counters type
    printf("\ndeleting...\n");
    if(item != NULL){
        counters_delete(item);
    }
    // return NULL;
}
