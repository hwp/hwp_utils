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

darray_t* darray_alloc(size_t elem_size, dup_f elem_dup,
    free_f elem_free) {
  if (elem_dup != NULL || elem_free != NULL) {
    assert(elem_size == sizeof(void*));
  }
  darray_t* list = malloc(sizeof(darray_t));
  assert(list);

  list->elem_size = elem_size;
  list->size = 0;
  list->cap = 0;
  list->data = NULL;

  list->elem_dup = elem_dup;
  list->elem_free = elem_free;

  return list;
}

void darray_free(darray_t* list) {
  if (list) {
    if (list->elem_free) {
      assert(list->elem_size == sizeof(void*));
      size_t i;
      for (i = 0; i < list->size; i++) {
        list->elem_free(VOID_TO_PTR(darray_get(list, i), void));
      }
    }

    free(list->data);
    free(list);
  }
}

size_t darray_elem_size(darray_t* list) {
  return list->elem_size;
}

size_t darray_size(darray_t* list) {
  return list->size;
}

static size_t darray_increase_size(darray_t* list) {
  if (list->size == list->cap) {
    if (list->cap <= 0) {
      list->cap = DARRAY_INIT_CAP;
    }
    else {
      list->cap *= 2;
    }
    list->data = realloc(list->data, list->elem_size * list->cap);
    memset(PTR_OFFSET(list->data, list->size * list->elem_size),
        0, (list->cap - list->size) * list->elem_size);
  }

  size_t inew = list->size;
  list->size++;
  return inew;
}

size_t darray_push_back(darray_t* list, void* elem) {
  size_t inew = darray_increase_size(list);
  darray_set(list, inew, elem);
  return inew;
}

void* darray_pop_back(darray_t* list) {
  void* ret = darray_get(list, list->size - 1);
  list->size--;
  return ret;
}

void darray_set(darray_t* list, size_t index, void* elem) {
  assert(index >= 0 && index < list->size);
  void** ptr = darray_get(list, index);

  if (list->elem_free && *ptr) {
    list->elem_free(*ptr);
  }

  if (list->elem_dup) {
    *ptr = list->elem_dup(VOID_TO_PTR(elem, void));
  }
  else {
    memcpy(darray_get(list, index), elem, list->elem_size);
  }
}

void* darray_get(darray_t* list, size_t index) {
  assert(index >= 0 && index < list->size);
  return PTR_OFFSET(list->data, index * list->elem_size);
}

