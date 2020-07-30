# CS50 Lab 4
## CS50 Summer 2020

### Crawler

A `crawler` is an executable file that, when passed a valid url, directory, and maxDepth, will traverse the web for pages and store them. 
The `crawler` progressivley traverses the internet, adding and storing files to a directory as it goes.

The `crawler` will create files the that user must ultimatley delete.

### Usage

The *crawler* executable, defined mainly in `DESIGN.md and IMPLEMENTATION.md` and implemented in `crawler.c`, implements various functions to traverse and store webpages; namely, the following functions and modules.

```c
int main(const int argc, const char *argv[]){
void crawl(char *su, char *pd, const int md);
void stringdelete(void *arg, const char *key, void *item);
```

### Implementation

See `IMPLEMENTATION.md` for the specific implementation details.

### Assumptions

No assumptions beyond those outlined in the design and implementation specs have been made. 

### Files

* `Makefile` - compilation procedure
* `crawler.c` - the implementation
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