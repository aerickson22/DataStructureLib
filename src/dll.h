#ifndef DLL_H
#define DLL_H

#include "common.h"

struct double_linked_list_t;

typedef struct double_linked_list_t* double_linked_list_t;

struct double_linked_list_t* dll_init(int(*compare)(void* x, void* y));
void dll_free(struct double_linked_list_t* list);
bool dll_is_empty(struct double_linked_list_t* list);
int dll_append(void* x, struct double_linked_list_t* list);
int dll_prepend(void* x, struct double_linked_list_t* list);
void* dll_remove_head(struct double_linked_list_t* list);
void* dll_remove_tail(struct double_linked_list_t* list);
bool dll_contains(void* x, struct double_linked_list_t* list);
void* dll_get_head(struct double_linked_list_t* list);
void* dll_get_tail(struct double_linked_list_t* list);
size_t dll_size(struct double_linked_list_t* list);

#endif
