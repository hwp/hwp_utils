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
  darray_t* list = malloc(sizeof(darray_t));
  assert(list);

  list->elem_size = elem_size;
  list->size = 0;
  list->cap = DARRAY_INIT_CAP;
  list->data = malloc(list->elem_size * list->cap);
  assert(list->data);

  return list;
}

void darray_free(darray_t* list) {
  free(list->data);
  free(list);
}

void darray_freeall(darray_t* list, free_f free_elem) {
  assert(list->elem_size == sizeof(void*));
  size_t i;
  for (i = 0; i < list->size; i++) {
    free_elem(VOID_TO_PTR(darray_get(list, i), void));
  }
  darray_free(list);
}

size_t darray_elem_size(darray_t* list) {
  return list->elem_size;
}

size_t darray_size(darray_t* list) {
  return list->size;
}

size_t darray_push_back(darray_t* list, void* elem) {
  size_t inew = darray_increase_size(list);
  memcpy(darray_get(list, inew), elem, list->elem_size);
  return inew;
}

void* darray_pop_back(darray_t* list) {
  void* ret = darray_get(list, list->size - 1);
  list->size--;
  return ret;
}

size_t darray_increase_size(darray_t* list) {
  if (list->size == list->cap) {
    if (list-> cap <= 0) {
      list->cap = DARRAY_INIT_CAP;
    }
    else {
      list->cap *= 2;
    }
    list->data = realloc(list->data, list->elem_size * list->cap);
  }

  size_t inew = list->size;
  list->size++;
  return inew;
}

void* darray_get(darray_t* list, size_t index) {
  assert(index >= 0 && index < list->size);
  return PTR_OFFSET(list->data, index * list->elem_size);
}

