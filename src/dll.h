#ifndef DLL_H
#define DLL_H

#include "common.h"

typedef struct double_linked_list_t* double_linked_list_t;

double_linked_list_t dll_init(int(*compare)(void* x, void* y));
void dll_free(double_linked_list_t list);
bool dll_is_empty(double_linked_list_t list);
int dll_append(void* x, double_linked_list_t list);
int dll_prepend(void* x, double_linked_list_t list);
void* dll_remove_head(double_linked_list_t list);
void* dll_remove_tail(double_linked_list_t list);
bool dll_contains(void* x, double_linked_list_t list);
void* dll_get_head(double_linked_list_t list);
void* dll_get_tail(double_linked_list_t list);
size_t dll_size(double_linked_list_t list);

#endif
