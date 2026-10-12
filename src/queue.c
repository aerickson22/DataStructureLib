#include "queue.h"
#include "dll.h"

struct queue_t {
    double_linked_list_t data;
};

struct queue_t* queue_init(int(*compare)(void* x, void* y)){
    struct queue_t* out;
    if(!(out = malloc(sizeof(*out)))){
        return NULL;
    }
    if(!(out->data = dll_init(compare))){
        free(out);
        return NULL;
    }
    return out;
}

void queue_free(struct queue_t* q){
    dll_free(q->data);
    free(q);
}
int queue_offer(void* x, struct queue_t* q){
    return dll_append(x, q->data);
}
void* queue_poll(struct queue_t* q){
    return dll_remove_head(q->data);
}
void* queue_peek(struct queue_t* q){
    return dll_get_head(q->data);
}

size_t queue_size(struct queue_t* q){
    return dll_size(q->data);
}

bool queue_is_empty(struct queue_t* q){
    return dll_is_empty(q->data);
}


