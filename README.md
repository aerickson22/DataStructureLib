# Data Structures Library
 
- This is a simple Data Structures Static Library in C
- List includes and is limited to:
  - Single Linked List
  - Double Linked List
  - Ring Buffer
  - Dynamic Array
  - Queue
  - Hash Table
- All will be implemented as generic.
# Data Structures
 
- TLDR: This will be updated as I implement each with more detailed documentation.
## Single Linked List API

- `sll_init(compare_func)` - allocated and create a empty list takes comaparator as function pointer
- `sll_free(list)` - deallocates list
- `sll_append(x, list)` - appends x to end of list
- `sll_prepend(x, list)` - prepends x to start of list
- `sll_remove_head(list)` - removes head of list
- `sll_contains(x, list)` - checks if x is in list
- `sll_get_head(list)` - gets head of list
- `sll_size(list)` - size of list
- `sll_is_empty(list)` - whether list is empty
## Double Linked List API
 
- `dll_append(x, list)` - appends x to end of list
- `dll_prepend(x, list)` - prepends x to start of list
- `dll_remove_head(list)` - removes head of list
- `dll_remove_tail(list)` - removes tail of list
- `dll_contains(x, list)` - checks if x is in list
- `dll_get_head(list)` - gets head of list
- `dll_get_tail(list)` - gets tail of list
- `dll_size(list)` - size of list
- `dll_is_empty(list)` - whether list is empty
## Ring Buffer API

- `ringbuff_init(capacity, element_size)` - allocates and creates an empty buffer
- `ringbuff_free(buff)` - deallocates buffer
- `ringbuff_push(x, buff)` - inserts x at tail of buffer, returns -1 if full
- `ringbuff_pop(out, buff)` - copies head of buffer into out and removes it
- `ringbuff_peek(buff)` - gets head of buffer without removing it
- `ringbuff_is_empty(buff)` - whether buffer is empty
- `ringbuff_is_full(buff)` - whether buffer is full
- `ringbuff_size(buff)` - size of buffer
## Dynamic Array API
 
- `da_init(element_size)` - allocates and creates an empty array of elements that are `element_size` bytes each, returns NULL on failure
- `da_free(list)` - deallocates array
- `da_push(x, list)` - appends x to end of array, grows capacity if full, returns -1 on failure
- `da_at(out, i, list)` - copies element at index i into out, returns -1 if i is out of bounds
- `da_set(i, x, list)` - replaces element at index i with x, returns -1 if i is out of bounds
- `da_remove(out, list)` - removes last element and copies it into out, returns -1 if empty
- `da_is_empty(list)` - whether array is empty
- `da_size(list)` - size of array
- `da_capacity(list)` - capacity of array
## Queue API
 
- `offer(x)` - inserts an element
- `poll()` - gets and removes the head element
- `peek()` - looks at the head
- `size()` - size of queue
- `is_empty()` - whether queue is empty
## Hash Table API
 
- `put(key, value)` - inserts key and value
- `get(key)` - gets value for a key
- `remove(key)` - removes key and its value
- `has(key)` - checks if key exists
- `has_value(value)` - checks if value exists
- `size()` - size of table
- `capacity()` - capacity of table
- `is_empty()` - whether table is empty
# Quick start
 
- TODO
