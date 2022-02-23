//
// Created by lemai on 22/02/2022.
//
#include "pesage.h"
#include "camion.h"
pthread_mutex_t mutexPesage =PTHREAD_MUTEX_INITIALIZER;
void *pesage(void *camion){

    Camion *c = (Camion *)camion;
    pthread_mutex_lock(&mutexPesage);
    strcpy(c->state,"Pesage");
    c->poid = c->poidReel;
    sleep (1);
    pthread_mutex_unlock (&mutexPesage);
    return 0;
}

void *chargement(void *camion){
    Camion *c = (Camion *)camion;
    sem_wait (&c->sem);
    strcpy(c->state,"Loading");
    //printf ("Camion %d en cours de chargement \n", c->id);
    sleep (5);
    sem_post(&c->sem);
    return 0;
}