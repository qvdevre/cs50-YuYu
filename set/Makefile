# Makefile for 'set' module
#
# CS50 Lab 5
# based on bag/Makefile by David Kotz and Xia Zhou

OBJS = settest.o set.o ../lib/mem.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

settest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

settest.o: set.h ../lib/mem.h
set.o: set.h
../lib/mem.o: ../lib/mem.h

.PHONY: test valgrind clean

# simple functional test
test: settest
	./settest

# memory leak check
valgrind: settest
	$(VALGRIND) ./settest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f settest
	rm -f core
