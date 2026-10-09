#ifndef RINGBUFF_H
#define RINGBUFF_H

#include "common.h"

typedef struct ring_buffer_t* ring_buffer_t;

ring_buffer_t ringbuff_init(size_t capacity, size_t element_size);
void ringbuff_free(ring_buffer_t buff);
int ringbuff_push(void* x, ring_buffer_t buff);
void ringbuff_pop(void* out, ring_buffer_t buff);
void* ringbuff_peek(ring_buffer_t buff);
bool ringbuff_is_empty(ring_buffer_t buff);
bool ringbuff_is_full(ring_buffer_t buff);
size_t ringbuff_size(ring_buffer_t buff);

#endif
