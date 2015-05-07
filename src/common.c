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

#define fsign(x) ((int)(((x) > 0.0) - ((x) < 0.0)))

int compar_double(const void* a, const void* b, void* param) {
  return fsign(VOID_TO_DOUBLE(b) - VOID_TO_DOUBLE(a));
}

uint32_t hash_int(void* data, void* param) {
  return (uint32_t) VOID_TO_INT(data);
}

uint32_t hash_double(void* data, void* param) {
  size_t len = sizeof(double);
  return hash_rotate(data, &len);
}

uint32_t hash_rotate(void* data, size_t* size) {
  uint32_t hash = (uint32_t) *size;
  char* v = data;
  size_t i;
  for (i = 0; i < *size; i++) {
    hash = (hash << 4) ^ (hash >> 28) ^ v[i];
  }
  return hash;
}

