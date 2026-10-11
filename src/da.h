#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "common.h"

typedef struct dynamic_array_t* dynamic_array_t;

dynamic_array_t da_init(size_t element_size);
void da_free(dynamic_array_t list);
int da_push(void* x, dynamic_array_t list);
void da_at(void* out, size_t index, dynamic_array_t list);
int da_set(size_t index, void* x, dynamic_array_t list);
void da_remove(void* out, dynamic_array_t list);
size_t da_size(dynamic_array_t list);
bool da_is_empty(dynamic_array_t list);
size_t da_capacity(dynamic_array_t list);

#endif
