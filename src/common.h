// common.h
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>

/**
 * primitive data types
 */
typedef enum {
  DATATYPE_INT,
  DATATYPE_UINT,
  DATATYPE_FLOAT,
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
#define VOID_TO_FLOAT(x) (*(float*) (x))
#define VOID_TO_DOUBLE(x) (*(double*) (x))
#define VOID_TO_PTR(x, type) (*(type**) (x))

#endif  // COMMON_H_

