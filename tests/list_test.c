// list_test.c
// test list interfaces
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list_test.h"

#include <stdio.h>
#include <string.h>

#define DEF_TEST_ALLOC(name, _type) \
  HT_TEST(name, list_it*) { \
    void* l = param->alloc(_type); \
    HT_ASSERT(param->type(l) == _type); \
    HT_ASSERT(param->size(l) == 0); \
    param->free(l); \
  }

DEF_TEST_ALLOC(test_alloc_int, DATATYPE_INT)
DEF_TEST_ALLOC(test_alloc_uint, DATATYPE_UINT)
DEF_TEST_ALLOC(test_alloc_double, DATATYPE_DOUBLE)
DEF_TEST_ALLOC(test_alloc_ptr, DATATYPE_PTR)

#define LIST_SIZE 20000

HT_TEST(test_push_pop, list_it*) {
  void* l = param->alloc(DATATYPE_INT);
  int i = 0;
  for (i = 0; i < LIST_SIZE; i++) {
    int x = i * 2 - 12;
    param->push_back(l, &x);
  }
  HT_ASSERT(param->size(l) == LIST_SIZE);

  for (i = LIST_SIZE - 1; i >= 0; i--) {
    int x = VOID_TO_INT(param->pop_back(l));
    HT_ASSERT(x == i * 2 - 12);
  }
  HT_ASSERT(param->size(l) == 0);

  param->free(l);
}

HT_TEST(test_get, list_it*) {
  void* l = param->alloc(DATATYPE_DOUBLE);
  int i = 0;
  for (i = 0; i < LIST_SIZE; i++) {
    double x = 1.0 / (i + 1);
    param->push_back(l, &x);
  }
  HT_ASSERT(param->size(l) == LIST_SIZE);

  for (i = LIST_SIZE - 1; i >= 0; i--) {
    double x = VOID_TO_DOUBLE(param->get(l, i));
    HT_ASSERT(x == 1.0 / (i + 1));
  }
  HT_ASSERT(param->size(l) == LIST_SIZE);
  
  param->free(l);
}

HT_TEST(test_string, list_it*) {
  void* l = param->alloc(DATATYPE_PTR);
  int i = 0;
  for (i = 0; i < LIST_SIZE; i++) {
    char* s = malloc(20 * sizeof(char));
    snprintf(s, 20, "string %d", i);
    param->push_back(l, &s);
  }
  HT_ASSERT(param->size(l) == LIST_SIZE);

  for (i = 0; i < LIST_SIZE; i++) {
    char* s = VOID_TO_PTR(param->get(l, i), char);
    char buf[20];
    snprintf(buf, 20, "string %d", i);
    HT_ASSERT(strcmp(s, buf) == 0);
  }
  HT_ASSERT(param->size(l) == LIST_SIZE);
  
  param->freeall(l, free);
}

ht_suit_t* create_list_suit(list_it* param) {
  ht_suit_t* ret = ht_suit_alloc(param);

  ht_add_test(ret, test_alloc_int);
  ht_add_test(ret, test_alloc_uint);
  ht_add_test(ret, test_alloc_double);
  ht_add_test(ret, test_alloc_ptr);
  ht_add_test(ret, test_push_pop);
  ht_add_test(ret, test_get);
  ht_add_test(ret, test_string);

  return ret;
}

