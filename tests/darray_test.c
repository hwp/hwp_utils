// darray_test.c
// test dynamic array
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list_test.h"

int main(int argc, char** argv) {
  list_it param;
  param.alloc = (void* (*)(datatype_t)) darray_alloc;
  param.free = (void (*)(void*)) darray_free;
  param.type = (datatype_t (*)(void*)) darray_type;
  param.size = (size_t (*)(void*)) darray_size;
  param.push_back = (void (*)(void*, void*)) darray_push_back;
  param.pop_back = (void* (*)(void*)) darray_pop_back;
  param.get = (void* (*)(void*, size_t)) darray_get;

  ht_suit_t* suit = create_list_suit(&param);
  int ret = ht_run_suit(suit, &HT_DEFAULT_OPTION);
  ht_suit_free(suit);

  return ret;
}
