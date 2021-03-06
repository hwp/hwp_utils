// common.h
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef HWP_UTIL_COMMON_H_
#define HWP_UTIL_COMMON_H_

#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>

/**
 * free function
 */
typedef void (*free_f)(void*);

/**
 * duplicate function
 */
typedef void* (*dup_f)(const void*);

/**
 * compare function of two objects with parameters
 */
typedef int (*compar_f)(const void*, const void*, void*);

/**
 * hash function with parameters
 */
typedef uint32_t (*hash_f)(const void* data, void* param);

/*
 * conversion macros
 */
#define VOID_TO_INT(x) (*(int*) (x))
#define VOID_TO_UINT(x) (*(unsigned int*) (x))
#define VOID_TO_DOUBLE(x) (*(double*) (x))
#define VOID_TO_WCHAR(x) (*(wchar_t*) (x))
#define VOID_TO_TYPE(x, type) (*(type*) (x))
#define VOID_TO_PTR(x, type) (*(type**) (x))

/**
 * get offset address by bytes
 */
#define PTR_OFFSET(ptr, nbytes) ((char*) (ptr) + (nbytes))

/**
 * integer comparison function
 */
int compar_int(const void* a, const void* b, void* param);

/**
 * integer comparison function
 */
int compar_double(const void* a, const void* b, void* param);

/**
 * string (char*) comparison function
 */
int compar_str(const void* a, const void* b, void* param);

/**
 * wide char comparison function
 */
int compar_wchar(const void* a, const void* b, void* param);

/**
 * wide char string (wchar_t*) comparison function
 */
int compar_wcstr(const void* a, const void* b, void* param);

/**
 * hash function for integer
 */
uint32_t hash_int(const void* data, void* param);

/**
 * hash function for double
 */
uint32_t hash_double(const void* data, void* param);

/**
 * hash function for string (char*)
 */
uint32_t hash_str(const void* data, void* param);

/**
 * hash function for wide char (wchar_t)
 */
uint32_t hash_wchar(const void* data, void* param);

/**
 * hash function for wide char string (wchar_t*)
 */
uint32_t hash_wcstr(const void* data, void* param);

/**
 * rotation hash function for binary data
 * @param size data size (bytes)
 */
uint32_t hash_rotate(const void* data, size_t* size);

/**
 * escape special characters in the string for printing
 *
 * @return the escaped string, should be freed using free()
 */
char* escape_str(char* str);

/**
 * escape special characters in the wide string for printing
 *
 * @return the escaped string, should be freed using free()
 */
wchar_t* escape_wcstr(wchar_t* str);

#endif  // HWP_UTIL_COMMON_H_

