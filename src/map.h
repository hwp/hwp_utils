// map.h
// associative data structures
//
// Author : Weipeng He <heweipeng@gmail.com>
// Copyright (c) 2015, All rights reserved.

#ifndef HWP_UTIL_MAP_H_
#define HWP_UTIL_MAP_H_

#include "common.h"
#include "list.h"

#define HASHMAP_DEFAULT_NBINS 10007

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
   * the (key) bins
   */
  darray_t** keys;

  /**
   * the (value) bins
   */
  darray_t** values;

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
 * allocate a hash map
 *
 * @param key_size size of the key (bytes)
 * @param key_dup 
 *   if not NULL duplicate key data when adding elements,
 *     namely when hashmap_put() is called and the key is
 *     new.
 * @param key_free
 *   if not NULL free key data when hashmap_free() is called.
 * @param value_size size of the value (bytes)
 * @param value_dup 
 *   if not NULL duplicate value data when adding elements.
 * @param value_free
 *   if not NULL free value data when hashmap_free() is 
 *   called or existing key-value pair is changed.
 * @param nbins number of bins, use HASHMAP_DEFAULT_NBINS
 *   as default.
 * @param hash hash function for the key
 * @param hash_param the parameter for the hash function
 */
hashmap_t* hashmap_alloc(size_t key_size, dup_f key_dup,
    free_f key_free, size_t value_size, dup_f value_dup,
    free_f value_free, size_t nbins, hash_f hash, void* hash_param,
    compar_f compar_key, void* compar_param);

/**
 * free memory of a hash map
 */
void hashmap_free(hashmap_t* map);

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

#define HASHMAP_FOR(map, ktype, key, vtype, value) \
  { \
    int _hwp_util_i, _hwp_util_j; \
    for (_hwp_util_i = 0; _hwp_util_i < map->nbins; _hwp_util_i++) { \
      darray_t* _hwp_util_k = map->keys[_hwp_util_i]; \
      darray_t* _hwp_util_v = map->values[_hwp_util_i]; \
      for (_hwp_util_j = 0; _hwp_util_j < darray_size(_hwp_util_k); _hwp_util_j++) { \
        ktype key = VOID_TO_TYPE(darray_get(_hwp_util_k, _hwp_util_j), ktype); \
        vtype value = VOID_TO_TYPE(darray_get(_hwp_util_v, _hwp_util_j), vtype);

#define HASHMAP_ENDFOR } } }

#endif  // HWP_UTIL_MAP_H_

