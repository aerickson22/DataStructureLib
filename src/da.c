#include "da.h"
#include <stdatomic.h>
#include <string.h>

#define DEFAULT_CAPACITY 10

struct dynamic_array_t{
    size_t size;
    size_t capacity;
    size_t element_size;
    char* data;
};

struct dynamic_array_t* da_init(size_t element_size){
    struct dynamic_array_t* out;
    if(!(out = malloc(sizeof(*out)))){
        return NULL;
    }
    if(!(out->data = malloc(element_size * DEFAULT_CAPACITY))){
        free(out);
        return NULL;
    }
    out->size = 0;
    out->capacity = DEFAULT_CAPACITY;
    out->element_size = element_size;
    return out;
}

int _resize(size_t new_capacity, struct dynamic_array_t* list){
    char* new_sized_data;
    if(!(new_sized_data = realloc(list->data, (list->element_size * new_capacity)))){
        return -1;
    }
    list->data = new_sized_data;
    list->capacity = new_capacity;
    return 0;
}

bool da_is_empty(struct dynamic_array_t* list){
    return list->size == 0;
}

void da_free(struct dynamic_array_t* list){
    free(list->data);
    free(list);
}

int da_push(void* x, struct dynamic_array_t* list){
    if(list->capacity == list->size){
        if((_resize(list->capacity * 2, list))){
            return -1;
        }
    }
    memcpy((list->data + (list->size * list->element_size)), x, list->element_size);
    list->size++;
    return 0;
}

void da_at(void* out, size_t index, struct dynamic_array_t* list){
    if(da_is_empty(list)){
        out = NULL;
        return;
    }
    memcpy(out, ((list->data + (index * list->element_size))), list->element_size);

}

int da_set(size_t index, void* x, struct dynamic_array_t* list){
    if(da_is_empty(list)){
        return -1;
    }
    memcpy(((list->data + (index * list->element_size))), x, list->element_size);
    return 0;
}

void da_remove(void* out, struct dynamic_array_t* list){
    if(da_is_empty(list)){
        return;
    }
    memcpy(out, ((list->data + ((list->size - 1) * list->element_size))), list->element_size);
    list->size--;
}

size_t da_size(struct dynamic_array_t* list){
    return list->size;
}

size_t da_capacity(struct dynamic_array_t* list){
    return list->capacity;
}
