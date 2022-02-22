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
    printf ("Camion %d en cours de pesage \n", c->id);
    sleep (2);
    pthread_mutex_unlock (&mutexPesage);
    return 0;
}