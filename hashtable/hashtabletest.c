/*
 * settest.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * test for the hashtable module.
 *
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib -o hashtabletest hashtabletest.c hashtable.c ../lib/mem.o
 * ./hashtabletest
 *
 * Exit status:
 * 0 = success
 * nonzero = error during test
 */


#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "mem.h"

//print each key-item pair
static void
itemprint(FILE* fp, const char* key, void* item)
{
  if (fp != NULL && key != NULL && item != NULL) {
    fprintf(fp, "%s : %d", key, *(int*)item);
  }
}

// free item pointer
static void
itemdelete(void* item)
{
  if (item!=NULL) {
    mem_free(item);
  }
}

//count total items in the set
static void
itemcount(void* arg,const char* key, void* item)
{
  if (arg != NULL) {
    int* n = arg;
    (*n)++;
  }
}
int
main(void)
{
  printf("Hashtable Test Start\n");

  hashtable_t* ht = hashtable_new(5);
  if (ht==NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    return 1;
  }

  // insert a few key-item pairs
  for (int i = 0; i < 4; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    int* val = mem_malloc(sizeof(int));
    *val = i * 10;
    hashtable_insert(ht,key,val);
  }
  // test duplicate key
  int dummy = 999;
  if (!hashtable_insert(ht,"key1",&dummy)) {
    printf("Duplicate key was rejected correctly.\n");
  }

  // test find
  int* found = hashtable_find(ht, "key3");
  if (found != NULL) {
    printf("Found key3 -> %d\n", *found);
  } else {
    printf("key3 not found.\n");
  }

  // print table
  printf("Hashtable contents:\n");
  hashtable_print(ht, stdout, itemprint);

  // iterate to sum
  int total = 0;
  hashtable_iterate(ht, &total, itemcount);
  printf("Total sum of all values = %d\n", total);

  hashtable_delete(ht, itemdelete);
  printf("Hashtable was deleted successfully.\n");

  mem_report(stdout, "End Test");
  return 0;
}
