#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "MQTTAsync.h"

#define ADDRESS     "tcp://mqtt.eclipse.org:1883"
#define QOS         1
#define TIMEOUT     10000L

char CLIENTID;
int errorCode;

void printError(char message, int error){
    printf('%c.\n', message)
    printf('Error code: %d.\n', error);
}

void destroyExit(MQTTAsync mqttClient){
    MQTTAsync_destroy(&client);
    exit:
        return errorCode;
}

pthread_mutex_t thread_mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_mutex3 = PTHREAD_MUTEX_INITIALIZER;