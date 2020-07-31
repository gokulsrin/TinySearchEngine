#!/bin/bash

#In this file I will create tests of the type detailed in the implementation.md file. In sum, 
#I'm just testing how the program handles invalid input. 

#Test 1: Standard case where execution is successful and files are created correctly.
printf "Test 1: \n"
./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ./crawldir 1 

#Test 2: Case where maxDepth is invalid ... no output is returned
printf "\nTest 2: \n"
./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ./crawldir -1 

#Test 3: invalid directory name -- hence no output
printf "\nTest 3: \n"
./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html ./crawldireeee 2 

#Test 4: invalid url -- the url is null
printf "\nTest 4: \n"
./crawler  ./crawldir 1 

#Test 5: invalid url -- the url is wrong
printf "\nTest 5: \n"
./crawler  wwwwww ./crawldir 1 

#Test 6: invald dir name
printf "\nTest 6: \n"
./crawler  http://old-www.cs.dartmouth.edu/~cs50/index.html  ./crawldireee 1 

#The tests above capture, for the most part, the range of use cases of the function and the error handeling 

