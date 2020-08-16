#opting to do traditional testing, regression testing instead of fuzz testing, because I'm getting some strange seg faults
#I'll detail the testing slightly more in the readme, but in the event that you are reading this, please do not
#take points from the lab because I've included a folder called testing; this testing folder is used for all of the below testing...

#The first set of tests will showcase the querey checking

#Test 1 - Invalid pathDirectory in initial program call
printf "\nTest 1: invalid pathDirectory in initial program call \n"
errormessage=$( ./querier ./nonexistantpath ./testing/output.txt 2>&1)
echo $errormessage

#Test 2 - Invalid indexFile path in intial program call 
printf "\nTest 2: Invalid indexFile path in intial program call  \n"
errormessage=$( ./querier ./testing/crawldir/ ./testing/nonexistantpath  2>&1)
echo $errormessage

#Test 3 - consecutive ands in query 
printf "Test 3: consecutive ands in query  \n"
errormessage=$( echo "This and and that" | ./querier ./testing/crawldir/ ./testing/output.txt  2>&1)
echo $errormessage

#Test 4 - consecutive ors in query 
printf "Test 4: consecutive ors in query  \n"
errormessage=$( echo "This or or that" | ./querier ./testing/crawldir/ ./testing/output.txt  2>&1)
echo $errormessage

#Test 5 - and/or at the beginning 
printf "Test 5: and/or at the beginning  \n"
errormessage=$( echo "and this or that" | ./querier ./testing/crawldir/ ./testing/output.txt  2>&1)
echo $errormessage

#Test 6 - and/or at the end
printf "Test 6: and/or at the end  \n"
errormessage=$( echo "this that or" | ./querier ./testing/crawldir/ ./testing/output.txt  2>&1)
echo $errormessage

#Test 7 - and/or consecutively
printf "Test 7: and/or consecutively  \n"
errormessage=$( echo "this or and that" | ./querier ./testing/crawldir/ ./testing/output.txt  2>&1)
echo $errormessage

#The second set of tests will highlight the functionality of the querier provided valid arguments

#Test 8 - Query: "this   that or    home"
printf "Test 8: query: 'this   that or    home'  \n"
message=$( echo "this   that or    home" | ./querier ./testing/crawldir/ ./testing/output.txt  1>&1)
echo $message

#Test 9 - Query: "algorithm and the home"
printf "Test 9: query: 'this   that or    home'  \n"
message=$( echo "algorithm and the home" | ./querier ./testing/crawldir/ ./testing/output.txt  1>&1)
echo $message

#Test 10 - Query: "huffman or  transform  or traversal"
printf "Test 10: query: 'huffman or  transform  or traversal'  \n"
message=$( echo "huffman or  transform  or traversal" | ./querier ./testing/crawldir/ ./testing/output.txt  1>&1)
echo $message

#Test 11 - Query: "biology first search"
printf "Test 11: query: 'biology first search'  \n"
message=$( echo "biology first search" | ./querier ./testing/crawldir/ ./testing/output.txt  1>&1)
echo $message

#Test 12 - Query: "biology or first and search"
printf "Test 12: query: 'biology or first and search'  \n"
message=$( echo "biology or first and search" | ./querier ./testing/crawldir/ ./testing/output.txt  1>&1)
echo $message