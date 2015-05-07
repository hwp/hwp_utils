// hashmap_test.c
// test hash map
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "../src/map.h"
#include "../src/test.h"

HT_TEST(test_alloc, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(int), sizeof(int),
      HASHMAP_DEFAULT_NBINS, hash_int, NULL, compar_int, NULL);
  HT_ASSERT(hashmap_size(map) == 0);
  hashmap_free(map);
}

HT_TEST(test_put, void*) {
  hashmap_t* map = hashmap_alloc(sizeof(int), sizeof(int),
      HASHMAP_DEFAULT_NBINS, hash_int, NULL, compar_int, NULL);
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
  
  HASHMAP_PUT_TYPE(map, int, int, 2 + HASHMAP_DEFAULT_NBINS, -3);
  k = 2;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 3);
  k = 2 + HASHMAP_DEFAULT_NBINS;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == -3);

  HASHMAP_PUT_TYPE(map, int, int, 2, 3214);
  k = 2;
  HT_ASSERT(VOID_TO_INT(hashmap_get(map, &k)) == 3214);

  hashmap_free(map);
}

int main(int argc, char** argv) {
  ht_suit_t* suit = ht_suit_alloc(NULL); 

  ht_option_t option = HT_DEFAULT_OPTION;
  // option.onfail = HT_DEBUG;

  ht_add_test(suit, test_alloc);
  ht_add_test(suit, test_put);

  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

