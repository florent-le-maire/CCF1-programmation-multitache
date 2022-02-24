//
// Created by lemai on 22/02/2022.
//

#include "logistic.h"
pthread_mutex_t mutexPesage =PTHREAD_MUTEX_INITIALIZER;
extern Random random;

char *listDest[] = {
        "Lille",
        "Paris",
        "Mars",
        "Arles",
        "Nime",
        "Agde",
        "Lyon"
};

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

void *creatDestination(void *t){
    int nb = (int)t;
    int i = 0;
    while(1){
        int v = i%nb;
        writeDestination(random.destRandom[v]);
        sleep(random.timeGenerationDest[v]);
        i++;
    }
}
void writeDestination(int value){
    sem_wait (&random.semWrite);
    random.index ++;
    if(random.index <= 4){
        random.dest[random.index] = value;
    } else{
        random.index = 4;
    }
    printf("Value de index : %d\n",random.index);
    sem_post(&random.semRead);
}
int readDestination(Truck *c){
    sem_wait (&random.semRead);
    sleep(1);
    if(random.index >= 0){
        printf("Destination %d\n",random.index);
        strcpy(c->destination,listDest[random.dest[random.index]]);
        random.index --;
        sem_post(&random.semWrite);
        return 1;
    }
    printf("Pas de destination\n");
    sem_post(&random.semWrite);
    return -1;
}