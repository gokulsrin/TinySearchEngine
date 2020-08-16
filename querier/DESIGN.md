# TSE Querier Design Spec

For specific requirements please see the querier `requirements.md` file; the **Querier**, provided a valid directory containing crawled webpages, and an indexFileName, will allow the user to enter queries, and output which files best output each query, if any. 

Using a reconstructed index from the indexFileName, and the number of files within the pageDirectory, the querier is able to determine the score of each query for each respective file, check whether that file satisfies the query at all, and combine this information to provide valid output to the user. 

The user is able to enter queries until they decide to quit and press ctrl + c. 

### User interface

The querier has only a command line interface where two arguments are necessary. Not the slash after argument 1. This is critical.

```bash
./querier webpageDirectory/ indexFilePath 
```

For example:

``` bash
$ ./querier ./tesing/crawldir/ ./testing/output.txt
```
This is a case used within `testing.sh`itself.

### Inputs and outputs

Input: the only inputs are command-line parameters.

Output: We provide output to stdout detailing which of the files provided in pageDirectory best satisfy the query submitted. 


### Functional decomposition into modules

We anticipate the following modules or functions:

*process_arguments*, process command-line args 
*count_files*, determine the number of files in pageDirectory
*tokenize_string*, take the user query and turn it into an array of words
*validate_token*, ensure the tokens created meet the requirements
*process_querey*, process user query 
*score_documents*, determine the score for a particular query given a particular document
*orsequence*, traverse the query, adding the number returned from *andsequence* to the sum
*satisfies_or*, traverse the query, adding the boolean returned from *satisfies_and* to the boolean
*andsequence*, traverse the query, accumulating the minimum score between some current sum and some next word
*satisfies_and*,traverse the query, accumulating the boolean value of the accumulated boolean && next_word_boolean
*getscore*, get the score of a particular word given a particular file
*rankpages*, sort the scores for each file in descending order
*cmpfunc*, comparator for *qsort* in c
*geturl*, return the url of a specific file in pageDirectory
*deleteitem*, delete our index_t * structs
*deletewebpage*, delete our webpage_t * structs 

*main*, call the functions above sequentially

We also need to load indicies hence:
1. *index_load*, load the index from its saved form

We also need to load webpages so we should exect some modules or functions:
2. *webpageload*, given a crawled webpage, recreate the webpage data structure. 

And some helper modules that provide data structures:

3. *webpage* because we need to load a specific file and retrieve its url to display to the user
4. *counters* because they store the score for each {fileID, score} pair 

### Pseudo code for logic/algorithmic flow

The querier will run as follows:

1. execute from a command line as shown in the User Interface
2. process arguments and make sure they are valid 
3. process a query from stdin
    4. tokenize the query 
    5. ensure that the query is valid based on its tokens 
    6. score each of the files based on the query 
        7. take the sum with orsequence 
            8. take the sum with andsequence 
    9. determine which files satisfy the query 
        10. find the boolean with satisfies_or
            11. find the boolean with satisfies_and
    12. sort the scores of the files which satisfy the query in descending order
    13. Output these scores to the user, and continue repeating (3-13) until user quits 


### Dataflow through modules

 1. *main* sends parameters to have them parsed, builds the index, and saves the index
 2. *process_query* takes each query, has them tokenized in *tokenize_string* and validated in *validate_token*
 3. Each of the files is scored according to the query *score_documents* by being passed to *orsequence* and in turn to *andsequence*
 4. Each of the files is determined to satisfy the file in *score_documents* by being passed to *satisfies_or* and in turn to *satisfies_and*
 5. Output is generated
 

### Major data structures

Ararys for the backbone of my project. Particulary the: char *words[]. This array contains all of the tokenized words, and is passed between many functions, and is, without doubt, the most critcal data structure in my project. I'll be the first to admit, the run time of my code may be quicker if I had chosen to use more complex strucures, but because I don't feel that comfortable in c, I opted not to. 

### Testing plan


*Integration/regression testing*.  
Integration testing is conducted in testing.sh.

Broadly, the testing seeks to check the error handling capabilities of querier as well as its functionality. More about this in the README.md and in IMPLEMENTATION.md. 

BUT, SUPER IMPORTANT NOTE, PLEASE DO READ WHAT I'VE SAID IN THE README ABOUT TESTING. 
