/* 
 * normalizew_word - for making sure words of < 4 are discarded and words are all put into their lower case forms
 *
 *Gokul Srinivasan - Summer 2020 - CS50
 */

/**************** normalize_word() ****************/
/* Input: pointer to a string
 * We allocate new memory, change the word into its lowercase form, and return a pointer to a different malloc'd
 *block of memory. 
 *The user is responsible for freeing this memory
 */char* normalize_word(char* word);
