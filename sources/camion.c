//
// Created by lemai on 22/02/2022.
//
#include "camion.h"


void *launchCamion (void *camion)
{
    Camion *c = (Camion *)camion;
//    printf ("Argument recu %d, state %s tid: %u\n" ,c->id,c->state, (unsigned int)pthread_self());
    pesage(camion);
    strcpy(c->state,"WaitLoad");
    chargement(camion);
    strcpy(c->state,"WaitDest");

    printf ("fin thread %u\n",(unsigned int)pthread_self());
    return NULL;
}
