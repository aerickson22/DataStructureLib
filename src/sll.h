#ifndef SLL_H
#define SLL_H

#include "common.h"

typedef struct single_linked_list_t* single_linked_list_t;

single_linked_list_t sll_init(int(*compare)(void* x, void* y));
void sll_free(single_linked_list_t list);
int sll_append(void* x, single_linked_list_t list);
int sll_prepend(void* x, single_linked_list_t list);
void* sll_remove_head(single_linked_list_t list);
bool sll_contains(void* x, single_linked_list_t list);
void* sll_get_head(single_linked_list_t list);
size_t sll_size(single_linked_list_t list);
bool sll_is_empty(single_linked_list_t list);

#endif
