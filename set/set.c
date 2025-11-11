/*
 * set.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * Implement a set data structure that stores unique (key, item) pairs.
 * Provides create, insert, find, iterate, print, and delete functions.
 * 
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib set.c ../lib/mem.o -o set
 * ./set
 *
 * Exit status:
 * 0 = success
 * nonzero = runtime error
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "mem.h"

/**************** local types ****************/
typedef struct setnode {
  char* key;             
  void* item;                // pointer to item
  struct setnode* next;      // next node link
} setnode_t;

/**************** global type ****************/
typedef struct set {
  struct setnode* head;      // head of linked list
} set_t;

/**************** local functions ****************/
static setnode_t* setnode_new(char* key, void* item);
static char* key_copy(const char* key);

//Create a new (empty) set. See set.h for more description */
set_t*
set_new(void)
{
  set_t* set = mem_malloc(sizeof(set_t));
  if (set == NULL) {
    return NULL;
  } else {
    //// initialize contents of set structure
    set->head = NULL;
    return set;
  }
}

/* Insert item, identified by a key (string), into the given set.
see set.h for more description */
bool set_insert(set_t* set, const char* key, void* item)
{
  if (set==NULL || key == NULL || item == NULL) {
    return false;
  }
  // check existing key
  for (setnode_t* node = set-> head; node != NULL; node = node->next) {
    if (strcmp(node -> key, key) == 0) {
      return false; // key already exist
    }
  }
  // copy the key
  char* keycopy = key_copy(key);
  if (keycopy == NULL) {
    return false;
  }
  // Create new node
  setnode_t* new = setnode_new(keycopy, item);
  if (new == NULL) {
    mem_free(keycopy);
    return false;
  }
  // insert at head
  new->next = set->head;
  set->head = new;
  return true;
}
// helper: setnode_new 
static setnode_t*
setnode_new(char* key, void* item)
{
  setnode_t* node = mem_malloc(sizeof(setnode_t));
  if (node == NULL) {
    return NULL;
  } else {
    node-> key = key;
    node-> item = item;
    node-> next = NULL;
    return node;
  }
}

/**************** set_find ****************/
/* see set.h for more description */
void* set_find(set_t* set, const char* key)
{
  if (set == NULL || key == NULL) {
    return NULL;
  }
  for (setnode_t* node = set->head; node != NULL; node = node->next) {
    if (strcmp(node->key, key) == 0) {
      return node->item;
    }
  }
  return NULL;
}

/**************** set_print ****************/
/* see set.h for more description */
void set_print(set_t* set, FILE* fp, 
          void (*itemprint)(FILE* fp, const char* key, void* item) )
{
  fputc('{', fp);
  for (setnode_t* node = set->head; node != NULL; node = node->next) {
    if (itemprint != NULL) {
      (*itemprint)(fp, node->key, node-> item);
      if (node -> next != NULL) {
        fputs(", ", fp);
      }
    }
  }
  fputc('}', fp);
}

/**************** set_iterate ****************/
/* see set.h for more description */
void set_iterate(set_t* set, void* arg,
            void (*itemfunc)(void* arg, const char* key, void* item) )
{
  for (setnode_t* node = set->head; node != NULL; node = node->next) {
    (*itemfunc)(arg, node->key, node->item);
  }
}

/**************** set_delete ****************/
/* see set.h for more description */
void 
set_delete(set_t* set, void (*itemdelete)(void* item) )
{
  if (set == NULL) {
    return;
  }

  for (setnode_t* node = set->head; node != NULL; ) {
    if (itemdelete != NULL) {
      (*itemdelete)(node-> item);
    }
    mem_free(node->key);
    setnode_t* next = node->next;
    mem_free(node);
    node = next;
  }

  mem_free(set);
}

//copy a string key into new allocated memory
static char*
key_copy(const char* key)
{
  size_t len = strlen(key) + 1;
  char* copy = mem_malloc(len);
  if (copy != NULL) {
    strcpy(copy, key);
  }
  return copy;
}
