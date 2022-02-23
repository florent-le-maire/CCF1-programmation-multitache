
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

    printf ("fin thread main \n" );
    return EXIT_SUCCESS;
}
void initRandom(){
    double *tabWeight = malloc(sizeof (double )*nb);
    int *loadTime = malloc(sizeof (int )*nb);
    for (int i = 0; i < nb; ++i) {
        tabWeight[i] = (double)((rand()%55)+20)/10;
        loadTime[i] = ((rand()%5)+5);
    }
    random.loadTime = loadTime;
    random.realWeight = tabWeight;
}

void createThreads(int nb,pthread_t *tid){

    sem_t sem;
    sem_init (&sem,0,4);
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