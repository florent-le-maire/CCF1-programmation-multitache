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
    int nb = *(int *)t;
    int i = 0;
    while(1){
        int v = i%nb;
        writeDestination(random.destRandom[v]);
        sleep(random.timeGenerationDest[v]);
        i++;
    }
}
void *createMeteo(void *t){
    //ECRITURE ICI
    int i = 0;
    while(1){
        sem_wait(&random.semRedac);    // demande accès au buffer
        random.meteo = random.meteoRand[i%10];
        printf("Nouvelle meteo %d\n", random.meteo);
        sem_post(&random.semRead2);    // fin section critique
        sleep(20);
        i++;
    }

}
void getMeteo(Truck *c){
    sem_wait(&random.semRead2);
    c->meteo = random.meteo;
    printf("Lecture meteo %d\n", random.meteo);
    //LECTURE ICI
    sleep(1);
    sem_post(&random.semRedac);
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
    strcpy(c->state,"GetDest");
    sleep(1);
    while (random.index < 0){
        sleep(1);
    }
    printf("Destination %d\n",random.index);
    strcpy(c->destination,listDest[random.dest[random.index]]);
    random.index --;
    sem_post(&random.semWrite);
    return 1;


}