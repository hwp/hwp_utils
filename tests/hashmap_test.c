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

int main(int argc, char** argv) {
  ht_suit_t* suit = ht_suit_alloc(NULL); 

  ht_option_t option = HT_DEFAULT_OPTION;
  // option.onfail = HT_DEBUG;

  ht_add_test(suit, test_alloc);

  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

