//
// Created by lemai on 22/02/2022.
//
#include "camion.h"

void *launchCamion (void *truck)
{
    Truck *c = (Truck *)truck;
//    printf ("Argument recu %d, state %s tid: %u\n" ,c->id,c->state, (unsigned int)pthread_self());
    pesage(truck);
    strcpy(c->state,"WaitLoad");
    loading(truck);
    strcpy(c->state,"WaitDest");

    printf ("fin thread %u\n",(unsigned int)pthread_self());
    c->end = 1;
    return NULL;
}
char *displayCamion(Truck *c){
    char test[500];

    printf("Camion %d : %s information : poid[%f]\n",
           c->id, c->state, c->poid);
    return "";
}

