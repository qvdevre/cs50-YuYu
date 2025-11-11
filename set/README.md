# CS50 Lab 5
## CS50 Fall 2025
## Author: Yu Yu. Reference: lab5/bag from CS50

### set

A `set` is an unordered collection of unique (key, item) pairs.  
The `set` starts empty and grows as the caller inserts new pairs.  
The caller can retrieve items by asking for their key, but it can't remove or update pairs.  

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `void*`, and exports the following functions:

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) )
```

### Implementation

The `set` module is implemented using a simple linked list.  
Every new key–item pair is stored as a node at the head of the list.  
Duplicate keys were ignored.  
The module manages memory for key strings and allows users to provide custom delete or print functions.

### Assumptions

No assumptions beyond those that are clear from the spec.
The key and item must be non-NULL.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver

### Compilation

To compile, simply `make`.

### Testing

The 'settest.c' program inserts several key-item pairs, tests duplicate key rejection, retrieves values, and deletes the set. It prints internal data and confirms no memory leaks.

To test, simply `make test`.

To test with valgrind, `make valgrind`.
