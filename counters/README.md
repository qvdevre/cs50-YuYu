# CS50 Lab 5
## CS50 Fall 2025
## Author: Yu Yu. Reference: lab5/bag from CS50

### counters

A `counters` is a collection of integer keys, each associated with a counter value.  
Each key can appear only once; calling `counters_add()` increments its value, and calling `counters_set()` to assigns a specific value.   

### Usage

The *counter* module, defined in `counter.h` and implemented in `counter.c`, implements a set of integer counters and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

The `counters` module is implemented as a linked list of (key, count) pairs.  
Each node holds one integer key and its counter value.  
When a key is added, the counter is incremented or created if it doesn't exist.  

### Assumptions

Keys and counts must be non-negative integers.

### Files

* `Makefile` - compilation procedure
* `counter.h` - the interface
* `counter.c` - the implementation
* `countertest.c` - unit test driver

### Compilation

To compile, simply `make`.

### Testing

The 'counterstest.c' program exercises add, get, set, iterate, and delete functions.
It prints internal results and ensures no memory leaks.

To test, simply `make test`.

To test with valgrind, `make valgrind`.
