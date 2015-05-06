// debug.h
// debug utils
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef DEBUG_H_
#define DEBUG_H_

/**
 * register for invoking gdb on termination signals cathed.
 */
void debug_init(void);

/**
 * fork a process for debuging with gdb
 */
void invoke_gdb(void);

#endif  // DEBUG_H_

