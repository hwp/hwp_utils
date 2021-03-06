// list.h
// list data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef HWP_UTIL_LIST_H_
#define HWP_UTIL_LIST_H_

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

  /**
   * buffer for one element
   */
  void* buf;

  /**
   * function for duplicate element
   * only necessary when elements are pointers
   * and the data need to be duplicated when added 
   */
  dup_f elem_dup;

  /**
   * function for free element
   * only necessary when elements are pointers
   * and the data need to be freed when the list is freed
   */
  free_f elem_free;
} darray_t;

/**
 * allocate a dynamic array
 *
 * @param elem_size size of element (bytes)
 * @param elem_dup 
 *   if not NULL duplicate pointer and its data 
 *     when adding or setting elements, namely when
 *     darray_push_back() and darray_set() are called.
 * @param elem_free 
 *   if not NULL free pointer data when darray_free() called
 * @note elem_dup is necessary only when elements are
 *    data pointers and hard copied are required.
 * @note elem_free should be provided as long as elem_dup
 *    is not NULL or the list takes the ownership of the
 *    data.
 */
darray_t* darray_alloc(size_t elem_size, dup_f elem_dup,
    free_f elem_free);

/**
 * free a dynamic array
 */
void darray_free(darray_t* list);

/**
 * element size
 */
size_t darray_elem_size(darray_t* list);

/**
 * number of elements
 */
size_t darray_size(darray_t* list);

/**
 * add an element at the end 
 *
 * @return the index of the new element
 */
size_t darray_push_back(darray_t* list, void* elem);

/**
 * get the and delete the element at the end
 */
void* darray_pop_back(darray_t* list);

/**
 * set an element by index
 * index should not exceed size
 */
void darray_set(darray_t* list, size_t index, void* elem);

/**
 * get an element by index
 */
void* darray_get(darray_t* list, size_t index);

/**
 * swap elements by indices
 */
void darray_swap(darray_t* list, size_t i, size_t j);

#endif

