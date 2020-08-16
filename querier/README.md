# CS50 Lab 6
## CS50 Summer 2020

PLEASE READ THIS BEFORE YOU GRADE! THERE ARE ACTUALLY SOME IMPORTANT NOTES
### Querier

A `querier` is a program that will, given a valid set of inputs and queries, return the documents that best match the query, and their respective scores. 

A `querier` is limited by the crawlder directory and index file provided to it. That is, if there is any discrepancy between these things, that is a mismatch with directory and index file, or vice versa, there will be many unintended consequences that I have not checked for. 

Broadly speaking, however, my `querier` works perfectly fine, and has an implementation distinct from that persrcibed in the lab. As such, I will attempt to outline my thoughts thoroughly in `design.md`, `implementation.md`, and my comments. The most succinct form of my thoughts can be found in `design.md`, and will be expanded upon in `implementation.md`. 

### Usage
THE FOLLOWING IS CRITICAL; PLEASE NOTE.

To use querier properly, please ensure that the first argument [pageDirectory] has a '/' following its name. Failure to do so will result in many negative downstream consequences. So, please, follow this format when conducting tests. 

```bash
./querier ./pageDirectory/ ./indexFileName
```

### Implementation

See `IMPLEMENTATION.md` for the specific implementation details. For your reading convenience, however, I'll surmise the specifics here. 

Wheras the lab specifies counters and such to be used to store and conduct many of the core logical operations (scoring and the like), I did not use counters. Instead, I used a simply array that contained the scores for each query across every file: int array[numfiles]. I also used an array that tracked whether or not a query was satisfied by a specific file: bool array[numfiles]. Combining these two arrays, I was able to extract the fileID's and scores of the files which statisfied the query, place these into an array, sort the array, and spit them out to the user, with all of the relevant details. 


### Assumptions

No assumptions beyond those outlined in the design and implementation specs, and above in usage, have been made. 

### Files
THE FOLLOWING IS ALSO CRITICAL; PLEASE NOTE. 

* `Makefile` - compilation procedure
* `fuzzquery.c` - the implementation
* `querier.c` - the testing file for the suite of index functions
* `testing/crawldir/` - this folder contains all of the testing material neccesary for me to conduct my testing.sh. Please not that I am not horsing around and negligently including extra files. This is truly necessary for my testing in testing.sh -- it contains all of the crawled files. 
* `testing/output.txt` - this is the index file resulting from the cralwler at depth 6 provided on the course webpage. I repeat, this is crucial in my testing, and is not something added lightly. 
* `testing.sh` - testing script
* `testing.out` - recorded test output
* `DESIGN.md` - design spec
* `IMPLEMENTATION.md` - implementation spec
* `REQUIREMENTS.md` - requirement spec

### Compilation

To compile, simply `make`.

### Testing
THE FOLLOWING IS ALSO CRITICAL; PLEASE NOTE. 

My regression testing runs a series of hard coded test cases, broadly split into one of two categories 
    1. Tests that check the error handaling capacity of the program 
    2. Tests that check the functionality of the program provided valid input

In this process, there is some confusion that may arise for you, my dear reader, so I seek to clarify that before hand. Note that there are 3 files inside of my crawldir (1-3). Note further, that the index file I use has all 8 files denoted within it. As such, my querier implcitly restricts the scoring of each query to only those files included within crawldir. As such, you may see a test that you feel, should include a fileID: 8 in the end scoring, or a fileID: 7 and so forth, but remeber that because these files are not in crawldir they are not being tested for. 

With all of this said, when you run your own set of tests with a valid crawldir and a valid indexFileName, these problems will resolve themselves. Please contact me if there is any confusion with what I have said. 

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind` -- though unfortunately there are memory errors I am unable to correct.