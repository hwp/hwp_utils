// map.h
// associative data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef MAP_H_
#define MAP_H_

#include "common.h"
#include "list.h"

#define HASHMAP_DEFAULT_NBINS 3001

/**
 * hash map
 */
typedef struct {
  /**
   * key size 
   */
  size_t key_size;

  /**
   * value size 
   */
  size_t value_size;
  
  /**
   * # of bins
   */
  size_t nbins;

  /**
   * # of entries
   */
  size_t size;

  /**
   * the bins
   */
  darray_t** bins;

  /**
   * hash function
   */
  hash_f hash;

  /**
   * parameter for the hash function
   */
  void* hash_param;

  /**
   * function for compare key
   */ 
  compar_f compar_key;

  /**
   * parameter for the compare function
   */
  void* compar_param;
} hashmap_t;

/**
 * create for a hash map
 */
hashmap_t* hashmap_alloc(size_t key_size, size_t value_size,
    size_t nbins, hash_f hash, void* hash_param,
    compar_f compar_key, void* compar_param);

/**
 * free memory of a hash map
 */
void hashmap_free(hashmap_t* map);

/**
 * free memory of a hash map and the elements
 *
 * if free_key or free_value is NULL, then the space pointed with
 *   the key or the value of the entries will not be freed.
 */
void hashmap_freeall(hashmap_t* map, free_f free_key, free_f free_value);

/**
 * # of entries
 */
size_t hashmap_size(hashmap_t* map);

/**
 * add an entry
 *
 * replace existing entry if the key already exist
 */
void hashmap_put(hashmap_t* map, void* key, void* value);

#define HASHMAP_PUT_TYPE(map, ktype, vtype, key, value) \
  do { \
    ktype _hwp_util_k = key; \
    vtype _hwp_util_v = value; \
    hashmap_put(map, &_hwp_util_k, &_hwp_util_v); \
  } while (0)

/**
 * get an entry according to key
 *
 * @return NULL if entry not exist
 */
void* hashmap_get(hashmap_t* map, void* key);

#endif  // MAP_H_

