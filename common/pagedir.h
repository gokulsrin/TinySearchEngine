/* 
 * pagedir - for saving webpages to files and stuff
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