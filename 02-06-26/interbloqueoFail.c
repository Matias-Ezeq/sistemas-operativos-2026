
#include <stdio.h>
// Incluir biblioteca de hilos para gestión de hilos
#include <pthread.h>
// Incluir biblioteca de semáforos para sincronización
#include <semaphore.h>
// Incluir biblioteca unistd para funciones POSIX como sleep
#include <unistd.h>

#define N 2  // Cantidad de hilos // Definir constante N como 5, número de hilos

sem_t semaforo_recurso1, semaforo_recurso2; // Declarar semáforo para pedir recurso
int recursoCompartido1 = 0, recursoCompartido2 = 0;


void* hilo1(void* arg) {
    int id = *(int*)arg; // Obtener el ID del hilo desde el argumento
    printf("Valor del recurso %d\n", recursoCompartido1); // Imprimir que el hilo libera el recurso
    printf("hilo %d pidiendo recurso 1\n", id); // Imprimir que el hilo pidió el recurso
    sem_wait(&semaforo_recurso1); // Esperar (bloquear) semáforo semaforo_recurso para pedir acceso al recurso

    printf("hilo %d USANDO recurso 1\n", id); // Imprimir que el hilo está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido1 += 10;

    sem_post(&semaforo_recurso1); // Señalar (desbloquear) semáforo semaforo_recurso para liberar el pedido
    printf("hilo %d LIBERÓ recurso 1\n", id); // Imprimir que el hilo libera el recurso
    printf("Valor del recurso 1 %d\n", recursoCompartido1); // Imprimir que el hilo libera el recurso

    printf("Valor del recurso 1 %d\n", recursoCompartido2); // Imprimir que el hilo libera el recurso
    printf("hilo %d pidiendo recurso 2\n", id); // Imprimir que el hilo pidió el recurso
    sem_wait(&semaforo_recurso2); // Esperar (bloquear) semáforo semaforo_recurso para pedir acceso al recurso

    printf("hilo %d USANDO recurso 2\n", id); // Imprimir que el hilo está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido2 += 10;

    sem_post(&semaforo_recurso1); // Señalar (desbloquear) semáforo semaforo_recurso para liberar el pedido
    printf("hilo %d LIBERÓ recurso 2\n", id); // Imprimir que el hilo libera el recurso
    printf("Valor del recurso 2 %d\n", recursoCompartido2); 
    return NULL; // Retornar NULL al finalizar el hilo
}

void* hilo2(void* arg) {
    int id = *(int*)arg; // Obtener el ID del hilo desde el argumento
    printf("Valor del recurso 2 %d\n", recursoCompartido2); // Imprimir que el hilo libera el recurso
    printf("hilo %d pidiendo recurso 2\n", id); // Imprimir que el hilo pidió el recurso
    sem_wait(&semaforo_recurso2); // Esperar (bloquear) semáforo semaforo_recurso para pedir acceso al recurso

    printf("hilo %d USANDO recurso 2\n", id); // Imprimir que el hilo está usando el recurso
    sleep(1); // Dormir por 1 segundo simulando uso del recurso
    recursoCompartido2 += 10;

    sem_post(&semaforo_recurso1); // Señalar (desbloquear) semáforo semaforo_recurso para liberar el pedido
    printf("hilo %d LIBERÓ recurso 1\n", id); // Imprimir que el hilo libera el recurso
    printf("Valor del recurso 2 %d\n", recursoCompartido2); // Imprimir que el hilo libera el recurso
    return NULL; // Retornar NULL al finalizar el hilo
}

int main() {
    pthread_t hilos[N]; // Declarar arreglo de hilos para N hilos
    int id = 0, id2 = 1;
    
    sem_init(&semaforo_recurso1, 0, 1); // Inicializar semáforo semaforo_recurso con valor 3 (máximo 3 hilos pueden pedir)
    sem_init(&semaforo_recurso2, 0, 1); // Inicializar semáforo semaforo_recurso con valor 3 (máximo 3 hilos pueden pedir)


    pthread_create(&hilos[id], NULL, hilo1, &id); // Crear hilo ejecutando la función hilo con ID
    //id++;
    pthread_create(&hilos[id2], NULL, hilo2, &id2); // Crear hilo ejecutando la función hilo con ID
    //id++;

    for (int i = 0; i < N; i++) { // Bucle para esperar a que todos los hilos terminen
        pthread_join(hilos[i], NULL); // Esperar a que el hilo i termine
    }

    sem_destroy(&semaforo_recurso1); // Destruir semáforo semaforo_recurso
    sem_destroy(&semaforo_recurso2);

    printf("Sincronizacion OK - maximo 3 hilos accedieron al recurso\n"); // Imprimir mensaje de sincronización exitosa
    return 0; // Terminar programa con código 0
}
