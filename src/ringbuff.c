#include "ringbuff.h"
#include <string.h>

struct ring_buffer_t {
  size_t size;
  size_t capacity;
  size_t element_size;
  signed long long head;
  signed long long tail;
  char *data;
};

struct ring_buffer_t *ringbuff_init(size_t capacity, size_t element_size) {
  struct ring_buffer_t *out;
  if (!(out = malloc(sizeof(*out)))) {
    return NULL;
  }
  if (!(out->data = malloc(element_size * capacity))) {
    free(out);
    return NULL;
  }
  out->size = 0;
  out->capacity = capacity;
  out->element_size = element_size;
  out->head = -1;
  out->tail = -1;
  return out;
}

bool ringbuff_is_empty(struct ring_buffer_t *buff) {
  return buff->head == -1;
}

bool ringbuff_is_full(struct ring_buffer_t *buff) {
  return (((signed long long)((buff->tail + 1) % buff->capacity)) == ((signed long long)buff->head));
}

void ringbuff_free(struct ring_buffer_t *buff) {
  free(buff->data);
  free(buff);
}

int ringbuff_push(void *x, struct ring_buffer_t *buff) {
  if (ringbuff_is_full(buff)) {
    return -1;
  }
  if (ringbuff_is_empty(buff)) {
    buff->head = 0;
  }
  buff->tail = (buff->tail + 1) % buff->capacity;
  memcpy((buff->data + (buff->tail * buff->element_size)), x,
         buff->element_size);
  buff->size++;
  return 0;
}

void ringbuff_pop(void* out, struct ring_buffer_t *buff) {
  if (ringbuff_is_empty(buff)) {
    return;
  } 
  memcpy(out, (buff->data + (buff->head * buff->element_size)),
         buff->element_size);
  buff->head = (buff->head + 1) % buff->capacity;
  buff->size--;
  if (buff->size == 0) {
    buff->head = -1;
    buff->tail = -1;
  }
}

void *ringbuff_peek(struct ring_buffer_t *buff) {
  if (buff->size == 0) {
    return NULL;
  }
  return buff->data + (buff->head * buff->element_size);
}

size_t ringbuff_size(struct ring_buffer_t *buff) { 
    return buff->size; 
}
