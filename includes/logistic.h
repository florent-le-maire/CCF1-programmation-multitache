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

typedef struct Random{
    double *realWeight;//Create tab of weight
    int *loadTime;//Create tab of time
    int *timeGenerationDest;
    int *dest;
}Random;

typedef enum Meteo{
    PLUIE,
    NEIGE,
    BROUILLARD,
    RAS,
    VENT
}Meteo;
void *pesage(void *truck);
void *loading(void *truck);

#endif //TP_THREAD_LOGISTIC_H
