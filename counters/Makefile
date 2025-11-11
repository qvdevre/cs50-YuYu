# Makefile for counters module test
# Author: Yu Yu
# Date: 2025/11/06

OBJS = counterstest.o counters.o ../lib/mem.o
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/mem.h
counters.o: counters.h
../lib/mem.o: ../lib/mem.h

.PHONY: test valgrind clean

test: counterstest
	./counterstest

valgrind: counterstest
	$(VALGRIND) ./counterstest

#clean up all derived files
clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f counterstest
	rm -f core
