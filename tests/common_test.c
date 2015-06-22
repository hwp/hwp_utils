// common_test.c
// test common.c 
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "../src/common.h"
#include "../src/test.h"

#include <stdio.h>
#include <wchar.h>

HT_TEST(test_hash_str, void*) {
  char* buf1 = NULL;
  char* buf2 = NULL;
  int i;
  for (i = 0; i < 40; i++) {
    asprintf(&buf1, "key #%d", i);
    asprintf(&buf2, "key #%d", i);
    HT_ASSERT(hash_str(&buf1, NULL) == hash_str(&buf2, NULL));
  }

  free(buf1);
  free(buf2);
}

HT_TEST(test_compar_str, void*) {
  char* buf1 = NULL;
  char* buf2 = NULL;
  int i;
  for (i = 0; i < 40; i++) {
    asprintf(&buf1, "key #%d", i);
    asprintf(&buf2, "key #%d", i);
    HT_ASSERT(compar_str(&buf1, &buf2, NULL) == 0);
  }

  asprintf(&buf1, "a");
  asprintf(&buf2, "b");
  HT_ASSERT(compar_str(&buf1, &buf2, NULL) < 0);

  free(buf1);
  free(buf2);
}

HT_TEST(test_hash_wcstr, void*) {
  wchar_t buf1[21];
  wchar_t buf2[21];
  wchar_t* t1 = buf1;
  wchar_t* t2 = buf2;
  int i;
  for (i = 0; i < 40; i++) {
    swprintf(buf1, 20, L"key #%d", i);
    swprintf(buf2, 20, L"key #%d", i);
    HT_ASSERT(hash_wcstr(&t1, NULL) == hash_wcstr(&t2, NULL));
  }
}

HT_TEST(test_compar_wcstr, void*) {
  wchar_t buf1[21];
  wchar_t buf2[21];
  wchar_t* t1 = buf1;
  wchar_t* t2 = buf2;
  int i;
  for (i = 0; i < 40; i++) {
    swprintf(buf1, 20, L"key #%d", i);
    swprintf(buf2, 20, L"key #%d", i);
    HT_ASSERT(compar_str(&t1, &t2, NULL) == 0);
  }

  swprintf(buf1, 20, L"a");
  swprintf(buf2, 20, L"b");
  HT_ASSERT(compar_str(&t1, &t2, NULL) < 0);
}

int main(int argc, char** argv) {
  ht_suit_t* suit = ht_suit_alloc(NULL); 

  ht_option_t option;
  ht_get_option(argc, argv, &option);

  ht_add_test(suit, test_hash_str);
  ht_add_test(suit, test_compar_str);
  ht_add_test(suit, test_hash_wcstr);
  ht_add_test(suit, test_compar_wcstr);

  int ret = ht_run_suit(suit, &option);
  ht_suit_free(suit);

  if (ret == 0) {
    exit(EXIT_SUCCESS);
  }
  else {
    exit(EXIT_FAILURE);
  }
}

