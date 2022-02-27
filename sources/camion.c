//
// Created by lemai on 22/02/2022.
//
#include "camion.h"
//Fonction création du comportement des camions
void *launchCamion (void *truck)
{
    Truck *pTruck = (Truck *)truck;
    pesage(pTruck);
    strcpy(pTruck->state, "WaitLoad");
    loading(pTruck);
    strcpy(pTruck->state, "WaitDest");
    readDestination(pTruck);
    strcpy(pTruck->state, "WaitMeteo");
    getMeteo(pTruck);
    strcpy(pTruck->state, "GOOOO");
    printf ("fin du thread %u\n",(unsigned int)pthread_self());
    pTruck->end = 1;
    return NULL;
}
//Fonction pour afficher 1 camion
char *displayCamion(Truck *c){
    printf("Camion %d : %s | information : poid[%f] destination[%s] meteo[%d]\n",
           c->id, c->state, c->poid, c->destination,c->meteo);
    return "";
}

