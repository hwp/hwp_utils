// hashmap_test.c
// test hash map
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "../src/map.h"
#include "../src/test.h"

#include <stdio.h>

HT_TEST(test_alloc, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(int), NULL, NULL,
      sizeof(int), NULL, NULL, HASHMAP_DEFAULT_NBINS,
      hash_int, NULL, compar_int, NULL);
  HT_ASSERT(hashmap_size(map) == 0);
  hashmap_free(map);
}

HT_TEST(test_put, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(int), NULL, NULL,
      sizeof(int), NULL, NULL, HASHMAP_DEFAULT_NBINS,
      hash_int, NULL, compar_int, NULL);
  HASHMAP_PUT_TYPE(map, int, int, 2, 3);
  HASHMAP_PUT_TYPE(map, int, int, 3, 4);
  HASHMAP_PUT_TYPE(map, int, int, 4, 1);
  HT_ASSERT(hashmap_size(map) == 3);

  int k;
  k = 4;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 1);
  k = 3;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 4);
  k = 2;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 3);
  k = 1;
  HT_ASSERT(hashmap_get(map, &k) == NULL);
  
  HASHMAP_PUT_TYPE(map, int, int, 2 + HASHMAP_DEFAULT_NBINS, -3);
  k = 2;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 3);
  k = 2 + HASHMAP_DEFAULT_NBINS;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == -3);
  k = 1;
  HT_ASSERT(hashmap_get(map, &k) == NULL);

  HASHMAP_PUT_TYPE(map, int, int, 2, 3214);
  HT_ASSERT(hashmap_size(map) == 4);
  k = 2;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 3214);
  k = 1;
  HT_ASSERT(hashmap_get(map, &k) == NULL);

  hashmap_free(map);
}

#define SIZE_OF_MAP 2000

HT_TEST(test_put_int_double, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(int), NULL, NULL,
      sizeof(double), NULL, NULL, HASHMAP_DEFAULT_NBINS,
      hash_int, NULL, compar_int, NULL);
  HT_ASSERT(hashmap_size(map) == 0);

  int i;
  for (i = 0; i < SIZE_OF_MAP; i++) {
    HASHMAP_PUT_TYPE(map, int, double, 20 - i, 4.0 / (i + 1));
    HT_ASSERT(hashmap_size(map) == i + 1);
  }

  for (i = 0; i < SIZE_OF_MAP; i++) {
    int k = 20 - i;
    void* v = hashmap_get(map, &k);
    HT_ASSERT(v != NULL);
    HT_ASSERT(VOID_TO_DOUBLE(v) == 4.0 / (i + 1));
  }

  for (i = 0; i < SIZE_OF_MAP; i++) {
    HASHMAP_PUT_TYPE(map, int, double, 20 - i, 2.0);
  }
  HT_ASSERT(hashmap_size(map) == SIZE_OF_MAP);

  for (i = 0; i < SIZE_OF_MAP; i++) {
    int k = 20 - i;
    void* v = hashmap_get(map, &k);
    HT_ASSERT(v != NULL);
    HT_ASSERT(VOID_TO_DOUBLE(v) == 2.0);
  }

  hashmap_free(map);
}

HT_TEST(test_put_double_int, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(double), NULL, NULL,
      sizeof(int), NULL, NULL, HASHMAP_DEFAULT_NBINS,
      hash_double, NULL, compar_double, NULL);
  HT_ASSERT(hashmap_size(map) == 0);

  int i;
  for (i = 0; i < SIZE_OF_MAP; i++) {
    HASHMAP_PUT_TYPE(map, double, int, 4.0 / (i + 1), i);
    HT_ASSERT(hashmap_size(map) == i + 1);
  }

  for (i = 0; i < SIZE_OF_MAP; i++) {
    double k = 4.0 / (i + 1);
    void* v = hashmap_get(map, &k);
    HT_ASSERT(v != NULL);
    HT_ASSERT(VOID_TO_INT(v) == i);
  }

  for (i = 0; i < SIZE_OF_MAP; i++) {
    HASHMAP_PUT_TYPE(map, double, int, 4.0 / (i + 1), i - 1);
  }
  HT_ASSERT(hashmap_size(map) == SIZE_OF_MAP);

  for (i = 0; i < SIZE_OF_MAP; i++) {
    double k = 4.0 / (i + 1);
    void* v = hashmap_get(map, &k);
    HT_ASSERT(v != NULL);
    HT_ASSERT(VOID_TO_INT(v) == i - 1);
  }

  hashmap_free(map);
}

HT_TEST(test_put_string_int, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(char*),
      (dup_f) strdup, free, sizeof(int), NULL, NULL,
      HASHMAP_DEFAULT_NBINS, hash_str, NULL, compar_str, NULL);
  HT_ASSERT(hashmap_size(map) == 0);

  int i;
  char* k = NULL;
  for (i = 0; i < SIZE_OF_MAP; i++) {
    asprintf(&k, "key #%d", i);
    HASHMAP_PUT_TYPE(map, char*, int, k, 5 * i - 3);
    HT_ASSERT(hashmap_size(map) == i + 1);
    free(k);
  }

  HT_ASSERT(hashmap_size(map) == SIZE_OF_MAP);

  for (i = 0; i < SIZE_OF_MAP; i++) {
    asprintf(&k, "key #%d", i);
    void* v = hashmap_get(map, &k);
    HT_ASSERT(v != NULL);
    HT_ASSERT(VOID_TO_INT(v) == 5 * i - 3);
    free(k);
  }

  hashmap_free(map);
}

int main(int argc, char** argv) {
  ht_suit_t* suit = ht_suit_alloc(NULL); 

  ht_option_t option;
  ht_get_option(argc, argv, &option);

  ht_add_test(suit, test_alloc);
  ht_add_test(suit, test_put);
  ht_add_test(suit, test_put_int_double);
  ht_add_test(suit, test_put_double_int);
  ht_add_test(suit, test_put_string_int);

  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

