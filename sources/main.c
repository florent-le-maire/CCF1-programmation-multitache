#include <stdio.h>
#include "main.h"
#include "camion.h"

Camion **tabCamion;
int nb;
int currentNb;

int main() {
    srand(time(NULL));   // Initialization, should only be called once.
    nb = 2;
    currentNb = 0;
    pthread_t tid;
    Camion *c[nb];
    tabCamion = c;
    createThreads(nb,tid);

    printf("Libere la memoire\n");
    for (int i = 0; i < nb; ++i) {
        free(tabCamion[i]);
    }

    printf ("fin thread main \n" );
    return EXIT_SUCCESS;
}

void createThreads(int nb,pthread_t tid){

    sem_t sem;
    sem_init (&sem,0,4);
    if (pthread_create(&tid, NULL, display, (void*)1)!= 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }
    for (int i = 1; i < nb+1; i++) {
        Camion cInit = {.id=i,.state="WaitPesage",.poidReel = (double)((rand()%55)+20)/10,.sem= sem,.end = 0};
        Camion *c = malloc(sizeof (Camion));
        *c = cInit;
        tabCamion[i-1] = c;
        if (pthread_create(&tid, NULL, launchCamion, (void*)c)!= 0)
        {
            perror(" erreur pthread_create \n");
            exit (1);
        }
        currentNb++;
        sleep((rand()%7)+1);

    }

    pthread_join (tid, NULL);

}

void *display(void *arg){
    while (displayInfo() == 0){
        sleep(1);
    }
    printf ("fin thread %u\n",(unsigned int)pthread_self());
    return NULL;
}
int displayInfo(){
    int t = 0;
    int cpt = 0;
    for (int i = 0; i < currentNb; ++i) {
        if(tabCamion[i]->end == 1){
            cpt ++;
        }
        displayCamion(tabCamion[i]);
    }
    if(cpt == nb){
        return 1;
    }

    return t;
}