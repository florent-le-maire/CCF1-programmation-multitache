
#include "main.h"

Truck **tabCamion;
int nb;
int currentNb;
Random random;
int main() {
    srand(time(NULL));   // Initialization, should only be called once.
    nb = 6; //Nb Camion
    initRandom(); //Init random struct
    currentNb = 0; //Nombre de camion actuellement sur le circuit
    pthread_t tid[2];
    Truck *c[nb];//Creation du tableau de camion
    tabCamion = c;//Formatage de la zone memoire en tableau

    createThreads(nb,tid);//Creation du thread

    printf("Free memory\n");
    ////////////////////////////ON LIBERE TOUTES LES ALLOCATIONS DE MEMOIRE
    for (int i = 0; i < nb; ++i) {
        free(tabCamion[i]);
    }
    free(random.loadTime);
    free(random.realWeight);
    free(random.timeGenerationDest);
    free(random.destRandom);

    printf ("fin thread main \n" );
    return EXIT_SUCCESS;
}
//CREATION DE TAB WITH RANDOM NUMBER
void initRandom(){
    sem_t semWrite;
    sem_t semRead;
    sem_init (&semWrite,0,1);
    sem_init (&semRead,0,1);
    double *tabWeight = malloc(sizeof (double )*nb);
    int *loadTime = malloc(sizeof (int )*nb);
    int *destRandom = malloc(sizeof (int )*nb);
    int *timeGenerationDest = malloc(sizeof (int )*nb);
    int *dest = malloc(sizeof (int )*5);

    for (int i = 0; i < nb; ++i) {
        tabWeight[i] = (double)((rand()%11)+4)*0.5;
        loadTime[i] = ((rand()%5)+5);
        destRandom[i] = rand()%6;
        timeGenerationDest[i]= (rand()%9)+1;
    }
    for (int i = 0; i < 10; ++i) {
        int vv = rand()%METEO_SIZE;
        random.meteoRand[i] = vv;
        //printf("vv is %d\n",vv);

    }

    random.loadTime = loadTime;
    random.realWeight = tabWeight;
    random.destRandom = destRandom;
    random.timeGenerationDest = timeGenerationDest;
    random.dest = dest;
    random.index = -1;
    random.semRead = semRead;
    random.semWrite = semWrite;

}
//CREATION DES THREADS
void createThreads(int nbTruck, pthread_t *tid){

    //INITIALISATION SEM CAMION
    sem_t sem;
    sem_init (&sem,0,4);

    //CREATION DU THREAD METEO
    if (pthread_create(&tid[0], NULL, createMeteo, (void*)&nbTruck) != 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }
    //CREATION DU THREAD DESTINATION
    if (pthread_create(&tid[0], NULL, creatDestination, (void*)&nbTruck) != 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }

    //CREATION DU THREAD AFFICHAGE
    if (pthread_create(&tid[0], NULL, display, (void*)1)!= 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }

    //CREATION DES THREADS CAMION
    for (int i = 1; i < nbTruck + 1; i++) {
        Truck cInit = {.id=i,.state="WaitPesage",.sem= sem,.end = 0};
        Truck *c = malloc(sizeof (Truck));
        *c = cInit;
        tabCamion[i-1] = c;
        if (pthread_create(&tid[1], NULL, launchCamion, (void*)c)!= 0)
        {
            perror(" erreur pthread_create \n");
            exit (1);
        }
        currentNb++;
        sleep((rand()%7)+1);

    }

    pthread_join (tid[0], NULL);//On attend le premier thread

}
//Thread d'affichage
void *display(void *arg){
    while (displayInfo() == 0){
        sleep(1);
    }
    printf ("fin thread %u\n",(unsigned int)pthread_self());
    return NULL;
}
int displayInfo(){
    int cpt = 0;
    printf("===============================================\n");
    for (int i = 0; i < currentNb; ++i) {
        //Permet de savoir quand tout les camions on fini la procédure
        if(tabCamion[i]->end == 1){
            cpt ++;
        }
        displayCamion(tabCamion[i]);
    }
    printf("===============================================\n");
    if(cpt == nb){
        return 1;
    }

    return 0;
}