#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t mx;
uthread_cond_t cond;
int count;

void randomStall() {
    int i, r = random() >> 16;
    while (i++<r);
}

void waitForAllOtherThreads() {
    uthread_mutex_lock(mx);
    if (count > 0) {
        uthread_cond_wait(cond);
    }
    uthread_mutex_unlock(mx);
}

void* p(void* v) {
    randomStall();
    printf("a\n");
    
    uthread_mutex_lock(mx);
    count--;
    if (count == 0) {
        uthread_cond_broadcast(cond);
    }
    uthread_mutex_unlock(mx);
    
    waitForAllOtherThreads();
    printf("b\n");
    return NULL;
}

int main(int arg, char** arv) {
    uthread_init(4);
    
    mx = uthread_mutex_create();
    cond = uthread_cond_create(mx);
    count = NUM_THREADS;
    
    for (int i=0; i<NUM_THREADS; i++)
        threads[i] = uthread_create(p, NULL);
    for (int i=0; i<NUM_THREADS; i++)
        uthread_join (threads[i], NULL);
    printf("------\n");
}
