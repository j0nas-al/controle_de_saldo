#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMRET 1
#define NUMDEP 1

pthread_t ret[NUMRET];
pthread_t dep[NUMDEP];
int saldo = 10000;
pthread_mutex_t saldo_mutex;
int currentidx;

void *retirada(void *arg);
void *deposito(void *arg);

int main(int argc, char **argv) {
    int i;
    srand48(time(NULL));
    pthread_mutex_init(&saldo_mutex, NULL);
    currentidx = 0;
    
    
    for(i=0; i<NUMDEP; i++){
        pthread_create(&(dep[i]), NULL, deposito, NULL);
    }
    
    for(i=0; i<NUMRET; i++){
        pthread_create(&(ret[i]), NULL, retirada, NULL);
    }
    
    for(i=0; i<NUMDEP; i++){
        pthread_join(dep[i], NULL);
    }
    
    for(i=0; i<NUMRET; i++){
        pthread_join(ret[i], NULL);
    }
}

void *retirada(void *arg) {
    int n;
    int i;
    
    pthread_mutex_lock(&saldo_mutex);
    for(i=0; i < 5; i++){
        n = 100 + rand() % 415;
        saldo = saldo - n;
        printf("Retirando o valor: %d\n", n);
        sleep((int)(drand48() * 4.0));
    }
    printf("Saldo atual: %d\n", saldo);
    pthread_mutex_unlock(&saldo_mutex);
}

void *deposito(void *arg) {
    int n;
    int i;
    
    pthread_mutex_lock(&saldo_mutex);
    for(i=0; i < 5; i++){
        n = 100 + rand() % 415;
        saldo = saldo + n;
        printf("Depositando o valor: %d\n", n);
        sleep((int)(drand48() * 4.0));
    }
    printf("Saldo atual: %d\n", saldo);
    pthread_mutex_unlock(&saldo_mutex);
}


