 # include <stdio.h>
 # include <unistd.h>
 # include <sys/wait.h>

 int main () {
     pid_t pid = fork();

     // Fork failure
     if (pid < 0) { 
        fprintf (stderr , " Fork falhou !\n");
        return 1;
     // Son process 
     } else if (pid == 0) { 
        printf ("Vim ao mundoo! Meu cpf é %d, o do meu pai é %d.\n", getpid () , getppid ());
    // Father process      
     } else { 
        printf ("Eu sou o pai! Meu PID e %d, criei o filho %d.\n", getpid () , pid);
        wait (NULL); 
        printf ("Meu filho terminou, vamo nessa .\n");
     }
     return 0;
}
