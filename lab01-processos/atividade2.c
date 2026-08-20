#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_FILHOS 4

int main() {
    pid_t pid;

    printf("Processo Pai principal com PID %d.\n\n", getpid());

    for (int i = 0; i < N_FILHOS; i++) {
        pid = fork();

        if (pid < 0) { 
            fprintf(stderr, "Erro ao chamar fork()!\n");
            return 1;
        } else if (pid == 0) {
            printf("  -> [Filho %d] Meu PID e %d, meu pai e %d.\n", i + 1, getpid(), getppid());
            exit(0); 
        }
    }

    printf("--------------------------------------------\n");
    printf("Pai (PID %d) esperando todos os filhos terminarem...\n", getpid());
    for (int i = 0; i < N_FILHOS; i++) {
        wait(NULL);
    }

    printf("Todos os filhos terminaram. O processo pai vai encerrar.\n");

    return 0;
}
