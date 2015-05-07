// list_test.h
// test list interfaces
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef ___TESTS_LIST_TEST_H_
#define ___TESTS_LIST_TEST_H_

#include "../src/list.h"
#include "../src/test.h"

typedef struct {
  void* (*alloc)(size_t elem_size);
  void (*free)(void* obj);
  void (*freeall)(void* obj, free_f free_elem);
  size_t (*elem_size)(void* obj);
  size_t (*size)(void* obj);
  void (*push_back)(void* obj, void* elem);
  void* (*pop_back)(void* obj);
  void* (*get)(void* obj, size_t index);
} list_it;

/**
 * create a test suit with list interfaces
 */
ht_suit_t* create_list_suit(list_it* param);

#endif  // ___TESTS_LIST_TEST_H_

