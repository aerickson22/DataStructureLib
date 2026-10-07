#include "sll.h"
#include <assert.h>
#include <stdlib.h>

int compare_int(void* x, void* y){
    return *((int*)x) - *((int*)y);
}

int main(){
    single_linked_list_t* test_list;
    assert((test_list = sll_init(&compare_int)) != NULL);
    int x, y;
    x = 420;
    y = 67;

    assert(sll_append(&x,test_list) == 0);
    assert(sll_prepend(&y, test_list) == 0);
    assert(compare_int(sll_remove_head(test_list), &y) == 0);
    sll_append(&y, test_list);
    assert(sll_contains(&y, test_list) == true);
    assert(sll_size(test_list) == 2);
    sll_remove_head(test_list);
    sll_remove_head(test_list);
    assert(sll_is_empty(test_list) == true);
    sll_free(test_list);
}


