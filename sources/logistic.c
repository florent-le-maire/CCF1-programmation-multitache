//
// Created by lemai on 22/02/2022.
//

#include "logistic.h"
pthread_mutex_t mutexPesage =PTHREAD_MUTEX_INITIALIZER;
extern Random random;
void *pesage(void *truck){

    Truck *c = (Truck *)truck;
    pthread_mutex_lock(&mutexPesage);
    strcpy(c->state,"Pesage");
    c->poid = random.realWeight[c->id-1];
    sleep (3);
    pthread_mutex_unlock (&mutexPesage);
    return 0;
}

void *loading(void *truck){
    int val_sem;
    Truck *c = (Truck *)truck;
    sem_wait (&c->sem);
    sem_getvalue (&c->sem, &val_sem);
    printf("Place libre : Q%d\n",val_sem);
    strcpy(c->state,"Loading");
    sleep (random.loadTime[c->id-1]);
    sem_post(&c->sem);
    return 0;
}