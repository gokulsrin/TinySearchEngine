# CS50 Lab 4
## CS50 Summer 2020

### Crawler

A `indexer` is an executable file that, when passed a valid webpageDirectory and indexFilePath will take the results of crawler in a directory specified by webpageDirectory and create an inverted index and write that index to the file specificed by indexFilePath.

The `indexer` progressivley adds to its infrastructure, taking more memory as it proceeds. 

The `indexer` will create files the that user must ultimately delete.

### Usage

The *indexer* executable, defined mainly in `DESIGN.md and IMPLEMENTATION.md` and implemented in `indexer.c`, implements various functions to traverse directories, load webpages, and build indicies. 

```c
int main(const int argc, const char *argv[]);
bool process_arguments(const int argc, const char *argv[], char* p, char* i);
index_t* index_build(char *filedir, int size);
bag_t* directory_parse(char *filedir, int *len);
void deleteitem(void *item);
void deletewebpage(void *item);
```

### Implementation

See `IMPLEMENTATION.md` for the specific implementation details.

### Assumptions

No assumptions beyond those outlined in the design and implementation specs have been made. 

### Files

* `Makefile` - compilation procedure
* `indexer.c` - the implementation
* `indextest.c` - the testing file for the suite of index functions
* `testing.sh` - testing script
* `testing.out` - recorded test output
* `DESIGN.md` - design spec
* `IMPLEMENTATION.md` - implementation spec
* `REQUIREMENTS.md` - requirement spec

### Compilation

To compile, simply `make`.

### Testing

The testing simply runs a predetermined set of test cases designed to test all of the most important features of the program.

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind` -- though unfortunately there are memory errors I am unable to correct.