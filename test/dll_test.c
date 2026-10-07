#include "dll.h"
#include <assert.h>

int compare_int(void* x, void* y){
    return *((int*)x) - *((int*)y);
}

int main(){
    double_linked_list_t list;
    assert((list = dll_init(&compare_int)) != NULL);
    int x = 67;
    int y = 55;
    assert(dll_append(&x, list) == 0);
    assert(dll_prepend(&y, list) == 0);
    assert(compare_int(dll_get_head(list), &y) == 0);
    assert(compare_int(dll_get_tail(list), &x) == 0);
    assert(dll_contains(&x, list) == true);
    assert(compare_int(dll_remove_head(list), &y) == 0);
    assert(compare_int(dll_remove_tail(list), &x) == 0);
    assert(dll_is_empty(list) == true && dll_size(list) == 0);
    dll_free(list);
}
