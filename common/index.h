/*header file for index.c 
I think that there need to be a few methods 
1) index_new: create a new index_t struct 
2) index_insert: insert a word and webpage id so that the appropriate counters can be incremented 
3) index_delete: delete the index_t struct
4) index_save : save an index to a file 
    4.1 item_print: function passed to hashtable_iterate prints the key in each slot
    4.2 counter_print: function passed to counters_iterate, prints the (counter, count) pairs
5) index_load: load an index from a file of saved index 
*/
#include <stdio.h>
#include <stdlib.h>

//this is our data struct
typedef struct index index_t;

//index new 
/**************** index_new ****************/
/* Input: a valid hashtable size
*1. We construct an index_t struct with hashtable of size = size. 
*2. We make sure the memory allocated is valid or we return null
*3. We also return null if invalid size
*4. User is responsible for freeing memory
 */
index_t* index_new(const int size);

//index insert(pointer to index, word, file id)
/**************** index_insert ****************/
/* Input: index pointer, word, file_ID
 * 1. We hash the word and add to the position the counter containing the ID
 *2. If any of the parameters are invalid, we return false. Otherwise return true.
 */
bool index_insert(index_t * index, char * word, char * id);

//index delete
/**************** index_delete ****************/
/* Input: index ptr, function ptr.
* 1. We delete an index provided a valid reference to an index and delete function
* 2. Else, we return false and do nothing
*3. Return false if there is some other error
 */
bool index_delete(index_t *index, void (*itemdelete)(void *item));

//index save
//we should save index to the file given
/**************** index_save ****************/
/* Input: index ptr, file ptr.
 *1. We save the file given valid index and file pointers
 *2. Invalid arguments return false
 *3. If anything goes wrong return false.
 */
bool index_save(index_t *index, FILE *fp);

//print the key
/**************** item_print ****************/
/* Input: an argument (file pointer to print to), key (word), and item
 * This is a helper function to our index save function. We print every word, and call counter print
 * on every item or counterset. That is we print the key in (key, item), and we call counter_print to print
 * all of the counters in counter_set. 
 */
void item_print(void *arg, const char *key, void *item);

//print the (counter_id, count) pairs
/**************** counter_print ****************/
/* Input: an argument (file pointer to print to), key (file ID), and count
 * We print all of the counters in counter_set as [key] [count] pairs
 */
void counter_print(void *arg, const int key, const int count);

/**************** index_load ****************/
/* Input: a file pointer
 * The index is loaded from a file provided by index save. 
 * A non-NULL file pointer must be provided, else we return false. 
 */
index_t* index_load(FILE *fp);

/**************** index_retrieve ****************/
/* Input: a valid key
 * return the counters object
 */
void* index_retrieve(index_t *index, char *key);