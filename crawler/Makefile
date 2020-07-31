# Makefile for 'hashtable' module
#
# CS50, Summer 2020

#not sure what I'll need from the library 
PROG = crawler
OBJS = crawler.o 
# LIBS = ../libcs50/libcs50.a ../common/common.a
L = ../libcs50
C = ../common
LIBS = $(L)/libcs50.a $(C)/common.a
# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

# executable depends on object files
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(L) -I$(C)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# object files depend on include files
crawler.o: ../libcs50/bag.h ../libcs50/memory.h ../libcs50/webpage.h ../libcs50/hashtable.h


.PHONY: test valgrind clean

test: 
	bash -v testing.sh > testing.out

valgrind: $(PROG) 
	valgrind ./$(PROG) 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)