#!/bin/bash

#In this file I will create tests of the type detailed in the implementation.md file. In sum, 
#I'm just testing how the program handles invalid input. 

#Test 1: Standard case where execution is successful and files are created correctly.
printf "Test 1: \n"
./indexer ../crawler/crawldir ./test5.txt


#Test 2: Case where there isn't enough input
printf "\nTest 2: \n"
./indexer ../crawler/crawldir 


#Test 3: invalid directory name -- hence no output
printf "\nTest 3: \n"
./indexer ../crawler/crawldir///yolo ./test4.txt



#Test 5: No arguments
printf "\nTest 5: \n"
./indexer


#The tests above capture, for the most part, the range of use cases of the function and the error handeling 

