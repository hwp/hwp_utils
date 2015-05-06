// common.h
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>

/**
 * free function
 */
typedef void (*free_f)(void*);

/**
 * compare function of two objects with parameters
 */
typedef int (*compar_f)(const void*, const void*, void*);

/**
 * hash function with parameters
 */
typedef int (*hash_f)(void* data, void* param);

/**
 * primitive data types
 */
typedef enum {
  DATATYPE_INT,
  DATATYPE_UINT,
  DATATYPE_DOUBLE,
  DATATYPE_PTR
} datatype_t;

/**
 * get size of the type of data
 */
size_t datatype_size(datatype_t type);

/*
 * conversion macros
 */
#define VOID_TO_INT(x) (*(int*) (x))
#define VOID_TO_UINT(x) (*(unsigned int*) (x))
#define VOID_TO_DOUBLE(x) (*(double*) (x))
#define VOID_TO_PTR(x, type) (*(type**) (x))

/**
 * integer comparison function
 */
int compar_int(const void* a, const void* b, void* param);

/**
 * hash function for integer
 */
int hash_int(void* data, void* param);

#endif  // COMMON_H_

