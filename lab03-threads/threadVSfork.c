#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>

#define NUM_EXECUTIONS 1000

void* thread_function(void* arg) {
    return NULL;
}

void user_thread_simulation() {
    // Empty function to simulate some work
}

double get_time_in_ms() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000.0 + t.tv_usec / 1000.0;
}

int main() {
    double start, end;
    int i;

    printf("Executing %d creations for each type...\n\n", NUM_EXECUTIONS);

    // ---------------------
    // Time to create fork()
    // ---------------------
    start = get_time_in_ms();
    for (i = 0; i < NUM_EXECUTIONS; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            exit(0);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
    end = get_time_in_ms();
    printf("Total time with fork(): %.2f ms\n", end - start);

    // ---------------------
    // Time to create threads 
    // ---------------------
    pthread_t threads[NUM_EXECUTIONS];
    start = get_time_in_ms();
    for (i = 0; i < NUM_EXECUTIONS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }
    for (i = 0; i < NUM_EXECUTIONS; i++) {
        pthread_join(threads[i], NULL);
    }
    end = get_time_in_ms();
    printf("Total time with pthread_create(): %.2f ms\n", end - start);

    // ---------------------
    // Simulation with "user threads"
    // ---------------------
    start = get_time_in_ms();
    for (i = 0; i < NUM_EXECUTIONS; i++) {
        user_thread_simulation();
    }
    end = get_time_in_ms();
    printf("Total time with user thread simulation: %.2f ms\n", end - start);

    return 0;
}
