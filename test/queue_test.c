#include "queue.h"
#include <assert.h>
#include <stdlib.h>

static int cmp_int(void* x, void* y){
    return *(int*)x - *(int*)y;
}

int main(void){
    queue_t q = queue_init(cmp_int);
    assert(q != NULL);

    // A new queue is empty
    assert(queue_is_empty(q));
    assert(queue_size(q) == 0);
    assert(queue_peek(q) == NULL);
    assert(queue_poll(q) == NULL);

    // Offer elements
    int vals[100];
    for(int i = 0; i < 100; i++){
        vals[i] = i;
        int rc = queue_offer(&vals[i], q);
        assert(rc == 0);
        assert(queue_size(q) == (size_t)(i + 1));
    }
    assert(!queue_is_empty(q));

    // Peek returns the head and does not remove it
    int* head = queue_peek(q);
    assert(head != NULL && *head == 0);
    assert(queue_size(q) == 100);
    head = queue_peek(q);
    assert(*head == 0);

    // Poll returns elements in FIFO order
    for(int i = 0; i < 100; i++){
        int* out = queue_poll(q);
        assert(out != NULL);
        assert(*out == i);
        assert(queue_size(q) == (size_t)(99 - i));
    }
    assert(queue_is_empty(q));
    assert(queue_poll(q) == NULL);
    assert(queue_peek(q) == NULL);

    // Interleaved offer and poll
    int a = 1, b = 2, c = 3;
    int rc = queue_offer(&a, q);
    assert(rc == 0);
    rc = queue_offer(&b, q);
    assert(rc == 0);
    int* out = queue_poll(q);
    assert(out == &a);
    rc = queue_offer(&c, q);
    assert(rc == 0);
    assert(queue_size(q) == 2);
    assert(queue_poll(q) == &b);
    assert(queue_poll(q) == &c);
    assert(queue_is_empty(q));

    // Reusable after being emptied
    rc = queue_offer(&a, q);
    assert(rc == 0);
    assert(queue_size(q) == 1);
    assert(queue_peek(q) == &a);

    queue_free(q);
    return 0;
}
