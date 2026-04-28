#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char* args[] = {"ls", "-l", NULL};
    printf("Ejecutando exec...\n");
    execvp(args[0], args);
    perror("execvp falló");
    return EXIT_FAILURE;
}