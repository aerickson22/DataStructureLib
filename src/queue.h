#ifndef QUEUE_H
#define QUEUE_H

#include "dll.h"

typedef struct queue_t* queue_t;

queue_t queue_init(int(*compare)(void* x, void* y));
void queue_free(queue_t q);
int queue_offer(void* x, queue_t q);
void* queue_poll(queue_t q);
void* queue_peek(queue_t q);
size_t queue_size(queue_t q);
bool queue_is_empty(queue_t q);

#endif
