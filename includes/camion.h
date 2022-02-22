//
// Created by lemai on 22/02/2022.
//

#ifndef TP_THREAD_CAMION_H
#define TP_THREAD_CAMION_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "pesage.h"
typedef struct Camion{
    int id;
    char state[10];
} Camion;
void *launchCamion (void *camion);
#endif //TP_THREAD_CAMION_H
