// debug.c
// debut utils
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void hwp_sigaction(int signum, siginfo_t* siginfo,
    void* context) {
  fprintf(stderr, "Signal \"%s\" Catched (No: %d, Code: %d)\n",
      strsignal(siginfo->si_signo), siginfo->si_signo, siginfo->si_code);
  fprintf(stderr, "Type any key to attach to GDB\n");
  getchar();
  invoke_gdb();
  exit(EXIT_FAILURE);
}

void debug_init(void) {
  struct sigaction act;
  memset(&act, '\0', sizeof(act));
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = hwp_sigaction;

  if (sigaction(SIGABRT, &act, NULL) < 0
      || sigaction(SIGSEGV, &act, NULL) < 0) {  
    perror("sigaction");  
    exit(EXIT_FAILURE);  
  }  
}

void invoke_gdb(void) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid) {
    int status, wpid;
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
      if (wpid == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  else {
    char s[13];
    sprintf(s, "%d", getppid());
    execlp("gdb", "gdb", "-p", s, NULL);
  }
}

