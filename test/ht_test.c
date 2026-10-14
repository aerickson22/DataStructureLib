#include "ht.h"
#include <assert.h>
#include <stdlib.h>

static size_t hash_int(void* k){
    return (size_t)*(int*)k;
}

static int cmp_int(void* x, void* y){
    return *(int*)x - *(int*)y;
}

int main(void){
    hash_table_t ht = ht_init(hash_int, cmp_int);
    assert(ht != NULL);

    // A new table is empty
    assert(ht_is_empty(ht));
    assert(ht_size(ht) == 0);
    assert(ht_capacity(ht) > 0);

    // ht_put
    int keys[100];
    int vals[100];
    for(int i = 0; i < 100; i++){
        keys[i] = i;
        vals[i] = i * 10;
        int rc = ht_put(&keys[i], &vals[i], ht);
        assert(rc == 0);
        assert(ht_size(ht) == (size_t)(i + 1));
    }
    assert(!ht_is_empty(ht));
    assert(ht_capacity(ht) >= ht_size(ht));

    // ht_get and ht_has
    for(int i = 0; i < 100; i++){
        assert(ht_has(&keys[i], ht));
        assert(ht_get(&keys[i], ht) == &vals[i]);
    }

    // Lookup by an equal key at a different address
    int same = 45;
    assert(ht_has(&same, ht));
    assert(ht_get(&same, ht) == &vals[45]);

    // Missing key
    int missing = 999;
    assert(!ht_has(&missing, ht));
    assert(ht_get(&missing, ht) == NULL);

    // Overwrite an existing key
    int new_val = 55;
    assert(ht_put(&keys[45], &new_val, ht) == 0);
    assert(ht_size(ht) == 100);
    assert(ht_get(&keys[45], ht) == &new_val);

    // ht_remove
    assert(ht_remove(&keys[10], ht) == &vals[10]);
    assert(!ht_has(&keys[10], ht));
    assert(ht_size(ht) == 99);
    assert(ht_remove(&keys[10], ht) == NULL);

    ht_free(ht);
    return 0;
}
