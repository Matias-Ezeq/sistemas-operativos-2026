#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < 3; i++) {
        pid = fork();

        if (pid == 0) {
            // ¿Qué hace cada hijo?
            printf("Hijo %d - PID: %d\n",
                   i, getpid());
            sleep(i + 1);
            exit(0);
        }
    }

    // ¿Quién llega acá?
    int status;
    while (wait(&status) > 0);

    printf("Padre: todos terminaron\n");
    return 0;
}
