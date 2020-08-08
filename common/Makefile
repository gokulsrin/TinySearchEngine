# Makefile for CS50 library
#   Builds and compiles all these utility functions into a library.
#
#
# CS50, Summer 2020

# object files, and the target library
OBJS = pagedir.o index.o word.o
LIB = common.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.h 
index.o: index.h ../libcs50/memory.h ../libcs50/hashtable.h ../libcs50/counters.h ../libcs50/set.h
word.o: word.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
