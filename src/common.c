// common.c
// Common features
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "common.h"

#include <string.h>
#include <wchar.h>
#include <assert.h>

int compar_int(const void* a, const void* b, void* param) {
  return VOID_TO_INT(a) - VOID_TO_INT(b);
}

#define fsign(x) ((int)(((x) > 0.0) - ((x) < 0.0)))

int compar_double(const void* a, const void* b, void* param) {
  return fsign(VOID_TO_DOUBLE(a) - VOID_TO_DOUBLE(b));
}

int compar_str(const void* a, const void* b, void* param) {
  return strcmp(VOID_TO_PTR(a, const char), VOID_TO_PTR(b, const char));
}

int compar_wchar(const void* a, const void* b, void* param) {
  return VOID_TO_WCHAR(a) - VOID_TO_WCHAR(b);
}

int compar_wcstr(const void* a, const void* b, void* param) {
  return wcscmp(VOID_TO_PTR(a, const wchar_t), VOID_TO_PTR(b, const wchar_t));
}

uint32_t hash_int(const void* data, void* param) {
  return (uint32_t) VOID_TO_INT(data);
}

uint32_t hash_double(const void* data, void* param) {
  size_t len = sizeof(double);
  return hash_rotate(data, &len);
}

uint32_t hash_str(const void* data, void* param) {
  const char* str = VOID_TO_PTR(data, const char);
  size_t len = strlen(str);
  return hash_rotate(str, &len);
}

uint32_t hash_wchar(const void* data, void* param) {
  return (uint32_t) VOID_TO_WCHAR(data);
}

uint32_t hash_wcstr(const void* data, void* param) {
  const wchar_t* str = VOID_TO_PTR(data, const wchar_t);
  size_t len = wcslen(str) * sizeof(wchar_t);
  return hash_rotate(str, &len);
}

uint32_t hash_rotate(const void* data, size_t* size) {
  uint32_t hash = (uint32_t) *size;
  const char* v = data;
  size_t i;
  for (i = 0; i < *size; i++) {
    hash = ((hash << 5) + hash) + v[i];
  }
  return hash;
}

char* escape_str(char* str) {
  size_t len = strlen(str);
  char* buf = malloc(len * 2 + 1);
  char* p = buf;
  char c;

  while ((c = *(str++)) != '\0') {
    switch (c) {
      case '\n':
        *(p++) = '\\';
        *(p++) = 'n';
        break;
      case '\r':
        *(p++) = '\\';
        *(p++) = 'r';
        break;
      case '\a':
        *(p++) = '\\';
        *(p++) = 'a';
        break;
      case '\v':
        *(p++) = '\\';
        *(p++) = 'v';
        break;
      case '\t':
        *(p++) = '\\';
        *(p++) = 't';
        break;
      case '\f':
        *(p++) = '\\';
        *(p++) = 'f';
        break;
      case '\b':
        *(p++) = '\\';
        *(p++) = 'b';
        break;
      default:
        *(p++) = c;
        break;
    }
  }
  
  *p = '\0';
  return buf;
}

wchar_t* escape_wcstr(wchar_t* str) {
  size_t len = wcslen(str);
  wchar_t* buf = malloc(sizeof(wchar_t) * (len * 2 + 1));
  wchar_t* p = buf;
  wchar_t c;

  while ((c = *(str++)) != L'\0') {
    switch (c) {
      case L'\n':
        *(p++) = L'\\';
        *(p++) = L'n';
        break;
      case L'\r':
        *(p++) = L'\\';
        *(p++) = L'r';
        break;
      case L'\a':
        *(p++) = L'\\';
        *(p++) = L'a';
        break;
      case L'\v':
        *(p++) = L'\\';
        *(p++) = L'v';
        break;
      case L'\t':
        *(p++) = L'\\';
        *(p++) = L't';
        break;
      case L'\f':
        *(p++) = L'\\';
        *(p++) = L'f';
        break;
      case L'\b':
        *(p++) = L'\\';
        *(p++) = L'b';
        break;
      default:
        *(p++) = c;
        break;
    }
  }
  
  *p = L'\0';
  return buf;
}

