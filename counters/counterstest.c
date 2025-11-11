/*
 * settest.c
 * Author: Yu Yu
 * Date: 2025/11/06
 *
 * Purpose:
 * test for the counters module.
 *
 * Usage:
 * gcc -Wall -pedantic -std=c11 -ggdb -I../lib -o counterstest counterstest.c counters.c ../lib/mem.o
 * ./counterstest
 *
 * Exit status:
 * 0 = success
 * nonzero = error during test
 */

#include <stdio.h>
#include "counters.h"
#include "mem.h"

static void
countsum(void* arg, const int key, const int count)
{
  if (arg != NULL) {
    int* sum = arg;
    *sum += count;
  }
}

int
main(void)
{
  printf("Counters Module Test Start\n");

  counters_t* c = counters_new();
  if (c == NULL) {
    fprintf(stderr, "counters_new failed\n");
    return 1;
  }
  // add keys
  counters_add(c, 3);
  counters_add(c, 3);
  counters_add(c, 7);
  counters_add(c, 0);

  printf("After adding: ");
  counters_print(c, stdout);
  printf("\n");

  // get existing or non-existing
  printf("Key 3 = %d\n", counters_get(c, 3));
  printf("Key 7 = %d\n", counters_get(c, 7));
  printf("Key 99 = %d\n", counters_get(c, 99));

  // set counts
  counters_set(c, 3, 10);
  counters_set(c, 5, 8);

  printf("After sets: ");
  counters_print(c, stdout);
  printf("\n");

  // iterate to sum
  int total = 0;
  counters_iterate(c,&total,countsum);
  printf("Total count sum = %d\n", total);

  counters_delete(c);
  printf("Counters was deleted successfully.\n");

  mem_report(stdout, "End Test");
  return 0;
}
