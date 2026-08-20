#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 

#define NUM_PROCESS 4
#define LENGTH 1000

int main() {
    int fd[2];
    if(pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    static int array[LENGTH];
    for (int i = 0; i < LENGTH; i++) {
        array[i] = i + 1;
    }

    for(int i = 0; i < NUM_PROCESS; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork not working");
        } else if(pid == 0) {
            printf("Processo filho [Número %d]", pid);
        }
    }
    return 0;
}
