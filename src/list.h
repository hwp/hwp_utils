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
  /**
   * element size (in bytes)
   */
  size_t elem_size;

  /**
   * # of elements
   */
  size_t size;

  /**
   * capacity
   */
  size_t cap;

  /**
   * memory for elements
   */
  void* data;
} darray_t;

/**
 * allocate a dynamic array
 */
darray_t* darray_alloc(size_t elem_size);

/**
 * free a dynamic array
 */
void darray_free(darray_t* obj);

/**
 * free a dynamic array of pointers 
 *   and all the objects the lements point to
 */
void darray_freeall(darray_t* obj, free_f free_elem);

/**
 * element size
 */
size_t darray_elem_size(darray_t* obj);

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

