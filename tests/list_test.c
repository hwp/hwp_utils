// list_test.c
// test list interfaces
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "../src/list.h"
#include "../src/test.h"

void test_alloc(void* param) {
  darray_t* a = darray_alloc(DATATYPE_INT);
  H_ASSERT_EQ_INT(darray_size(a), 1);
  darray_free(a);
}

int main(int argc, char** argv) {
  h_test_suit_t* suit = h_test_suit_alloc(NULL);

  h_add_test(suit, test_alloc);
  int ret = h_run_suit(suit, &H_TEST_DEFAULT_OPTION);

  h_test_suit_free(suit);

  return ret;
}

