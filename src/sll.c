#include "sll.h"
#include "common.h"

struct sll_node_t{
    void* data;
    struct sll_node_t* next; 
};

struct single_linked_list_t{
    size_t size;
    struct sll_node_t* head;
    int(*compare)(void* x, void* y);
};

struct single_linked_list_t* sll_init(int(*compare)(void* x, void* y)){
    if(!compare){
        return NULL;
    }
    single_linked_list_t* out;
    if(!(out = malloc(sizeof(*out)))){
        return NULL;
    }
    out->size = 0;
    out->head = NULL;
    out->compare = compare;
    return out;
}

void sll_free(struct single_linked_list_t* list){
    struct sll_node_t* curr = list->head;
    struct sll_node_t* prev;
    while(curr){
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(curr);
    free(list);
}

int sll_append(void* x, struct single_linked_list_t* list){
    if(!x || !list){
        return -1;
    }

    struct sll_node_t* new_node;    
    if(!(new_node = malloc(sizeof(*new_node)))){
        return -1;
    }
    new_node->data = x;
    new_node->next = NULL;

    if(sll_is_empty(list)){
        list->head = new_node;
    }else{
        struct sll_node_t* curr = list->head;
        while(curr->next){
            curr = curr->next;
        }
        curr->next = new_node;
    }
    list->size++;
    return 0;
}

int sll_prepend(void* x, struct single_linked_list_t* list){
    if(!x || !list){
        return -1;
    }

    struct sll_node_t* new_node;    
    if(!(new_node = malloc(sizeof(*new_node)))){
        return -1;
    }
    new_node->data = x;
    new_node->next = list->head;

    list->head = new_node;
    list->size++;
    return 0;
}

void* sll_remove_head(struct single_linked_list_t* list){
    if(sll_is_empty(list)){
        return NULL;
    }
    struct sll_node_t* curr_head = list->head;
    void* out = list->head->data;
    list->head = curr_head->next;
    curr_head->next = NULL;
    free(curr_head);
    list->size--;
    return out;
}

bool sll_contains(void* x, single_linked_list_t* list){
    if(sll_is_empty(list)){
        return false;
    }
    struct sll_node_t* curr = list->head;
    while(curr){
        if(list->compare(x, curr->data) == 0){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void* sll_get_head(struct single_linked_list_t* list){
    return list->head->data;
}

size_t sll_size(struct single_linked_list_t* list){
    return list->size;
}

bool sll_is_empty(struct single_linked_list_t* list){
    return !list->head;
}
