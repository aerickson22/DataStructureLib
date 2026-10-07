
Readme · MD
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
 
- `append(x)` - appends x to end of list
- `prepend(x)` - prepends x to start of list
- `remove_head()` - removes head of list
- `contains(x)` - checks if x is in list
- `get_head()` - gets head of list
- `size()` - size of list
- `is_empty()` - whether list is empty
## Double Linked List API
 
- `append(x)` - appends x to end of list
- `prepend(x)` - prepends x to start of list
- `remove_head()` - removes x from head of list
- `remove_tail()` - removes x from tail of list
- `contains(x)` - checks if x is in list
- `get_head()` - gets head of list
- `get_tail()` - gets tail of list
- `size()` - size of list
- `is_empty()` - whether list is empty
## Ring Buffer API
 
- `put(x)` - inserts element at tail
- `get()` - gets element from head
- `is_empty()` - whether buffer is empty
- `is_full()` - whether buffer is full
- `size()` - size of buffer
## Dynamic Array API
 
- `push(x)` - appends element to end of array
- `at(i)` - gets element at index i
- `set(i, x)` - replaces element at index i with x
- `remove(i)` - removes element at index i
- `size()` - size of array
- `is_empty()` - whether array is empty
- `capacity()` - capacity of array
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
