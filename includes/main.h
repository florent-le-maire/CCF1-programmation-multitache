//
// Created by lemai on 22/02/2022.
//

#ifndef TP_THREAD_MAIN_H
#define TP_THREAD_MAIN_H
#include "camion.h"
void createThreads(int nbTruck, pthread_t *tid);
int displayInfo();
void *display(void *arg);
void initRandom();
double getStep();
#endif //TP_THREAD_MAIN_H
