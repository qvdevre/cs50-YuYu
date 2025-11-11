/*
 * counters.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * Implement a counters data structure that tracks integer keys and counts.
 * Provides create, add, get, set, print, iterate, and delete functions.
 *
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib counters.c ../lib/mem.o -o counters
 * ./counters
 *
 * Exit status:
 * 0 = success
 * nonzero = error
 */
#include <stdio.h>
#include <stdlib.h>
#include "counters.h"
#include "mem.h"  

/**************** local types ****************/
typedef struct counternode {
  int key;                    
  int count;                  
  struct counternode* next;   // next node link
} counternode_t;

/**************** global type ****************/
typedef struct counters {
  struct counternode* head;   // head of linked list
} counters_t;

/**************** local function prototype ****************/
static counternode_t* counternode_new(const int key, const int count);

/**************** counters_new ****************/
/* see counters.h for description */
counters_t*
counters_new(void)
{
  counters_t* ctrs = mem_malloc(sizeof(counters_t));
  if (ctrs==NULL) {
    return NULL;
  } else {
    ctrs->head = NULL;
    return ctrs;
  }
}
/**************** counters_add ****************/
/* see counters.h for description */
int
counters_add(counters_t* ctrs, const int key)
{
  for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
    if (node -> key == key) {
      node -> count++;
      return node->count;
    }
  }
  // not found; create new node with count = 1
  counternode_t* new = counternode_new(key, 1);
  if (new==NULL) {
    return 0;
  }
  new->next = ctrs->head;
  ctrs->head = new;
  return new->count;
}

/**************** counters_get ****************/
/* see counters.h for description */
int
counters_get(counters_t* ctrs, const int key)
{
  if (ctrs == NULL || key < 0) {
    return 0;
  }
  for (counternode_t* node = ctrs->head;node!=NULL; node = node->next) {
    if (node->key==key) {
      return node->count;
    }
  }
  return 0;   // not found
}

/**************** counters_set ****************/
/* see counters.h for description */
bool
counters_set(counters_t* ctrs, const int key, const int count)
{
  if (ctrs == NULL || key < 0 || count < 0) {
    return false;
  }
  for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
    if (node->key == key) {
      node->count = count;
      return true;
    }
  }
  // not found; creat new node
  counternode_t* new = counternode_new(key, count);
  if (new == NULL) {
    return false;
  }
  new->next = ctrs->head;
  ctrs->head = new;
  return true;
}

/**************** counters_print ****************/
/* see counters.h for description */
void
counters_print(counters_t* ctrs, FILE* fp)
{
  fputc('{', fp);
  for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
    fprintf(fp, "%d=%d", node->key, node->count);
    if (node->next != NULL) {
      fputs(", ", fp);
    }
  }
  fputc('}', fp);
}

/**************** counters_iterate ****************/
/* see counters.h for description */
void counters_iterate(counters_t* ctrs, void* arg,
                 void (*itemfunc)(void* arg, const int key, const int count))
{
  for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
    (*itemfunc)(arg, node->key, node->count);
  }
}

/**************** counters_delete ****************/
/* see counters.h for description */
void
counters_delete(counters_t* ctrs)
{ if (ctrs == NULL) {
    return;
  }
  for (counternode_t* node = ctrs->head; node != NULL; ) {
    counternode_t* next=node->next;
    mem_free(node);
    node = next;
  }
  mem_free(ctrs);
}

/**************** local helper: counternode_new ****************/
static counternode_t*
counternode_new(const int key, const int count)
{
  counternode_t* node = mem_malloc(sizeof(counternode_t));
  if (node==NULL) {
    return NULL;
  } else {
    node->key = key;
    node->count = count;
    node->next = NULL;
    return node;
  }
}
