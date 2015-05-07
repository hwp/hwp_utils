// darray_test.c
// test dynamic array
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list_test.h"

int main(int argc, char** argv) {
  list_it param;
  param.alloc = (void* (*)(size_t)) darray_alloc;
  param.free = (void (*)(void*)) darray_free;
  param.freeall = (void (*)(void*, free_f)) darray_freeall;
  param.elem_size = (size_t (*)(void*)) darray_elem_size;
  param.size = (size_t (*)(void*)) darray_size;
  param.push_back = (size_t (*)(void*, void*)) darray_push_back;
  param.pop_back = (void* (*)(void*)) darray_pop_back;
  param.get = (void* (*)(void*, size_t)) darray_get;

  ht_suit_t* suit = create_list_suit(&param);
  
  ht_option_t option;
  ht_get_option(argc, argv, &option);
  
  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

