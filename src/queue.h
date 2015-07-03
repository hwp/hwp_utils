// queue.h
// queue data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef HWP_UTILS_QUEUE_H_
#define HWP_UTILS_QUEUE_H_

#include "common.h"
#include "list.h"

/********** priority queue **********/

/**
 * priority queue
 */
typedef struct {
  /**
   * data stored in an array (heap)
   */
  darray_t* list;
  
  /**
   * Comparison function
   */
  compar_f compar_elem;

  /**
   * parameter for the compare function
   */
  void* compar_param;
} pqueue_t;

/**
 * allocate an empty priority queue 
 *
 * parameters same as darray_alloc()
 *
 * @param compar_elem comparison function
 */
pqueue_t* pqueue_alloc(size_t elem_size, dup_f elem_dup,
    free_f elem_free, compar_f compar_elem, void* compar_param);

/**
 * free a priority queue
 */
void pqueue_free(pqueue_t* queue);

/**
 * element size
 */
size_t pqueue_elem_size(pqueue_t* queue);

/**
 * number of elements
 */
size_t pqueue_size(pqueue_t* queue);

/**
 * add an element to the queue
 */
void pqueue_push(pqueue_t* queue, void* elem);

/**
 * get and remove the smallest element
 *   (accroding to compar_elem) 
 *
 * @return the smallest element, NULL if queue is empty
 */
void* pqueue_pop(pqueue_t* queue);

#endif  // HWP_UTILS_QUEUE_H_

