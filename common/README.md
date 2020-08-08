# CS50 Lab 4
## CS50 Summer 2020

### Pagedir

A `pagedir` is an executable file that contains a method pagesave() which is passed a valid url, depth, content, and id, and writes those parameters to a file specified. 

### Index

A `Index` is an data structure that maps words to (id, count) pairs. It takes in any number of words and file ids to construct this mapping. It is fundamentally a hashtable of counter items. 

### Word 

A `Word` is an executable file that contains the function normalize_word, which, when passed a multivariate string will return an all lower-case string. This function is about (80%) functional, but not completely. You can verify that for yourself. 

### Usage

You simply call the functions within pagedir as neccesary.

You simply call all of the index API's functions as neccesary.

You simply call all of the Word API's functions as necessary.

## Pagedir
```c
void pagesave(char * url, int depth, char * content, int id);
webpage_t* pageload(char *filename);
```
## Index
```c
typedef struct index index_t; 
index_t* index_new(const int size);
bool index_insert(index_t * index, char * word, char * id);
bool index_delete(index_t *index, void (*itemdelete)(void *item));
bool index_save(index_t *index, FILE *fp);
void item_print(void *arg, const char *key, void *item);
void counter_print(void *arg, const int key, const int count);
index_t* index_load(FILE *fp);
```

## Word
```c
char* normalize_word(char* word);
```
### Implementation

In Pagedir, pagesave has an implementation described in the`pagedir.h` file. Pageload has a fairly simple implementation. Scan the first two lines of a valid file and treat these as the url and depth respectively. Construct a webpage using these values. 

In Index, the implementations of each of the methods is described in more detail within the file itself. 

In Word, the implementation of each of the methods is described within the file itself.

### Assumptions

Not an assumption, but a remark regarding normalize_word's behavior. Normalize word does both reject words < 3 characters long and turn all words into lower case, the problem is that it included non-alphabetic characters that prove troublesome in their own right. For this reason I've chosen not to use normalize-word, though it is a semi-functional module. 

The assumptions made for index have been made per the requirement spec. No further assumptions were made. 


### Files

* `Makefile` - compilation procedure
* `pagedir.c` - the implementation
* `pagedir.h` - header file
* `index.c` - the implementation
* `index.h` - header file
* `word.h` - the implementation
* `word.h` - header file
* `README.md` - readme



### Compilation

To compile, simply `make`.

### Testing

The testing simply runs a predetermined set of test cases designed to test all of the most important features of the program.

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind` -- though unfortunately there are memory errors I am unable to correct.