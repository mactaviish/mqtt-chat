#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "MQTTAsync.h"

#define ADDRESS     "tcp://localhost:1883"
#define QOS         1
#define TIMEOUT     10000L

char CLIENTID;
int ERRORCODE;

void printError(char message, int error){
    printf('%c.\n', message)
    printf('Error code: %d.\n', error);
}

pthread_mutex_t thread_mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_mutex3 = PTHREAD_MUTEX_INITIALIZER;