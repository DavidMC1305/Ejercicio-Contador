#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int counter;

void* increase_counter( void *args )
{
    while(1)
    {
        counter++;
        if (counter == 3) {
            printf("Alarma activada. El contador ha tardado mucho.\n");
            alarm(2); // Configurar una alarma para que expire en 2 segundos
        }
        sleep(1);
    }
    pthread_exit( NULL );
}

void handle_alarm(int sig) {
    printf("Te tardaste mucho, terminando el proceso.\n");
    kill(getpid(), SIGKILL); // Terminar el proceso
}

int main()
{
    pthread_t thread_1; // ID del hilo
    int state; // Valor de retorno de la creación del hilo
    counter = 0;    // La cuenta empieza en 0
   
    signal(SIGALRM, handle_alarm); // Configurar la señal de alarma
   
    state = pthread_create( &thread_1, NULL, &increase_counter, NULL ); // Crear al hilo, call_return debe dar 0 o hay error

    printf("Contando. Presiona cualquier tecla para ver la cuenta.\n");
    getchar();
    printf("El contador llegó a: %d.\n", counter);
   
    exit(0); // Terminar el proceso también mata a todos sus hilos secundarios
}
