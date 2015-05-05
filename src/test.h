// test.h
// Test framework
//
// Author : Weipeng He <heweipeng@gmail.com>
// Distributed under the MIT License.

#ifndef TEST_H_
#define TEST_H_

/**
 * what to do when assertion fails
 */
typedef enum {
  H_TEST_CONTINUE,
  H_TEST_GDB,
  H_TEST_STOP
} h_test_onfail_t;

/**
 * test option
 */
typedef struct {
  int silent;
  h_test_onfail_t onfail;
} h_test_option_t;

h_test_option_t H_TEST_DEFAULT_OPTION;

/**
 * test function
 */
typedef void (*h_test_f)(void* param);

/**
 * test suite
 */
typedef struct {
  h_test_f* tests;
  int size;
  int cap;
  void* param;
} h_test_suit_t;

/**
 * allocate memory for a test suit
 */
h_test_suit_t* h_test_suit_alloc(void* param);

/**
 * free a test suit
 */
void h_test_suit_free(h_test_suit_t* suit);

/**
 * add a test to suit
 */
void h_add_test(h_test_suit_t* suit, h_test_f test);

/**
 * run a set of tests with fixtures
 *
 * @return # of failed assertions
 */
int h_run_suit(h_test_suit_t* suit, h_test_option_t* opt);

#define H_ASSERT_EQ_INT(x, y) \
  h_assert((x) == (y), #x" == "#y, __FILE__, __LINE__)

int h_assert(int expr, char* msg, char* file, int line);
// int h_assert_eq_int(int x, int y, char* file, int line);

#endif  // TEST_H_

