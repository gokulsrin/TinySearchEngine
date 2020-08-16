# Makefile for 'bag' module
#
# CS50, Summer 2020

PROG1 = indextest 
OBJS1 = indextest.o 

PROG2 = indexer
OBJS2 = indexer.o 
#all the libs
L = ../libcs50
C = ../common
LIBS = $(C)/common.a $(L)/libcs50.a 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(C) -I$(L)
CC = gcc
MAKE = make

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest.o: ../libcs50/memory.h ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/counters.h ../common/index.h
indexer.o: ../common/index.h ../libcs50/memory.h ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/counters.h ../libcs50/bag.h ../common/pagedir.h

.PHONY: test valgrind clean

# expects nothing
test: 
	bash -v testing.sh 

# expects a file `test.names` to exist; it can contain any text.
valgrind: $(PROG) test.names
	valgrind ./$(PROG) < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
