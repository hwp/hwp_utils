// test.h
// Test framework
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef TEST_H_
#define TEST_H_

#include <string.h>

/**
 * what to do when assertion fails
 */
typedef enum {
  HT_ABORT,
  HT_DEBUG
} ht_onfail_t;

/**
 * test option
 */
typedef struct {
  int silent;
  ht_onfail_t onfail;
} ht_option_t;

#define HT_DEFAULT_OPTION {0, HT_ABORT}

/**
 * test function
 */
typedef void (*ht_test_f)(void* param);

char* name_ptr;
#define HT_NAME_MAXLEN 128
#define __HT_NAME__ (name_ptr)

#define HT_TEST(name, param_type) \
  static void ht_test_##name(param_type param); \
  void name(void* param) { \
    strncpy(__HT_NAME__, #name, HT_NAME_MAXLEN); \
    ht_test_##name(param); \
  } \
  void ht_test_##name(param_type param)

/**
 * test suite
 */
typedef struct {
  ht_test_f* tests;
  int size;
  int cap;
  void* param;
} ht_suit_t;

/**
 * allocate memory for a test suit
 */
ht_suit_t* ht_suit_alloc(void* param);

/**
 * free a test suit
 */
void ht_suit_free(ht_suit_t* suit);

/**
 * add a test to suit
 */
void ht_add_test(ht_suit_t* suit, ht_test_f test);

/**
 * run a set of tests with fixtures
 *
 * @return # of failed assertions
 */
int ht_run_suit(ht_suit_t* suit, ht_option_t* opt);

#define HT_ASSERT(expr) \
  ht_assert(expr, #expr, __FILE__, __LINE__)

int ht_assert(int expr, char* msg, const char* file, unsigned int line);

#endif  // TEST_H_

