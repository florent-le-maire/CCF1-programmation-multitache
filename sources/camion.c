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
    c->end = 1;
    return NULL;
}
char *displayCamion(Camion *c){
    char test[500];

    printf("Camion : id[%d] state[%s] poid[%f]\n",
           c->id, c->state, c->poid);
    return "";
}

