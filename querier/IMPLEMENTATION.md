# CS50 Lab 6
## CS50 Summer 2020


### Functions & Interfaces

Truth be told, I envision my querier function to be quite extravagant with it's use of functions. At the minimum, there needs to be a function to process intitial arguments, process queries, tokenize queries, count the number of files in a document, score each query, and chec, which files satisfy a particular query. Aside from this files may be needed to assist with clean up and specific logical operations. 

```c
bool process_arguments(const int argc, const char *argv[], char* p, char* i);
bool process_querey(index_t *index, int filenum, char *pageDirectory);
int count_files(char *pageDirectory);
bool score_documents(char *line, index_t *index, int filenum, char *pageDirectory);
bool tokenize_string(char *line, char *words[]);
bool validate_token(char *words[], int query_size);
int orsequence(char *words[], int size, int fileID, index_t *index);
bool satisfies_or(char *words[], int size, int fileID, index_t *index);
int andsequence(index_t *index, char *words[], int fileID, int pos, int size);
bool satisfies_and(index_t *index, char *words[], int fileID, int pos, int size);
int getscore(index_t *index, char*word, int fileID);
int * rankpages(int scores[], bool satisfies [], int size);
int cmpfunc (const void * a, const void * b);
char* geturl(char* pageDirectory, int ID);
void deleteitem(void *item);
void deletewebpage(void *item);
int main(const int argc, const char *argv[]);
```

The bulk of the work in this program centers around string manipulation, array creation, and boolean logic/arithmetic. As such, standard libraries like `<stdio.h>`, `<stdlib.h>` , and `<string.h>` were used. Obviously `<stdbool.h>` was also used. Because asseertions were spread throughout the code, `<assert.h>` was also necessary. The other standard libraries were more supplemental and saw little use. Memory, file opening/closing, creation of webpages, use of counters, hashtables, and indicies were also present, hence the other inclusions. Lastly, indicies were loaded, hence index.h, and pagedir is necessary as it contains webpage_load for retreiving the url of a specific file. 

```c
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
#include "../libcs50/bag.h"
#include "../common/index.h"
#include "../common/pagedir.h"
```

Because we will be loading a webpage from the pageDirectory provided in order to find it's url, `pageload` is necessary. Further, we will need to search a counters object to find how many times a particular word occours in a file, hence `counters_get`. Lastly, we will need to retreive from an index a set of counters, for every word, hence `index_retrieve`. 

```c
webpage_t* pageload(char * filepath); 
int counters_get(counters_t *ctrs, const int key);
void* index_retrieve(index_t *index, char *key);
```
### Implementation Psuedocode

Parse initial arguments and verify that the pageDirectory and the indexFileName exist, in addition figure out how many files are in pageDirectory. 
Functions Used: `process_arguments` `count_files`


We will then need to verify every query and parse the queries themselves.
Functions Used: `process_querey` `tokenize_string` `validate_token`
1. Call `strtok` on the query string with space as a delimiter until all of the words have been seperated, and copied into malloc'd char*'s. Once this is done, store them in an array. 
2. Iterate through the array making sure that there are no cases that violate those outlined in `REQUIREMENTS.md`.


We will score each query across one single file, and then iterate across all files:
Functions Used: `score_documents` `orsequence` `andsequence`
1. Begin attempting to score an orsequence 
2. Within the orsequence, call the andsequence, letting it run until it encounters and 'or', or reachers the end of the query
	3. Within the andsequence, we will need to accumulate the score between some (left, right) pair. 
	4. We can begin by setting the sum equal to the score of the first word, then comparing it to the word in front of it, or infront of the and in front of it, or, if there is an or, simply returning the score. 
	5. From there, we can take the minimum of (sum and w2), and continually update sum, each time progressing the index to the word just infront of the and or the current index. 
	6. Return the sum once we enocunter the end of the query or an or 
7. Add the sum to the running sum
8. Leap just past the 'or' where the andsequence exited, and call the andsequence once again, or, if the end of the query is reached, return sum.

We will need to calculate whether a query is satisfied within a specific file, to determine whether to include it in our final search:
Functions Used: `satisfies_or` `satisfies_and`
1. Run the procedure described with 'orsequences' and 'andsequences', but this time keep a accumulated boolean within the andsequence, where the boolean is constantly compared to the next word using an and statement (sum = sum && w2), and keep an accumulated boolean within the orstatement, where the accumulated boolean is constantly compared to the one returned by andsequence. 
2. The process repeats according to the conditions described above 

Once we have knowledge of both which files satisfy the query, and the query score for each file, we are able to take the subset of files that satisfy the query, and sort their respective scores. 
Functions Used: `rankpages` 
1. Within rank pages, we pass an array containing the score of every file, and have that file sorted per c's default qsort method.

From here, we simply display these scores with additional information. 


### Data Structures

There are mainly arrays in use for the vast majority of the operations that occur. Obviously an index structure is needed, and a webpage is also needed, but no counters are used besides to calculate the score of a particular word in a file. 

### Error Handeling

Again, there are many assert() and if(NULL) checks throughout the code, ensuring that all memory created, deleated or altered is done so correctly. If these checks are not passe, usually a message is printed to stderr and a return is executed. Ultimatley, there are actually memory errors, and memory still reachable errors at the end. In fact, there are numerous errors that occour, but no blatant memory leaks. I hope that the grading in this regard will be fair, however, as despite their existance, most have to do with strcpy and specific malloc quantities, and do not affect the programs functionality. 

### Resource Management

All of the mallocs conducted in this project have corresponding frees. I swear this is true, despite the fact that valgrind claims I have malloc'd more than I have free'd. I have systematically checked all of my malloc's and assigned them corresponding frees. 

### File Storage 

So there are some files that are critical and will be written to no matter what. Running make test should write all output to `testing.out`. Similarly, it is assumed that the `pathDirectory` and the `indexFileName` provided are all correct. 


### Testing

I chose not to use fuzz testing because it was giving me persistant segmentation errors. Thus I just opted for traditional regression testing. 

Broadly, testing is spread over two categories

1. Various types of incorrect usage cases
2. Various types of correct usage cases, making it a point to vary syntactic structure

I will detail the specific tests more in the `testing.sh` file, but the gist is that we want to know how the program responds to errors, as well as how it responds to working test cases. 


