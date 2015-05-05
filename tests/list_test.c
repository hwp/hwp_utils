// list_test.c
// test list interfaces
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list_test.h"

#define DEF_TEST_ALLOC(name, _type) \
  static void name(list_it* param) { \
    void* a = param->alloc(_type); \
    HT_ASSERT(param->type(a) == _type); \
    HT_ASSERT(param->size(a) == 0); \
    param->free(a); \
  }

DEF_TEST_ALLOC(test_alloc_int, DATATYPE_INT)
DEF_TEST_ALLOC(test_alloc_uint, DATATYPE_UINT)
DEF_TEST_ALLOC(test_alloc_double, DATATYPE_DOUBLE)
DEF_TEST_ALLOC(test_alloc_ptr, DATATYPE_PTR)

ht_suit_t* create_list_suit(list_it* param) {
  ht_suit_t* ret = ht_suit_alloc(param);

  ht_add_test(ret, (ht_test_f) test_alloc_int);
  ht_add_test(ret, (ht_test_f) test_alloc_uint);
  ht_add_test(ret, (ht_test_f) test_alloc_double);
  ht_add_test(ret, (ht_test_f) test_alloc_ptr);

  return ret;
}

