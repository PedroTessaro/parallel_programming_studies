#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 8
// If the INCREMENTS_PER_THREAD value was too low, the result probably will by the expected without
// race condition, because the threads would end their loop before the next started working on the same
// variable
#define INCREMENTS_PER_THREAD 1000000

long long counter = 0;

void* thread_func(void* arg) {
    long thread_id = (long)arg;
    printf("Thread %ld started working...\n", thread_id);
    
    for (int i = 0; i < INCREMENTS_PER_THREAD; ++i) {
        // there are 3 things happening behing the curtains here:
        // this instruction happens in 3 steps:
        // 1- Reading from the register that has the counter
        // 2- Executing the sum
        // 3- Write the value down in the counter variable
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads 
    for (long i = 0; i < NUM_THREADS; ++i) {
      if (pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for the threads to stop
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    long long expected = (long long)NUM_THREADS * INCREMENTS_PER_THREAD;
    printf("\n--- Results ---\n");
    printf("Final value:    %lld\n", counter);
    printf("expected value: %lld\n", expected);
    
    if (counter != expected) {
        printf("Difference: %lld. Race condition detected!\n", expected - counter);
    } else {
        printf("Resultado correto!\n");
    }
    
    return 0;
}
