#include "dll.h"
 
struct dll_node_t{
    void* data;
    struct dll_node_t* next;
    struct dll_node_t* prev;
};
 
struct double_linked_list_t{
    struct dll_node_t* head;
    struct dll_node_t* tail;
    size_t size;
    int(*compare)(void* x, void* y);
};
 
struct double_linked_list_t* dll_init(int(*compare)(void* x, void* y)){
    struct double_linked_list_t* out;
    if(!(out = malloc(sizeof(*out)))){
        return NULL;
    }
    out->head = NULL;
    out->tail = NULL;
    out->size = 0;
    out->compare = compare;
    return out;
}
 
void dll_free(struct double_linked_list_t* list){
    struct dll_node_t* curr = list->head;
    struct dll_node_t* prev;
    while(curr){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
}
 
bool dll_is_empty(struct double_linked_list_t* list){
    return list->size == 0;
}
 
int dll_append(void* x, struct double_linked_list_t* list){
    struct dll_node_t* new_node;
    if(!(new_node = malloc(sizeof(*new_node)))){
        return -1;
    }
    new_node->data = x;
    new_node->next = NULL;
    new_node->prev = list->tail;
 
    if(dll_is_empty(list)){
        list->head = new_node;
    }else{
        list->tail->next = new_node;
    }
    list->tail = new_node;
    list->size++;
    return 0;
}
 
int dll_prepend(void* x, struct double_linked_list_t* list){
    struct dll_node_t* new_node;
    if(!(new_node = malloc(sizeof(*new_node)))){
        return -1;
    }
    new_node->data = x;
    new_node->prev = NULL;
    new_node->next = list->head;
 
    if(dll_is_empty(list)){
        list->tail = new_node;
    }else{
        list->head->prev = new_node;
    }
    list->head = new_node;
    list->size++;
    return 0;
}
 
void* dll_remove_head(struct double_linked_list_t* list){
    if(dll_is_empty(list)){
        return NULL;
    }
    struct dll_node_t* curr_head = list->head;
    void* out = curr_head->data;
 
    list->head = curr_head->next;
    if(list->head){
        list->head->prev = NULL;
    }else{
        list->tail = NULL;
    }
    free(curr_head);
    list->size--;
    return out;
}
 
void* dll_remove_tail(struct double_linked_list_t* list){
    if(dll_is_empty(list)){
        return NULL;
    }
    struct dll_node_t* curr_tail = list->tail;
    void* out = curr_tail->data;
 
    list->tail = curr_tail->prev;
    if(list->tail){
        list->tail->next = NULL;
    }else{
        list->head = NULL;
    }
    free(curr_tail);
    list->size--;
    return out;
}
 
bool dll_contains(void* x, struct double_linked_list_t* list){
    struct dll_node_t* curr_l = list->head;
    struct dll_node_t* curr_r = list->tail;
 
    while(curr_l && curr_l != curr_r && curr_l->prev != curr_r){
        if(list->compare(curr_l->data, x) == 0
                || list->compare(curr_r->data, x) == 0){
            return true;
        }
        curr_l = curr_l->next;
        curr_r = curr_r->prev;
    }
    return curr_l && curr_l == curr_r && list->compare(curr_l->data, x) == 0;
}
 
void* dll_get_head(struct double_linked_list_t* list){
    return list->head ? list->head->data : NULL;
}
 
void* dll_get_tail(struct double_linked_list_t* list){
    return list->tail ? list->tail->data : NULL;
}
 
size_t dll_size(struct double_linked_list_t* list){
    return list->size;
}
