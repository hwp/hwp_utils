// map.c
// associative data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "map.h"

#include <stdlib.h>
#include <assert.h>

hashmap_t* hashmap_alloc(size_t key_size, size_t value_size,
    size_t nbins, hash_f hash, void* hash_param,
    compar_f compar_key, void* compar_param) {
  hashmap_t* ret = malloc(sizeof(hashmap_t));
  assert(ret);
  
  ret->key_size = key_size;
  ret->value_size = value_size;
  ret->nbins = nbins;
  ret->bins = malloc(ret->nbins * sizeof(darray_t*));
  assert(ret->bins);

  size_t i;
  for (i = 0; i < ret->nbins; i++) {
    ret->bins[i] = darray_alloc(key_size + value_size);
  }

  ret->size = 0;
  ret->hash = hash;
  ret->hash_param = hash_param;
  ret->compar_key = compar_key;
  ret->compar_param = compar_param;

  return ret;
}

void hashmap_free(hashmap_t* obj) {
  if (obj) {
    size_t i;
    for (i = 0; i < obj->nbins; i++) {
      darray_free(obj->bins[i]);
    }
    free(obj->bins);
    free(obj);
  }
}

void hashmap_freeall(hashmap_t* obj, free_f free_key, free_f free_value) {
  // TODO
}

size_t hashmap_size(hashmap_t* obj) {
  return obj->size;
}

void hashmap_put(hashmap_t* obj, void* key, void* value) {
  // TODO
}

void* hashmap_get(hashmap_t* obj, void* key) {
  // TODO
  return NULL;
}

