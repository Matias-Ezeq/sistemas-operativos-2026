
#include <stdio.h>
// Incluir biblioteca de hilos para gestión de hilos
#include <pthread.h>
// Incluir biblioteca de semáforos para sincronización
#include <semaphore.h>
// Incluir biblioteca unistd para funciones POSIX como sleep
#include <unistd.h>

#define N 2  // Cantidad de procesos // Definir constante N como 5, número de procesos

sem_t pedir_recurso1, pedir_recurso2; // Declarar semáforo para pedir recurso
int recursoCompartido1 = 0, recursoCompartido2 = 0;


void* proceso1(void* arg) {
    int id = *(int*)arg; // Obtener el ID del proceso desde el argumento
    printf("Valor del recurso %d\n", recursoCompartido1); // Imprimir que el proceso libera el recurso
    printf("Proceso %d pidiendo recurso\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&pedir_recurso1); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    printf("Proceso %d USANDO recurso\n", id); // Imprimir que el proceso está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido1 += 10;

    sem_post(&pedir_recurso1); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("Proceso %d LIBERÓ recurso 1\n", id); // Imprimir que el proceso libera el recurso
    printf("Valor del recurso 1 %d\n", recursoCompartido1); // Imprimir que el proceso libera el recurso

    printf("Valor del recurso 1 %d\n", recursoCompartido2); // Imprimir que el proceso libera el recurso
    printf("Proceso %d pidiendo recurso 1\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&pedir_recurso2); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    printf("Proceso %d USANDO recurso 2\n", id); // Imprimir que el proceso está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido2 += 10;

    sem_post(&pedir_recurso1); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("Proceso %d LIBERÓ recurso 2\n", id); // Imprimir que el proceso libera el recurso
    printf("Valor del recurso 2 %d\n", recursoCompartido2); 
    return NULL; // Retornar NULL al finalizar el hilo
}

void* proceso2(void* arg) {
    int id = *(int*)arg; // Obtener el ID del proceso desde el argumento
    printf("Valor del recurso 2 %d\n", recursoCompartido2); // Imprimir que el proceso libera el recurso
    printf("Proceso %d pidiendo recurso 2\n", id); // Imprimir que el proceso pidió el recurso
    sem_wait(&pedir_recurso2); // Esperar (bloquear) semáforo pedir_recurso para pedir acceso al recurso

    printf("Proceso %d USANDO recurso 2\n", id); // Imprimir que el proceso está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido2 += 10;

    sem_post(&pedir_recurso1); // Señalar (desbloquear) semáforo pedir_recurso para liberar el pedido
    printf("Proceso %d LIBERÓ recurso\n", id); // Imprimir que el proceso libera el recurso
    printf("Valor del recurso %d\n", recursoCompartido2); // Imprimir que el proceso libera el recurso
    return NULL; // Retornar NULL al finalizar el hilo
}

int main() {
    pthread_t procesos[N]; // Declarar arreglo de hilos para N procesos
    int id = 0;
    
    sem_init(&pedir_recurso1, 0, 1); // Inicializar semáforo pedir_recurso con valor 3 (máximo 3 procesos pueden pedir)

    pthread_create(&procesos[id], NULL, proceso1, &id); // Crear hilo ejecutando la función proceso con ID
    id++;
    pthread_create(&procesos[id], NULL, proceso2, &id); // Crear hilo ejecutando la función proceso con ID
    //id++;

    for (int i = 0; i < N; i++) { // Bucle para esperar a que todos los hilos terminen
        pthread_join(procesos[i], NULL); // Esperar a que el hilo i termine
    }

    sem_destroy(&pedir_recurso1); // Destruir semáforo pedir_recurso

    printf("Sincronizacion OK - maximo 3 procesos accedieron al recurso\n"); // Imprimir mensaje de sincronización exitosa
    return 0; // Terminar programa con código 0
}
