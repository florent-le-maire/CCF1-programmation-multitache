#include <stdio.h>
#include "main.h"
#include "camion.h"

Camion **tabCamion;

int main() {
    int nb = 6;
    pthread_t tid;

    Camion *c[nb];
    tabCamion = c;
    createThreads(nb,tid);
    while(pthread_join (tid, NULL)){

    }

    for (int i = 0; i < nb; ++i) {
        free(tabCamion[i]);
    }

    printf ("fin thread main \n" );
    return EXIT_SUCCESS;
}

void createThreads(int nb,pthread_t tid){

    sem_t sem;
    sem_init (&sem,0,4);
    for (int i = 1; i < nb+1; i++) {
        Camion cInit = {.id=i,.state="WaitPesage",.sem= sem};
        Camion *c = malloc(sizeof (Camion));
        *c = cInit;
        tabCamion[i-1] = c;
        if (pthread_create(&tid, NULL, launchCamion, (void*)c)!= 0)
        {
            perror(" erreur pthread_create \n");
            exit (1);
        }

    }

}
