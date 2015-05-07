// list.c
// list data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "list.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/********** dynamic array **********/

#define DARRAY_INIT_CAP 16

darray_t* darray_alloc(size_t elem_size) {
  darray_t* obj = malloc(sizeof(darray_t));
  assert(obj);

  obj->elem_size = elem_size;
  obj->size = 0;
  obj->cap = DARRAY_INIT_CAP;
  obj->data = malloc(obj->elem_size * obj->cap);
  assert(obj->data);

  return obj;
}

void darray_free(darray_t* obj) {
  free(obj->data);
  free(obj);
}

void darray_freeall(darray_t* obj, free_f free_elem) {
  assert(obj->elem_size == sizeof(void*));
  size_t i;
  for (i = 0; i < obj->size; i++) {
    free_elem(VOID_TO_PTR(darray_get(obj, i), void));
  }
  darray_free(obj);
}

size_t darray_elem_size(darray_t* obj) {
  return obj->elem_size;
}

size_t darray_size(darray_t* obj) {
  return obj->size;
}

void darray_push_back(darray_t* obj, void* elem) {
  if (obj->size == obj->cap) {
    obj->cap *= 2;
    obj->data = realloc(obj->data, obj->elem_size * obj->cap);
  }

  obj->size++;
  memcpy(darray_get(obj, obj->size - 1), elem, obj->elem_size);
}

void* darray_pop_back(darray_t* obj) {
  void* ret = darray_get(obj, obj->size - 1);
  obj->size--;
  return ret;
}

void* darray_get(darray_t* obj, size_t index) {
  assert(index >= 0 && index < obj->size);
  return PTR_OFFSET(obj->data, index * obj->elem_size);
}

