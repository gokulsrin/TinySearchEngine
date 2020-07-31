# CS50 Lab 4
## CS50 Summer 2020

### Pagedir

A `pagedir` is an executable file that contains a method pagesave() which is passed a valid url, depth, content, and id, and writes those parameters to a file specified. 


### Usage

You simply call the functions within pagedir as neccesary.

```c
void pagesave(char * url, int depth, char * content, int id);
```

### Implementation

Again, the only function in pagedir at the moment is pagesave, which has implementation described in the `pagesave.h` file

### Assumptions

The page save function assumes a fixed directory './crawldir'. Thus, without modifying the actual code, the program will always write to this directory. This was due to a misconception I had about the assignment. I thought it asked for files to always be written to a specific directory callec './crawldir'... I understand how strange that sounds but it is the truth. 

### Files

* `Makefile` - compilation procedure
* `pagedir.c` - the implementation
* `pagedir.h` - header file
* `README.md` - readme



### Compilation

To compile, simply `make`.

### Testing

The testing simply runs a predetermined set of test cases designed to test all of the most important features of the program.

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind` -- though unfortunately there are memory errors I am unable to correct.