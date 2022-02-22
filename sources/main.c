#include <stdio.h>
#include "main.h"
#include "camion.h"


int main() {

    createThreads(2);
    sleep (3);
    printf ("fin thread main \n" );
    return EXIT_SUCCESS;
}

void createThreads(int nb){
    pthread_t tid;
    for (int i = 1; i < nb+1; i++) {
        Camion cInit = {.id=i,.state="WaitPesage"};
        Camion *c = malloc(sizeof (Camion));
        *c = cInit;

        if (pthread_create(&tid, NULL, launchCamion, (void*)c)!= 0)
        {
            perror(" erreur pthread_create \n");
            exit (1);
        }

    }
    pthread_join (tid, NULL);
}
