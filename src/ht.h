#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "common.h"
#include <stddef.h>

typedef struct hash_table_t* hash_table_t;

hash_table_t ht_init(size_t(*hash_func)(void* k), int(*compare_key)(void* x, void* y));
void ht_free(hash_table_t ht);
int ht_put(void* key, void* val, hash_table_t ht);
void* ht_get(void* key, hash_table_t ht);
void* ht_remove(void* key, hash_table_t ht);
bool ht_has(void* key, hash_table_t ht);
size_t ht_size(hash_table_t ht);
size_t ht_capacity(hash_table_t ht);
bool ht_is_empty(hash_table_t ht);

#endif
