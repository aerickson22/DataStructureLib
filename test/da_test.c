#include "da.h"
#include <assert.h>
#include <stdlib.h>

int main(void){
    dynamic_array_t list = da_init(sizeof(int));
    assert(list != NULL);

    for(int i = 0; i < 100; i++){
        int x = i;
        int rc = da_push(&x, list);
        assert(rc == 0);
    }

    int* at = malloc(sizeof(int));
    if(!at){
        da_free(list);
        return -1;
    }

    // da_at
    da_at(at, 45, list);
    assert(*at == 45);

    // da_set
    *at = 55;
    da_set(45, at, list);
    da_at(at, 45, list);
    assert(*at == 55);

    // da_remove (assuming it removes the last element into `at`)
    da_remove(at, list);
    assert(*at == 99);
    
    free(at);
    da_free(list);
    return 0;
}
