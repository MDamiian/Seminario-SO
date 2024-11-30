#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Función que ejecutará cada hilo
void* threadFunction(void* arg) {
    int threadNum = *((int*)arg);
    printf("Thread %d: Iniciando\n", threadNum);
    sleep(1); // Simula trabajo del hilo
    printf("Thread %d: Terminando\n", threadNum);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int threadArgs[3];
    int result;

    // Crear e inicializar hilos
    for (int i = 0; i < 3; i++) {
        threadArgs[i] = i;
        printf("Main: Creando hilo %d\n", i);
        result = pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]);
        if (result != 0) {
            printf("Error creando hilo %d\n", i);
            return 1;
        }
    }

    // Administrar el ciclo de vida de los hilos
    for (int i = 0; i < 3; i++) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            printf("Error esperando hilo %d\n", i);
            return 1;
        }
        printf("Main: Hilo %d terminado\n", i);
    }

    printf("Main: Todos los hilos han terminado\n");
    return 0;
}