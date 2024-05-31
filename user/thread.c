//Lab3
#include "thread.h"
#include "user.h"

// Routine to allocate a user stack of PGSIZE bytes and call clone() to create a child thread
int thread_create(void *(start_routine)(void*), void *arg) {
    // Allocate a user stack of PGSIZE bytes (4096 bytes)
    void *stack = (void*) malloc(4096);

    // Create the child thread
    int thread_id = clone(stack);
    if (thread_id == 0) { // If this is the child thread
        (*start_routine)(arg); // Execute the start routine with the given argument
        exit(0); // Terminate the child thread after completion
    }
    return 0; // Return to the parent thread
}

// Initialize the lock (reference to corresponding functions in spinlock.c)
void lock_init(struct lock_t* lock) {
    lock->locked = 0; // Set the lock to unlocked state
}

// Acquire the lock
void lock_acquire(struct lock_t* lock) {
    // Busy-wait until the lock is acquired
    while (__sync_lock_test_and_set(&lock->locked, 1) != 0);
    __sync_synchronize(); // Memory barrier to ensure all previous memory operations are complete
}

// Release the lock
void lock_release(struct lock_t* lock) {
    __sync_synchronize(); // Memory barrier to ensure all previous memory operations are complete
    __sync_lock_release(&lock->locked); // Release the lock
}

