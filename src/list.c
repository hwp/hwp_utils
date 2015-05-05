// list.c
// List data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/********** dynamic array **********/

#define DARRAY_INIT_CAP 128

darray_t* darray_alloc(datatype_t type) {
  darray_t* obj = malloc(sizeof(darray_t));
  assert(obj);

  obj->type = type;
  obj->size = 0;
  obj->cap = DARRAY_INIT_CAP;
  obj->data = malloc(datatype_size(type) * obj->cap);
  assert(obj->data);

  return obj;
}

void darray_free(darray_t* obj) {
  free(obj->data);
  free(obj);
}

datatype_t darray_type(darray_t* obj) {
  return obj->type;
}

size_t darray_size(darray_t* obj) {
  return obj->size;
}

static void* offset_bytes(void* ptr, size_t nbytes) {
  char* bp = ptr;
  return bp + nbytes;
}

void darray_push_back(darray_t* obj, void* elem) {
  if (obj->size == obj->cap) {
    obj->cap *= 2;
    obj->data = realloc(obj->data, datatype_size(obj->type) * obj->cap);
  }

  memcpy(darray_get(obj, obj->size), elem, datatype_size(obj->type));
  obj->size++;
}

void* darray_pop_back(darray_t* obj) {
  void* ret = darray_get(obj, obj->size - 1);
  obj->size--;
  return ret;
}

void* darray_get(darray_t* obj, size_t index) {
  assert(index >= 0 && index < obj->cap);
  return offset_bytes(obj->data, index * datatype_size(obj->type));
}

