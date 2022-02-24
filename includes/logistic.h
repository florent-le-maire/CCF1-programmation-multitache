//
// Created by lemai on 22/02/2022.
//

#ifndef TP_THREAD_LOGISTIC_H
#define TP_THREAD_LOGISTIC_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
typedef struct Truck{
    int id;
    char state[10];
    double poid;
    char destination[5];
    int meteo;
    sem_t sem;
    int end;
} Truck;
typedef enum Meteo{
    PLUIE,
    NEIGE,
    BROUILLARD,
    RAS,
    VENT,
    METEO_SIZE
}Meteo;

typedef struct Random{
    double *realWeight;//Create tab of weight
    int *loadTime;//Create tab of time
    //Pour la partie destination
    int *timeGenerationDest;
    int *destRandom;
    int *dest;
    int index;
    sem_t semWrite;
    sem_t semRead;
    //Pour la meteo
    Meteo meteo;
    Meteo meteoRand[10];
    sem_t semRead2;
    sem_t semRedac;
}Random;



void *pesage(void *truck);
void *loading(void *truck);
void *creatDestination(void *t);
void writeDestination(int value);
int readDestination(Truck *c);
void *createMeteo(void *t);
void getMeteo(Truck *c);
#endif //TP_THREAD_LOGISTIC_H
