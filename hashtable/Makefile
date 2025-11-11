# Makefile for hashtable module test
# Author: Yu Yu
# Date: 2025/11/06

OBJS = hashtabletest.o hashtable.o hash.o ../set/set.o ../lib/mem.o
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../set/set.h ../lib/mem.h hash.h
hashtable.o: hashtable.h hash.h ../set/set.h
hash.o: hash.h
../set/set.o: ../set/set.h
../lib/mem.o: ../lib/mem.h

.PHONY: test valgrind clean

test: hashtabletest
	./hashtabletest

valgrind: hashtabletest
	$(VALGRIND) ./hashtabletest

#clean up all derived files
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
