//
// Created by lemai on 22/02/2022.
//

#ifndef TP_THREAD_PESAGE_H
#define TP_THREAD_PESAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

void *pesage(void *camion);
void *chargement(void *camion);

#endif //TP_THREAD_PESAGE_H
