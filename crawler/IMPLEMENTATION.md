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
int main(const int argc, const char *argv[]){
void crawl(char *su, char *pd, const int md);
void stringdelete(void *arg, const char *key, void *item);
```
Within the main function, I seek to take the command line arguments from the user, verify their accuracy, and call the crawl function where the bulk of the logic lies. It is important to note that many imporant modules are invoked outside of the cralwer.c file. Mainly:

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../libcs50/bag.h"
#include "../libcs50/memory.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../common/pagedir.h"
#include "unistd.h"
```

Some of these files are not often used (i.e. <stdlib.h> or "unistd.h"), but I use the bag, memory, hashtable nad pagedir module extensively. On that note, we will have to discuss the pagedir module further and describe in more detail what it does. 

The `pagedir` module allows for a file to be written into when given a valid url, depth, html content, and file id. Some more of the specifics will be discussed in `pagedir.h`, but the module functions to write our webpage content into a file.

```c
void pagesave(char * url, int depth, char * content, int id); 
```
As a said above, the crawl function has psuedocode detailed in `DESIGN.md`, but I will repeat it here: 
The crawler will run as follows:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. make a *webpage* for the `seedURL`, marked with depth=0
4. add that page to the *bag* of webpages to crawl
5. add that URL to the *hashtable* of URLs seen
3. while there are more webpages to crawl,
	5. extract a webpage (URL,depth) item from the *bag* of webpages to be crawled,
	4. pause for at least one second,
	6. use *pagefetcher* to retrieve the HTML for the page at that URL,
	5. use *pagesaver* to write the webpage to the `pageDirectory` with a unique document ID, as described in the Requirements.
	6. if the webpage depth is < `maxDepth`, explore the webpage to find links:
		7. use *pagescanner* to parse the webpage to extract all its embedded URLs;
		7. for each extracted URL,
			8. 'normalize' the URL (see below)
			9. if that URL is not 'internal' (see below), ignore it;
			9. try to insert that URL into the *hashtable* of URLs seen
				10. if it was already in the table, do nothing;
				11. if it was added to the table,
					12. make a new *webpage* for that URL, at depth+1
					13. add the new webpage to the *bag* of webpages to be crawled

The above was precisley the way the crawl function was implemented, where pagesaver is a function in the `pagedir` module. 

Lastly, `stringdelete` iterates through the hashtable by calling the hashtable_iterate function and deletes each of the key values in the table. Just to be clear, I tried to no avail finding a way to delete the items in the table as well, given that some were allocated, and I could not. From free to count_free, I tried a number of methods that did not work. 

### Implementation Psuedocode
 The main method needed to do the following: 

 1. collect user arguments 
 2. check validity of the arguments and pass them to a crawl function 

The crawl method is specified above. 

The stringdelete method needed to do the following: 

1. Take a void *item and free the item if it was indeed pointing to something 

### Data Structures

As specified in `DESIGN.md`, I used only a hashtable and a bag to do most of the relavent orginization needed for the lab. In total, I used one hashtable and one bag. I make it a point to free these structures at the endd of my code, though, again, I was unable to free all of the items within them first because of a strange recurring core dump error. I promise you that these valgrind errors are not from a lack of trying, but a genuine inability to locate the crux of the problem. 

### Error Handeling

Error checks are run in `int main`, `void crawl`, and `void pagesave`. 

Within main, I make sure to check that that there are 3 arguments, and each of the arguments is non-NULL. Further, there is a test to make sure that the page directory passed is a valid and accessible directory. It would also be prudent of me to describe the return statuses: 

0. If the program returns with a 0, it has executed successfully
1. If the program returns with a 1, there are insufficient parameters passed 
2. If the program returns with a 2, the parameters provided are themselves invalid
3. If the program returns with a 3, the creation of a webpage object has failed

Other errors are detailed with their own perror messages. 

Crawl runs a series of tests throughout its implementation ensuring that allocated data returns non-NULL memory, and objects are created successfully.

Lastly pagesave tests to ensure that the parameters passed to it are non-NULL and valid. 


### Resource Management

As much as possible, every malloc that was used was freed, but there are some that I simply could not figure out how to free for the life of me. To my credit, outside of these errors, the program is not incredibly inefficient, and memory and computation is used sparingly. 

### File Storage 

Files produced by running the program with valid parameters are stored in the `./crawldir/` directory that I have made, but the program will in theory work with any valid directory. 

### Testing

My testing scheme has been devised as follows:

1. Test invalid parameters
2. Test partially valid partially invalid parameters
3. Test boundary cases


