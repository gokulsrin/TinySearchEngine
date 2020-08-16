# Makefile for 'hashtable' module
#
# CS50, Summer 2020

#not sure what I'll need from the library 
PROG = querier
OBJS = querier.o 
# LIBS = ../libcs50/libcs50.a ../common/common.a
L = ../libcs50
C = ../common
LIBS = $(C)/common.a $(L)/libcs50.a
# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

# executable depends on object files
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(C) -I$(L)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# object files depend on include files
querier.o: ../common/index.h ../libcs50/memory.h ../libcs50/file.h ../libcs50/webpage.h ../libcs50/counters.h ../libcs50/hashtable.h 


.PHONY: test valgrind clean

test: 
	bash -v testing.sh > testing.out

valgrind: $(PROG) 
	valgrind ./$(PROG) 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)