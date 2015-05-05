// test.c
// Test framework
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ht_option_t HT_DEFAULT_OPTION = {0, HT_CONTINUE};

static int fail_counter;
static ht_option_t* option;

ht_suit_t* ht_suit_alloc(void* param) {
  ht_suit_t* ret = malloc(sizeof(ht_suit_t));
  assert(ret);

  ret->size = 0;
  ret->cap = 10;
  ret->param = param;

  ret->tests = malloc(ret->cap * sizeof(ht_test_f));
  assert(ret->tests);

  return ret;
}

void ht_suit_free(ht_suit_t* suit) {
  if (suit) {
    free(suit->tests);
    free(suit);
  }
}

void ht_add_test(ht_suit_t* suit, ht_test_f test) {
  if (suit->size == suit->cap) {
    suit->cap *= 2;
    suit->tests = realloc(suit->tests, suit->cap * sizeof(ht_test_f));
  }
  suit->tests[suit->size] = test;
  suit->size++;
}

int ht_run_suit(ht_suit_t* suit, ht_option_t* opt) {
  fail_counter = 0;
  option = opt;

  int i;
  for (i = 0; i < suit->size; i++) {
    suit->tests[i](suit->param);
  }

  if (!opt->silent) {
    printf("**** %d failed / %d tested ****\n", fail_counter, suit->size);
  }

  return fail_counter;
}

int ht_assert(int expr, char* msg, const char* file, unsigned int line, const char* name) {
  if (!expr) {
    fail_counter++;
    if (!option->silent) {
      printf("%s (%s:%d): Assertion Failed : %s\n", name, file, line, msg);
    }
  }
  
  return expr;
}

