#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include utils_menu.c
#include utils_direct.c;
#include utils_group.c;
#include utils_broker.c;

#define PORTA     "tcp://localhost:1883"

int escolha;


int main(int argc, char *argv[]){
    MQTTAsync mqttClient;
    MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;
    
    configConnection(connectOptions);
    configDisconnection(disconnectOptions);
    
    printMenu();
    doSelection();
}

//mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
