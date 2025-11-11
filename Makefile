# Makefile for set module test
# Author: Yu Yu
# Date: 2025/11/06

MAKE = make TESTING=$(TESTING)

all:
	$(MAKE) --directory=bag
	$(MAKE) --directory=counters
	$(MAKE) --directory=set
	$(MAKE) --directory=hashtable
	$(MAKE) --directory=lib

.PHONY: clean

#clean up all derived files
clean:
	rm -f *~
	make --directory=bag clean
	make --directory=set clean
	make --directory=counters clean
	make --directory=hashtable clean
	make --directory=lib clean
