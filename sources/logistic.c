//
// Created by lemai on 22/02/2022.
//

#include "logistic.h"
pthread_mutex_t mutexPesage =PTHREAD_MUTEX_INITIALIZER;
extern Random random;

//création de la liste des destination
char *listDest[] = {
        "Lille",
        "Paris",
        "Mars",
        "Arles",
        "Nime",
        "Agde",
        "Lyon"
};

//Fonction pesage avec mutex
void *pesage(void *truck){

    Truck *c = (Truck *)truck;
    pthread_mutex_lock(&mutexPesage);
    strcpy(c->state,"Pesage");
    c->poid = random.realWeight[c->id-1];
    sleep (3);
    pthread_mutex_unlock (&mutexPesage);
    return 0;
}
//Fonction chargement avec sem de 4
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
//Thread creation des destination
void *creatDestination(void *t){
    int nb = *(int *)t;
    int i = 0;
    //Pour des raison de simplicité nous avons fait une boucle infini
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
    //On affecte la meteo au camion
    c->meteo = random.meteo;
    printf("Lecture meteo %d\n", random.meteo);
    sleep(1);
    sem_post(&random.semRedac);
}
void writeDestination(int value){
    sem_wait (&random.semWrite);
    random.index ++;
    if(random.index <= 4){
        //On associe la case du tableau la valeur
        random.dest[random.index] = value;
    } else{
        //On empeche l'index de dépasser la valeur du tableau
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
    //On prend la valeur à l'index
    strcpy(c->destination,listDest[random.dest[random.index]]);
    //Puis on la supprime en décrementent l'index
    random.index --;
    sem_post(&random.semWrite);
    return 1;

}