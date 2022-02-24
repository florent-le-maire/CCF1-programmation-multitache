
#include "main.h"

Truck **tabCamion;
int nb;
int currentNb;
Random random;
int main() {
    srand(time(NULL));   // Initialization, should only be called once.
    nb = 6;
    initRandom(); //Init random logistic number
    currentNb = 0;
    pthread_t tid[2];
    Truck *c[nb];
    tabCamion = c;

    createThreads(nb,tid);

    printf("Free memory\n");
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
void createThreads(int nb,pthread_t *tid){

    sem_t sem;

    sem_init (&sem,0,4);

    if (pthread_create(&tid[0], NULL, createMeteo, (void*)&nb)!= 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }
    if (pthread_create(&tid[0], NULL, creatDestination, (void*)&nb)!= 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }


    if (pthread_create(&tid[0], NULL, display, (void*)1)!= 0)
    {
        perror(" erreur pthread_create \n");
        exit (1);
    }
    for (int i = 1; i < nb+1; i++) {
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

void *display(void *arg){
    while (displayInfo() == 0){
        sleep(2);
    }
    printf ("fin thread %u\n",(unsigned int)pthread_self());
    return NULL;
}
int displayInfo(){
    int cpt = 0;
    printf("===============================================\n");
    for (int i = 0; i < currentNb; ++i) {
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