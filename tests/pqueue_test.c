// pqueue_test.c
// test priority queue
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "../src/queue.h"
#include "../src/test.h"

HT_TEST(test_alloc, void*) {
  pqueue_t* queue = pqueue_alloc(sizeof(int), NULL, NULL,
      compar_int, NULL);
  HT_ASSERT(queue != NULL);
  HT_ASSERT(pqueue_size(queue) == 0);
  HT_ASSERT(pqueue_elem_size(queue) == sizeof(int));
  pqueue_free(queue);
}

HT_TEST(test_int, void*) {
  pqueue_t* queue = pqueue_alloc(sizeof(int), NULL, NULL,
      compar_int, NULL);
  int x = 5;
  pqueue_push(queue, &x);
  x = 3;
  pqueue_push(queue, &x);
  x = -1;
  pqueue_push(queue, &x);
  x = 0;
  pqueue_push(queue, &x);
  x = 7;
  pqueue_push(queue, &x);
  x = 4;
  pqueue_push(queue, &x);
  HT_ASSERT(pqueue_size(queue) == 6);

  void* v = NULL;
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == -1);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 0);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 3);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 4);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 5);

  HT_ASSERT(pqueue_size(queue) == 1);

  x = 4;
  pqueue_push(queue, &x);
  pqueue_push(queue, &x);

  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 4);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 4);
  v = pqueue_pop(queue);
  HT_ASSERT(v != NULL);
  HT_ASSERT(VOID_TO_INT(v) == 7);
  v = pqueue_pop(queue);
  HT_ASSERT(v == NULL);

  HT_ASSERT(pqueue_size(queue) == 0);

  pqueue_free(queue);
}

int main(int argc, char** argv) {
  ht_suit_t* suit = ht_suit_alloc(NULL); 

  ht_option_t option;
  ht_get_option(argc, argv, &option);

  ht_add_test(suit, test_alloc);
  ht_add_test(suit, test_int);

  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

