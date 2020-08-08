/* 
 * pagedir - for saving and loading webpages to files and stuff
 *
 *Gokul Srinivasan - Summer 2020 - CS50
 */


/**************** pagesave ****************/
/*  //want to create a page writing function 
//  1. The page URL on the first line,
//  2. the depth of the page (where the seed is depth 0) on the second line,
//  3. the page contents, beginning on the third line.
//save the file to a unique file ID
* Usage: char *string = "hello";
        int depth = 1;
        char *content = "content";
        int id = 4;
        pagesave(string, depth, ontent, id);
 */
void pagesave(char * url, int depth, char * content, int id);
/**************** pageload ****************/
/* Input: a file path
 * 1. We attempt to load the webpage_t file based on the files first and second lines
 * which should correspond to the url and the depth.
 2. We handle null pointer, and other complications, but assume that the file is formatted properly. 
 3. The user will later be responsible for freeing the memory allocated
 */
webpage_t* pageload(char *filename);