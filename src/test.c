// test.c
// Test framework
//
// Author : Weipeng He <heweipeng@gmail.com>
// Distributed under the MIT License.

#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

h_test_option_t H_TEST_DEFAULT_OPTION = {0, H_TEST_CONTINUE};

static int fail_counter;
static h_test_option_t* option;

h_test_suit_t* h_test_suit_alloc(void* param) {
  h_test_suit_t* ret = malloc(sizeof(h_test_suit_t));
  assert(ret);

  ret->size = 0;
  ret->cap = 10;
  ret->param = param;

  ret->tests = malloc(ret->cap * sizeof(h_test_f));
  assert(ret->tests);

  return ret;
}

void h_test_suit_free(h_test_suit_t* suit) {
  if (suit) {
    free(suit->tests);
    free(suit);
  }
}

void h_add_test(h_test_suit_t* suit, h_test_f test) {
  if (suit->size == suit->cap) {
    suit->cap *= 2;
    suit->tests = realloc(suit->tests, suit->cap * sizeof(h_test_f));
  }
  suit->tests[suit->size] = test;
  suit->size++;
}

int h_run_suit(h_test_suit_t* suit, h_test_option_t* opt) {
  fail_counter = 0;
  option = opt;

  int i;
  for (i = 0; i < suit->size; i++) {
    suit->tests[i](suit->param);
  }

  return fail_counter;
}

int h_assert(int expr, char* msg, char* file, int line) {
  if (!expr) {
    fail_counter++;
    if (!option->silent) {
      printf("assertion failed at %s:%d\n\t%s\n", file, line, msg);
    }
  }
  
  return expr;
}

/*
h_assert_eq_int(int x, int y, char* file, int line) {
  char* msg;
  asprintf(msg, "expected  ==  ")

    free(msg);
}
*/
