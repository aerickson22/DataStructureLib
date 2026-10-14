#include "ht.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define DEFAULT_CAPACITY 10
#define LOAD_FACTOR 0.75

struct hash_table_entry_t{
    void* key;
    void* value;
    struct hash_table_entry_t* next;
};

struct hash_table_t{
    size_t size;
    size_t capacity;
    struct hash_table_entry_t** buckets;
    size_t(*hash_func)(void* k);
    int(*compare)(void* x, void* y);
};

int _ht_resize(struct hash_table_t* ht, size_t new_capacity){
    struct hash_table_entry_t** new_buckets = calloc(new_capacity, sizeof(*new_buckets));
    if(!new_buckets){
        return -1;
    }
    for(size_t i = 0; i < ht->capacity; i++){
        struct hash_table_entry_t* curr = ht->buckets[i];
        while(curr){
            struct hash_table_entry_t* next = curr->next;
            size_t index = ht->hash_func(curr->key) % new_capacity;
            curr->next = new_buckets[index];
            new_buckets[index] = curr;
            curr = next;
        }
    }
    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
    return 0;
}

struct hash_table_t* ht_init(size_t(*hash_func)(void* k), int(*compare_key)(void* x, void* y)){
    if(!hash_func || !compare_key){
        return NULL;
    }
    struct hash_table_t* out = malloc(sizeof(*out));
    if(!out){
        return NULL;
    }
    out->buckets = calloc(DEFAULT_CAPACITY, sizeof(*out->buckets));
    if(!out->buckets){
        free(out);
        return NULL;
    }
    out->size = 0;
    out->capacity = DEFAULT_CAPACITY;
    out->hash_func = hash_func;
    out->compare = compare_key;
    return out;
}

void ht_free(struct hash_table_t* ht){
    for(size_t i = 0; i < ht->capacity; i++){
        struct hash_table_entry_t* curr = ht->buckets[i];
        struct hash_table_entry_t* prev;
        while(curr){
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    free(ht->buckets);
    free(ht);
}

int ht_put(void* key, void* val, struct hash_table_t* ht){
    if(((double)ht->size / (double)ht->capacity) >= LOAD_FACTOR){
        if(_ht_resize(ht, ht->capacity * 2) < 0){
            return -1;
        }
    }
    size_t index = ht->hash_func(key) % ht->capacity;
    for(struct hash_table_entry_t* curr = ht->buckets[index]; curr; curr = curr->next){
        if(ht->compare(curr->key, key) == 0){
            curr->value = val;
            return 0;
        }
    }
    struct hash_table_entry_t* new_bucket = malloc(sizeof(*new_bucket));
    if(!new_bucket){
        return -1;
    }
    new_bucket->key = key;
    new_bucket->value = val;
    new_bucket->next = ht->buckets[index];
    ht->buckets[index] = new_bucket;
    ht->size++;
    return 0;
}

void* ht_get(void* key, struct hash_table_t* ht){
    size_t index = ht->hash_func(key) % ht->capacity;
    struct hash_table_entry_t* curr = ht->buckets[index];
    while(curr){
        if(ht->compare(curr->key, key) == 0){
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void* ht_remove(void* key, struct hash_table_t* ht){
    size_t index = ht->hash_func(key) % ht->capacity;
    struct hash_table_entry_t** link = &ht->buckets[index];
    while(*link){
        struct hash_table_entry_t* curr = *link;
        if(ht->compare(curr->key, key) == 0){
            void* out = curr->value;
            *link = curr->next;
            free(curr);
            ht->size--;
            return out;
        }
        link = &curr->next;
    }
    return NULL;
}

bool ht_has(void* key, struct hash_table_t* ht){
    size_t index = ht->hash_func(key) % ht->capacity;
    struct hash_table_entry_t* curr = ht->buckets[index];
    while(curr){
        if(ht->compare(curr->key, key) == 0){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

size_t ht_size(struct hash_table_t* ht){
    return ht->size;
}

size_t ht_capacity(struct hash_table_t* ht){
    return ht->capacity;
}

bool ht_is_empty(struct hash_table_t* ht){
    return ht->size == 0;
}
