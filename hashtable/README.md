# CS50 Lab 5
## CS50 Fall 2025
## Author: Yu Yu. Reference: lab5/bag from CS50

### hashtable

A `hashtable` is a collection of (key, item) pairs, which provides efficient access via hashing.  

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a hashtable of `void*`, and exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation

The `hashtable` module uses an array of `set` structures as hash buckets.  
It uses a hash function to assign each key to a bucket based on its hash value.Operations like insert, find, and iterate are achieved by the `set` module.  
All buckets and their contents were released when the hashtable was deleted.

### Assumptions

Number of slots must be greater than 0.
Keys and items must be non-NULL.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtabletest.c` - unit test driver
* `hash.c / hash.h` - hash function

### Compilation

To compile, simply `make`.

### Testing

The hashtabletest.c program inserts several key-item pairs, tests duplicate handling, and prints all buckets.
It prints internal iteraltions and ensures no memory leaks.

To test, simply `make test`.

To test with valgrind, `make valgrind`.
