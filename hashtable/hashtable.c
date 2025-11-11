/*
 * hashtable.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * Implement a hashtable that maps (key, item) pairs using an array of sets.
 * Provides create, insert, lookup, print, iterate, and delete functions.
 *
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib -I../set hashtable.c hash.c ../set/set.o ../lib/mem.o -o hashtable
 * ./hashtable
 *
 * Exit status:
 * 0 = success
 * nonzero = error
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"
#include "mem.h"
#include "set.h"  

/**************** local types ****************/
typedef struct hashtable {
  int nslots;        // number of slots
  set_t** slots;  
} hashtable_t;

/**************** hashtable_new ****************/
/* see hashtable.h for description */
hashtable_t*
hashtable_new(const int num_slots)
{
  if (num_slots <= 0) {
    return NULL;
  }
  hashtable_t* ht = mem_malloc(sizeof(hashtable_t));
  if (ht == NULL) {
    return NULL;
  }
  ht-> nslots = num_slots;
  ht-> slots = mem_calloc(num_slots, sizeof(set_t*));
  if (ht->slots == NULL) {
    mem_free(ht);
    return NULL;
  }
  // initialize each slot with a new set
  for (int i = 0; i < num_slots; i++) {
    ht->slots[i] = set_new();
    if (ht->slots[i] == NULL) {
      // free previously allocated sets
      for (int j = 0; j < i; j++) {
        set_delete(ht->slots[j], NULL);
      }
      mem_free(ht->slots);
      mem_free(ht);
      return NULL;
    }
  }
  return ht;
}

/**************** hashtable_insert ****************/
/* see hashtable.h for description */
bool
hashtable_insert(hashtable_t* ht, const char* key, void* item)
{
  unsigned long index = hash_jenkins(key, ht->nslots); // hash key to find slot index
  set_t* bucket = ht->slots[index];
  if (bucket == NULL) {
    return false;
  }

  return set_insert(bucket, key, item);
}

/**************** hashtable_find ****************/
/* see hashtable.h for description */
void*
hashtable_find(hashtable_t* ht, const char* key)
{
  if (ht == NULL || key == NULL) {
    return NULL;
  }
  // hash key to find bucket
  unsigned long index = hash_jenkins(key, ht->nslots);
  set_t* bucket = ht->slots[index];
  if (bucket == NULL) {
    return NULL;
  }

  return set_find(bucket, key);
}

/**************** hashtable_print ****************/
/* see hashtable.h for description */
void
hashtable_print(hashtable_t* ht, FILE* fp,
                void (*itemprint)(FILE* fp, const char* key, void* item))
{
  for (int i = 0; i < ht -> nslots; i++) {
    fprintf(fp, "Slot[%d]: ", i);
    set_print(ht->slots[i], fp, itemprint);
    fputc('\n', fp);
  }
}

/**************** hashtable_iterate ****************/
/* see hashtable.h for description */
void
hashtable_iterate(hashtable_t* ht, void* arg,
                  void (*itemfunc)(void* arg, const char* key, void* item))
{
  if (ht == NULL || itemfunc == NULL) {
    return;
  }
  for (int i = 0; i < ht->nslots; i++) {
    set_iterate(ht->slots[i], arg, itemfunc);
  }
}

/**************** hashtable_delete ****************/
/* see hashtable.h for description */
void
hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item))
{
  for (int i = 0; i < ht -> nslots; i++) {
    set_delete(ht->slots[i], itemdelete);
  }
  mem_free(ht->slots);
  mem_free(ht);
}
