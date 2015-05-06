// common.c
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "common.h"

#include <assert.h>

size_t datatype_size(datatype_t type) {
  size_t size;
  switch (type) {
    case DATATYPE_INT:
      size = sizeof(int);
      break;
    case DATATYPE_UINT:
      size = sizeof(unsigned int);
      break;
    case DATATYPE_DOUBLE:
      size = sizeof(double);
      break;
    case DATATYPE_PTR:
      size = sizeof(void*);
      break;
    default:
      assert(0);
      break;
  }
  
  return size;
}

int compar_int(const void* a, const void* b, void* param) {
  return VOID_TO_INT(b) - VOID_TO_INT(a);
}

int hash_int(void* data, void* param) {
  return VOID_TO_INT(data);
}

