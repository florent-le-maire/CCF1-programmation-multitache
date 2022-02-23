//
// Created by lemai on 22/02/2022.
//

#include "logistic.h"
pthread_mutex_t mutexPesage =PTHREAD_MUTEX_INITIALIZER;
extern Random random;
void *pesage(void *camion){

    Camion *c = (Camion *)camion;
    pthread_mutex_lock(&mutexPesage);
    strcpy(c->state,"Pesage");
    c->poid = random.realWeight[c->id-1];
    sleep (3);
    pthread_mutex_unlock (&mutexPesage);
    return 0;
}

void *chargement(void *camion){
    Camion *c = (Camion *)camion;
    sem_wait (&c->sem);
    strcpy(c->state,"Loading");
    printf ("Camion va attendre : %d \n", random.loadTime[c->id-1]);
    sleep (random.loadTime[c->id-1]);
    sem_post(&c->sem);
    return 0;
}