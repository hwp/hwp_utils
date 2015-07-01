// map.c
// associative data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

hashmap_t* hashmap_alloc(size_t key_size, dup_f key_dup,
    free_f key_free, size_t value_size, dup_f value_dup,
    free_f value_free, size_t nbins, hash_f hash, void* hash_param,
    compar_f compar_key, void* compar_param) {
  hashmap_t* ret = malloc(sizeof(hashmap_t));
  assert(ret);

  ret->key_size = key_size;
  ret->value_size = value_size;
  ret->nbins = nbins;
  ret->keys = calloc(ret->nbins, sizeof(darray_t*));
  ret->values = calloc(ret->nbins, sizeof(darray_t*));
  ret->key_dup = key_dup;
  ret->key_free = key_free;
  ret->value_dup = value_dup;
  ret->value_free = value_free;
  assert(ret->keys && ret->values);

  ret->size = 0;
  ret->hash = hash;
  ret->hash_param = hash_param;
  ret->compar_key = compar_key;
  ret->compar_param = compar_param;

  return ret;
}

void hashmap_free(hashmap_t* map) {
  if (map) {
    size_t i;
    for (i = 0; i < map->nbins; i++) {
      darray_free(map->keys[i]);
      darray_free(map->values[i]);
    }
    free(map->keys);
    free(map->values);
    free(map);
  }
}

size_t hashmap_size(hashmap_t* map) {
  return map->size;
}

static void hashmap_search(hashmap_t* map, void* key, size_t* ibin, size_t* ielem, int* found) {
  *ibin = (size_t) map->hash(key, map->hash_param) % map->nbins;
  darray_t* kbin = map->keys[*ibin];
  if (kbin) {
    size_t bin_size = darray_size(kbin);
    for (*ielem = 0; *ielem < bin_size; (*ielem)++) {
      if (map->compar_key(darray_get(kbin, *ielem),
            key, map->compar_param) == 0) {
        break;
      }
    }

    *found = *ielem < bin_size;
  }
  else {
    *ielem = 0;
    *found = 0;
  }
}

void hashmap_put(hashmap_t* map, void* key, void* value) {
  size_t ibin;
  size_t ielem;
  int found;
  hashmap_search(map, key, &ibin, &ielem, &found);

  if (found) {      // key exist, replace
    darray_set(map->values[ibin], ielem, value);
  }
  else {            // new key, add
    if (map->keys[ibin] == NULL) {
      assert(map->values[ibin] == NULL);
      map->keys[ibin] = darray_alloc(map->key_size,
          map->key_dup, map->key_free);
      map->values[ibin] = darray_alloc(map->value_size,
          map->value_dup, map->value_free);
    }
    darray_push_back(map->keys[ibin], key);
    darray_push_back(map->values[ibin], value);
    map->size++;
  }
}

void* hashmap_get(hashmap_t* map, void* key) {
  size_t ibin;
  size_t ielem;
  int found;
  hashmap_search(map, key, &ibin, &ielem, &found);

  if (found) {
    return darray_get(map->values[ibin], ielem);
  }
  else {
    return NULL;
  }
}

