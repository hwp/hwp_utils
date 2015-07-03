// queue.c
// queue data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "queue.h"

#include <assert.h>

#define PARENT(n) (((n) - 1) / 2)
#define LCHILD(n) (((n) + 1) * 2 - 1)
#define RCHILD(n) (((n) + 1) * 2)

pqueue_t* pqueue_alloc(size_t elem_size, dup_f elem_dup,
    free_f elem_free, compar_f compar_elem, void* compar_param) {
  pqueue_t* ret = malloc(sizeof(pqueue_t));
  assert(ret);

  ret->list = darray_alloc(elem_size, elem_dup, elem_free);
  ret->compar_elem = compar_elem;
  ret->compar_param = compar_param;
  
  return ret;
}

void pqueue_free(pqueue_t* queue) {
  if (queue) {
    darray_free(queue->list);
    free(queue);
  }
}

size_t pqueue_elem_size(pqueue_t* queue) {
  return darray_elem_size(queue->list);
}

size_t pqueue_size(pqueue_t* queue) {
  return darray_size(queue->list);
}

void pqueue_push(pqueue_t* queue, void* elem) {
  size_t i = darray_push_back(queue->list, elem);
  while (i > 0 && queue->compar_elem(
        darray_get(queue->list, PARENT(i)), 
        darray_get(queue->list, i), queue->compar_param) > 0) {
    darray_swap(queue->list, PARENT(i), i);
    i = PARENT(i);
  }
}

void* pqueue_pop(pqueue_t* queue) {
  size_t s = pqueue_size(queue);
  if (s == 0) {
    return NULL;
  }

  s--;
  darray_swap(queue->list, 0, s);

  size_t i = 0;
  while (LCHILD(i) < s) {
    if (queue->compar_elem(
          darray_get(queue->list, i),
          darray_get(queue->list, LCHILD(i)), 
          queue->compar_param) > 0) {
      // l < p
      if (RCHILD(i) < s && queue->compar_elem(
            darray_get(queue->list, LCHILD(i)),
            darray_get(queue->list, RCHILD(i)), 
            queue->compar_param) > 0) {
        // r < l < p
        darray_swap(queue->list, i, RCHILD(i));
        i = RCHILD(i);
      }
      else {
        // l <= r
        darray_swap(queue->list, i, LCHILD(i));
        i = LCHILD(i);
      }
    }
    else {
      // p <= l
      if (RCHILD(i) < s && queue->compar_elem(
            darray_get(queue->list, i),
            darray_get(queue->list, RCHILD(i)), 
            queue->compar_param) > 0) {
        // r < p <= l
        darray_swap(queue->list, i, RCHILD(i));
        i = RCHILD(i);
      }
      else {
        // p <= r
        break;
      }
    }
  }

  return darray_pop_back(queue->list);
}

