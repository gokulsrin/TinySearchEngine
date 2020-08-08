# CS50 Lab 4
## CS50 Summer 2020

<!-- Need to include the following: 

Detailed pseudo code for each of the objects/components/functions,
Definition of detailed APIs, interfaces, function prototypes and their parameters,
Data structures (e.g., struct names and members),
Security and privacy properties,
Error handling and recovery,
Resource management,
Persistant storage (files, database, etc). -->

### Functions & Interfaces
There are three functions being used in my code. Namely: 

```c
int main(const int argc, const char *argv[]);
bool process_arguments(const int argc, const char *argv[], char* p, char* i);
index_t* index_build(char *filedir, int size);
bag_t* directory_parse(char *filedir, int *len);
void deleteitem(void *item);
void deletewebpage(void *item);

index_t* index_new(const int size);
bool index_insert(index_t * index, char * word, char * id);
bool index_delete(index_t *index, void (*itemdelete)(void *item));
bool index_save(index_t *index, FILE *fp);
void item_print(void *arg, const char *key, void *item);
void counter_print(void *arg, const int key, const int count);
index_t* index_load(FILE *fp);

```
Within the main function, I do call two main functions that do the bulk of the work: 1) process_arguments and 2) index_build. These functions then call a host of other functions, some defined in indexer.c and most others belonging to the API index.h

```c
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
#include "../common/pagedir.h"
```

Some of these files are not often used (i.e. <stdlib.h> or "unistd.h"), but I use the bag, memory, hashtable pagedir, and index.h module extensively. The most frequent API calls are indeed calls to index.h and pagedir.h where, as stated above, the bulk of the logic exists.

The `pagedir` module allows for a file to be written into when given a valid url, depth, html content, and file id. Some more of the specifics will be discussed in `pagedir.h`, but the module functions to write our webpage content into a file. The pagedir method also contains our pageload() function that creates a webpages struct from a saved webpage, proceeding through all of the words contained within the document.

```c
webpage_t* pageload(char * filepath); 
```
### Implementation Psuedocode

Again the bulk of the psuedocode exists in index_build which needs to operate as follows:

1. Traverse the directory containing stored webpages
2. For each file, create a webpage and add that webpage to a bag
3. Once the bag is created, iterate trhough every webpage in the bag
	4. For each webpage, iterate through every word in the webpage
	5. For each word that passes the minimum constraints, insert the word and the fileID into the index 
	6. Make sure, through this entire process that all logic checks are enforced

The psuedocode for directory_parse is as follows:

1. Assume every file in directory is labeled correctly 
2. While there is another file in the directory, proceed 
	3. For each file, store the first two lines of the file as url and depth 
	4. Create a webpage with that information
	5. Add  webpage to the bag of files
6. Return bag 


### Data Structures

The index struct consists of nothing but a hashhtabe with (word, counter_set) pairs. Each counter_set contains counters with (fileID, # of occurances) within it. Each time a word is added with a fileID matching some already in the table, that specific counter is incremented. 

Other than that, a bag is used to store all of the loaded webpages in directory_parse. 

### Error Handeling

Again, there are many assert() and if(NULL) checks throughout the code, ensuring that all memory created, deleated or altered is done so correctly. If these checks are not passe, usually a message is printed to stderr and a return is executed. 

### Resource Management

All of the mallocs conducted in this project have corresponding frees. 

### File Storage 

File [indexFilePath] has traditionally been "testx.txt" within the same directory, but there are really no restrictions on where you are allowed to place these things. 


### Testing

Again, the testing for indexer, given that it is command line, is conducted in the testing.sh script 

Broadly testing is spread over 3 categories 

1. Proper input, different test cases
2. Mixed input, different test cases
3. Entirely incorrect input, different test cases


