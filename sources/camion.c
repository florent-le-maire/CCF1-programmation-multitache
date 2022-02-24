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
    int d = -1;
    do {
        d = readDestination(c);
        strcpy(c->state,"GetDest");
    } while (d == -1);

    strcpy(c->state,"WaitMeteo");
    getMeteo(c);
    strcpy(c->state,"GOOOO");
    printf ("fin du thread %u\n",(unsigned int)pthread_self());
    c->end = 1;
    return NULL;
}
char *displayCamion(Truck *c){
    char test[500];

    printf("Camion %d : %s information : poid[%f] destination[%s] meteo[%d]\n",
           c->id, c->state, c->poid, c->destination,c->meteo);
    return "";
}

