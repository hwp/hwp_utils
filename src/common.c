// common.c
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "common.h"

#include <assert.h>

int compar_int(const void* a, const void* b, void* param) {
  return VOID_TO_INT(b) - VOID_TO_INT(a);
}

int hash_int(void* data, void* param) {
  return VOID_TO_INT(data);
}

