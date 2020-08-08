# TSE Indexer Design Spec

For specific requirements please see the indexer `requirements.md` file; the **Indexer**, provided a valid directory contained crawled webpages, and a file to store output, will take each of the webpages crawled by crawler and build an inverted index, wherin each word will map to a distinct counters set, where the the file that word appeared in, and the number of times that word appeared in said file are recorded. 

It parses all of the saved webpages in a provided directory, given that all of the pages are formatted correctly. From each file, a webpage is loaded, and from the webpage the text is extracted and inserted into our inverted index. 

After this process is complete, the index saved to a file, and can be loaded for further use. 

### User interface

The indexer has only a command line interface where two arguments are necessary.
```
./indexer webpageDirectory indexFilePath 
```

For example:

``` bash
$ ./indexer ../crawler/crawldir ./test2.txt
```

### Inputs and outputs

Input: the only inputs are command-line parameters.

Output: We construct and inverted index and save the index to a file specified by `indexFilePath`.
 * [word] [fileID] [count] ... 

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules
 2. *index_build*, which builds the index
 3. *process_arguments*, which parses the arguments given in the command line
 4. *directory_parse*, which sorts through the directory of webpages
 5. *deleteitem*, which deletes all of the items 
 6. *deletewebpage*, which deletes all of the webpages

And in index we anticipate the following modules or functions: 
1. *index_new*, create an inverted index
2. *index_save*, save the index to a file
3. *index_delete*, delete the index
4. *index_insert*, insert a word and (fileID, wordOccourance) pair into the index. 
5. *index_print*, print the index
6. *index_load*, load the index from its saved form

We also need to load webpages so we should exect some modules or functions:
1. *webpageload*, given a crawled webpage, recreate the webpage data structure. 

And some helper modules that provide data structures:

 1. *bag* of webpages.
 2. *hashtable* is the backbone of the index where each item is a counters struct.
 3. *set* because, well, I don't remember.
 4. *webpage* because we need to sort through the text in a webpage.
 5. *counters* to store each (fileId, word count) pair.  

### Pseudo code for logic/algorithmic flow

The indexer will run as follows:

1. execute from a command line as shown in the User Interface
2. process arguments and make sure they are valid 
3. Build the index 
    4. iterate through directory of crawled webpages
    5. for each webpage, load a webpage_t struct
    6. Add all of these structs to a bag containing all of the loaded webpages
    7. Iterate through each word in every webpage, adding the word, the file from which it came, and the frequency of the word's occurance to the index
8. Verify the index was properly constructed 
9. Save the index



### Dataflow through modules

 1. *main* sends parameters to have them parsed, builds the index, and saves the index
 2. *process_arguments* take the arguments sent from main, copy them into the pointers sent, and make sure that they are good else return false. 
 3. *index_build* called from main, take the webpage directory and the number of slots wanted in the index and craft the index by calling first directory parse, and then taking the bag returned from that and iterating through every webpage, adding the words to the index
 4. *directory_parse* Load every webpage in the directory and add it to a bag retured to index_build

### Major data structures

Three helper modules provide data structures:

 1. *bag* of webpage (URL, depth) structures
 2. *set* of URLs (indirectly used by hashtable)
 4. *hashtable* used by Index

### Testing plan

*Unit testing*.
For the most part, unit testing is done in indextest. 

1. Test creation of the index
2. Test addition of information to the index
3. Test the printing of information 
4. Test the deletion of index
5. Test an index being loaded
6. Test the index being saved

*Integration testing*.  
Integration testing is conducted in testing.sh where each of the major error cases are considered;

1. Results of output from running the indexer on the information provided on the lab_5 webpage 
