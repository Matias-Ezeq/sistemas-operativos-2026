#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int num; pidmore t pid;
    for (num= 0; num< 3; num++) {
        pid= fork();
        //Hacer la Segunda prueba sacando estos comentarios
        // printf ("Soy el proceso de PID%d y mi padre tiene%d de PID.\n", getpid(), getppid());
        
        if (pid!= 0) break;
        //Hacer la primera prueba sacando estos comentarios
        //printf ("Soy el proceso de PID%d y mi padre tiene%d de PID.\n", getpid(), getppid());
        srandom(getpid());
        sleep (random()%3);
    }
    if (pid!= 0) printf ("Fin del proceso de PID%d.\n", wait (NULL)); return 0;

}