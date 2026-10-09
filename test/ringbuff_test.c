#include "ringbuff.h"
#include <assert.h>
#include <stdlib.h>

int compare(void* x, void* y){
    return *((int*)x) - *((int*)y);
}

int main(){
    ring_buffer_t buff;
    assert((buff = ringbuff_init(10, sizeof(int))) != NULL);
    for(int i = 0; i < 9; i++){
        int x = i;
        assert(ringbuff_push(&x, buff) == 0);
    }
    assert(ringbuff_is_full(buff) == false);
    int y = 55;
    ringbuff_push(&y, buff);
    assert(ringbuff_is_full(buff) == true);
    int z = 55;

    void* pop;
    if(!(pop = malloc(sizeof(int)))){
        return -1;
    } 
    ringbuff_pop(pop, buff);
    assert(compare(pop, &z));
    free(pop);
    ringbuff_free(buff);
}
