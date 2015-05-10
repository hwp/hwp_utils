// test.c
// Test framework
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "test.h"

#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

static ht_option_t* option;
char* name_ptr;

ht_suit_t* ht_suit_alloc(void* param) {
  ht_suit_t* ret = malloc(sizeof(ht_suit_t));
  assert(ret);

  ret->size = 0;
  ret->cap = 10;
  ret->param = param;

  ret->tests = malloc(ret->cap * sizeof(ht_test_f));
  assert(ret->tests);

  return ret;
}

void ht_suit_free(ht_suit_t* suit) {
  if (suit) {
    free(suit->tests);
    free(suit);
  }
}

void ht_add_test(ht_suit_t* suit, ht_test_f test) {
  if (suit->size == suit->cap) {
    suit->cap *= 2;
    suit->tests = realloc(suit->tests, suit->cap * sizeof(ht_test_f));
  }
  suit->tests[suit->size] = test;
  suit->size++;
}

int ht_run_suit(ht_suit_t* suit, ht_option_t* opt) {
  int fail_counter = 0;
  option = opt;
  pid_t child_pid, wpid;
  int status;
  
  name_ptr = mmap(NULL, sizeof(char) * HT_NAME_MAXLEN, PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  if (option->onfail == HT_DEBUG) {
    debug_init();
  }

  int i;
  for (i = 0; i < suit->size; i++) {
    fflush(stdout);
    fflush(stderr);
    child_pid = fork();
    if (child_pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } 
    else if (child_pid == 0) { /* This is the child */
      suit->tests[i](suit->param);
      fflush(stdout);
      fflush(stderr);
      _exit(EXIT_SUCCESS);
    }
    else {                     /* This is the parent */
      do {
        wpid = waitpid(child_pid, &status, WUNTRACED);
        if (wpid == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
          if (WEXITSTATUS(status) != EXIT_SUCCESS) {
            fail_counter++;
          }
          else {
            if (!option->silent) {
              printf("%s: passed\n", __HT_NAME__);
            }
          }
        } 
        else if (WIFSIGNALED(status)) {
          int sig = WTERMSIG(status);
          char* desc = strsignal(sig);
          if (!option->silent) {
            printf("%s: killed with signal %d: %s\n", __HT_NAME__, sig, desc);
          }
          fail_counter++;
        }
        else if (WIFSTOPPED(status)) {
          int sig = WSTOPSIG(status);
          char* desc = strsignal(sig);
          if (!option->silent) {
            printf("%s: stopped with signal %d: %s\n", __HT_NAME__, sig, desc);
          }
        }
        else {    /* Non-standard case -- may never happen */
          if (!option->silent) {
            printf("Unexpected status (0x%x)\n", status);
          }
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  }

  munmap(name_ptr, sizeof(char) * HT_NAME_MAXLEN);

  if (!option->silent) {
    printf("**** %d failed / %d tested ****\n", fail_counter, suit->size);
  }

  return fail_counter;
}

int ht_assert(int expr, char* msg, const char* file, unsigned int line) {
  if (!expr) {
    if (!option->silent) {
      printf("%s: %s:%d: assertion failed : %s\n", __HT_NAME__, file, line, msg);
    }

    if (option->onfail == HT_ABORT) {
      exit(EXIT_FAILURE);
    }
    else {
      invoke_gdb();
      exit(EXIT_FAILURE);
    }
  }

  return expr;
}

void ht_get_option(int argc, char** argv, ht_option_t* option) {
  ht_option_t def = HT_DEFAULT_OPTION;
  *option = def;

  int showhelp = 0;
  int opt;
  while ((opt = getopt(argc, argv, "sdh")) != -1) {
    switch (opt) {
      case 'h':
        showhelp = 1;
        break;
      case 's':
        option->silent = 1;
        break;
      case 'd':
        option->onfail = HT_DEBUG;
        break;
      default:
        showhelp = 1;
        break;
    }
  }

  if (showhelp) {
    printf("Usage: %s [-s] [-d]\n\t-s silent mode\n\t-d debug on fail\n", argv[0]);
    exit(EXIT_FAILURE);   
  }
}

