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
typedef struct Camion{
    int id;
    char state[10];
    double poid;
    int destination;
    int chargement;
    int meteo;
    sem_t sem;
    int end;
} Camion;
typedef struct Random{
    double *realWeight;//Create tab of weight
    int *loadTime;//Create tab of time
}Random;
void *pesage(void *camion);
void *chargement(void *camion);

#endif //TP_THREAD_LOGISTIC_H
