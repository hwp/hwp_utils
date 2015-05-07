// map.c
// associative data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HASHMAP_ADDR_KEY(map, ibin, ielem) \
  darray_get((map)->bins[ibin], ielem)

#define HASHMAP_ADDR_VALUE(map, ibin, ielem) \
  PTR_OFFSET(darray_get((map)->bins[ibin], ielem), (map)->key_size)

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

void hashmap_free(hashmap_t* map) {
  if (map) {
    size_t i;
    for (i = 0; i < map->nbins; i++) {
      darray_free(map->bins[i]);
    }
    free(map->bins);
    free(map);
  }
}

void hashmap_freeall(hashmap_t* map, free_f free_key, free_f free_value) {
  // TODO
}

size_t hashmap_size(hashmap_t* map) {
  return map->size;
}

static void hashmap_search(hashmap_t* map, void* key, size_t* ibin, size_t* ielem, int* found) {
  *ibin = (size_t) map->hash(key, map->hash_param) % map->nbins;
  size_t bin_size = darray_size(map->bins[*ibin]);
  for (*ielem = 0; *ielem < bin_size; (*ielem)++) {
    if (map->compar_key(HASHMAP_ADDR_KEY(map, *ibin, *ielem),
          key, map->compar_param) == 0) {
      break;
    }
  }

  *found = *ielem < bin_size;
}

void hashmap_put(hashmap_t* map, void* key, void* value) {
  size_t ibin;
  size_t ielem;
  int found;
  hashmap_search(map, key, &ibin, &ielem, &found);

  if (found) {      // key exist, replace
    memcpy(HASHMAP_ADDR_VALUE(map, ibin, ielem), value, map->value_size);
  }
  else {            // new key, add
    ielem = darray_increase_size(map->bins[ibin]);
    memcpy(HASHMAP_ADDR_KEY(map, ibin, ielem), key, map->key_size);
    memcpy(HASHMAP_ADDR_VALUE(map, ibin, ielem), value, map->value_size);
    map->size++;
  }
}

void* hashmap_get(hashmap_t* map, void* key) {
  size_t ibin;
  size_t ielem;
  int found;
  hashmap_search(map, key, &ibin, &ielem, &found);

  if (found) {
    return HASHMAP_ADDR_VALUE(map, ibin, ielem);
  }
  else {
    return NULL;
  }
}

