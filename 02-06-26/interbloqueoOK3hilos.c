
#include <stdio.h>
// Incluir biblioteca de hilos para gestión de hilos
#include <pthread.h>
// Incluir biblioteca de semáforos para sincronización
#include <semaphore.h>
// Incluir biblioteca unistd para funciones POSIX como sleep
#include <unistd.h>

#define N 2  // Cantidad de procesos // Definir constante N como 5, número de procesos

sem_t semaf_recurso1, semaf_recurso2; // Declarar semáforo para pedir recurso
int recursoCompartido1 = 0, recursoCompartido2 = 0;


void* funcion1(void* arg) {
    long id = (long)arg; // Obtener el ID del proceso desde el argumento


    printf("hilo %ld - Valor del recurso 1 %d\n", id, recursoCompartido1); // Imprimir que el proceso libera el recurso
    printf("hilo %ld pidiendo recurso 1\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&semaf_recurso1); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido1 += 10;
    printf("hilo %ld USANDO recurso 1\n", id); // Imprimir que el proceso está usando el recurso

    sem_post(&semaf_recurso1); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("hilo %ld - Valor del recurso 1 %d\n", id, recursoCompartido1); // Imprimir que el proceso libera el recurso
    printf("hilo %ld LIBERÓ recurso 1\n", id); // Imprimir que el proceso libera el recurso





    printf("hilo %ld - Valor del recurso 2 %d\n", id, recursoCompartido2); // Imprimir que el proceso libera el recurso
    printf("hilo %ld pidiendo recurso 2\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&semaf_recurso2); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    printf("hilo %ld USANDO recurso 2\n", id); // Imprimir que el proceso está usando el recurso
    recursoCompartido2 += 10;

    sem_post(&semaf_recurso2); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("hilo %ld LIBERÓ recurso 2\n", id); // Imprimir que el proceso libera el recurso
    printf("hilo %ld - Valor del recurso 2 %d\n", id, recursoCompartido2); // Imprimir que el proceso 
    

    return NULL; // Retornar NULL al finalizar el hilo
}

void* funcion2(void* arg) {
    long id = (long)arg; // Obtener el ID del proceso desde el argumento
 
    printf("hilo %ld - Valor del recurso 2 %d\n", id, recursoCompartido2); // Imprimir que el proceso libera el recurso
    printf("hilo %ld pidiendo recurso 2\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&semaf_recurso2); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    printf("hilo %ld USANDO recurso 2\n", id); // Imprimir que el proceso está usando el recurso
    recursoCompartido2 += 10;

    sem_post(&semaf_recurso2); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("hilo %ld LIBERÓ recurso 2\n", id); // Imprimir que el proceso libera el recurso
    printf("hilo %ld - Valor del recurso 2 %d\n", id, recursoCompartido2); // Imprimir que el proceso libera el recurso



    printf("hilo %ld - Valor del recurso 1 %d\n", id, recursoCompartido1); // Imprimir que el proceso libera el recurso
    printf("hilo %ld pidiendo recurso 1\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&semaf_recurso1); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido1 += 10;
    printf("hilo %ld USANDO recurso 1\n", id); // Imprimir que el proceso está usando el recurso

    sem_post(&semaf_recurso1); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("hilo %ld - Valor del recurso 1 %d\n", id, recursoCompartido1); // Imprimir que el proceso libera el recurso
    printf("hilo %ld LIBERÓ recurso 1\n", id); // Imprimir que el proceso libera el recurso

    return NULL; // Retornar NULL al finalizar el hilo
}

int main() {
    pthread_t procesos[N]; // Declarar arreglo de hilos para N procesos
    int id = 0;
    
    sem_init(&semaf_recurso1, 0, 1); // Inicializar semáforo pedir_recurso con valor 3 (máximo 3 procesos pueden pedir)
    sem_init(&semaf_recurso2, 0, 1); // Inicializar semáforo pedir_recurso con valor 3 (máximo 3 procesos pueden pedir)

    pthread_create(&procesos[id], NULL, funcion1, (void *)1); // Crear hilo ejecutando la función proceso con ID
    id++;
    pthread_create(&procesos[id], NULL, funcion2, (void *)2); // Crear hilo ejecutando la función proceso con ID
    //id++;

    for (int i = 0; i < N; i++) { // Bucle para esperar a que todos los hilos terminen
        pthread_join(procesos[i], NULL); // Esperar a que el hilo i termine
    }

    sem_destroy(&semaf_recurso1); // Destruir semáforo pedir_recurso
    sem_destroy(&semaf_recurso2); // Destruir semáforo pedir_recurso

    printf("Sincronizacion OK - maximo 3 procesos accedieron al recurso\n"); // Imprimir mensaje de sincronización exitosa
    return 0; // Terminar programa con código 0
}
