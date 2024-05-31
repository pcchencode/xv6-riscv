//Lab3
#include "kernel/types.h"

struct lock_t {
    uint locked; 
}; 

typedef struct lock_t lock_t;

int thread_create(void *(start_routine)(void*), void *arg);
void lock_init(lock_t* lock);
void lock_acquire(lock_t* lock);
void lock_release(lock_t* lock);