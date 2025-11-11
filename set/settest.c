/*
 * settest.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * test for the set module.
 *
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib -o settest settest.c set.c ../lib/mem.o
 * ./settest
 *
 * Exit status:
 * 0 = success
 * nonzero = error during test
 */
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "../lib/mem.h"

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
  printf("Set Module Test Start\n");

  set_t* myset = set_new();
  if (myset == NULL) {
    fprintf(stderr, "set_new failed\n");
    return 1;
  }

  // insert items
  for (int i = 0; i < 3; i++) {
    char key[10];
    sprintf(key, "key%d", i);
    int* val = mem_malloc(sizeof(int));
    *val = i*10;
    if (!set_insert(myset, key, val)) {
      fprintf(stderr, "insert failed for %s\n", key);
    }
  }

  // test duplicate insert
  int dummy = 999;
  if (!set_insert(myset, "key1", &dummy)) {
    printf("Duplicate key was rejected correctly.\n");
  }
  // test find
  int* found = set_find(myset, "key2");
  if (found != NULL) {
    printf("Found key2 -> %d\n", *found);
  } else {
    printf("key2 not found.\n");
  }

  // test print
  printf("Set contents: ");
  set_print(myset, stdout, itemprint);
  printf("\n");

  // test iterate
  int count = 0;
  set_iterate(myset, &count, itemcount);
  printf("Total items counted: %d\n", count);

  // test delete
  set_delete(myset, itemdelete);
  printf("Set was deleted successfully.\n");

  mem_report(stdout, "End Test");
  return 0;
}
