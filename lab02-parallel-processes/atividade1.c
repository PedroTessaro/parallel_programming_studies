#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 200000000
#define NUM_PROCESSES 10

void heavy_work(double* array, int start, int end) {
    for(int i = start; i < end; ++i) {
        array[i] = sin(array[i]) * cos(array[i]) + sqrt (array[i]);
    }     
}

int main() {
    double* array = (double*)malloc(ARRAY_SIZE * sizeof(double));
    if(array == NULL) {
        fprintf(stderr, "Error on allocation");
        return 1;
    }

    for(int i = 0; i < ARRAY_SIZE; ++i)
        array[i] = (double)i;

    int chunk_size = ARRAY_SIZE / NUM_PROCESSES;
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for(int i = 0; i < NUM_PROCESSES; ++i) {
        pid_t pid = fork();

        if(pid < 0) {
            fprintf(stderr, "Fork failure");
            return 1;
        } else if(pid == 0) {
            int start = i * chunk_size;
            int end = (i == NUM_PROCESSES - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
            heavy_work(array, start, end);
            exit(0);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double time_spent = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("%d processes which executed in %f seconds\n", NUM_PROCESSES, time_spent);

    free(array);
    return 0;
}
