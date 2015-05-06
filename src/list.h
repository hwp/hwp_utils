// list.h
// list data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef LIST_H_
#define LIST_H_

#include "common.h"

/********** dynamic array **********/

/**
 * dynamic array
 */
typedef struct {
  datatype_t type;
  size_t size;
  size_t cap;

  void* data;
} darray_t;

/**
 * allocate a dynamic array
 */
darray_t* darray_alloc(datatype_t type);

/**
 * free a dynamic array
 */
void darray_free(darray_t* obj);

/**
 * free a dynamic array and all the elements
 */
void darray_freeall(darray_t* obj, free_f free_elem);

/**
 * element data type
 */
datatype_t darray_type(darray_t* obj);

/**
 * number of elements
 */
size_t darray_size(darray_t* obj);

/**
 * add an element at the end 
 */
void darray_push_back(darray_t* obj, void* elem);

/**
 * get the and delete the element at the end
 */
void* darray_pop_back(darray_t* obj);

/**
 * get an element by index
 */
void* darray_get(darray_t* obj, size_t index);

#endif

