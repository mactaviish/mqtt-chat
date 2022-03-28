#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "MQTTAsync.h"

#define ADDRESS     "tcp://localhost:1883"
#define QOS         1
#define TIMEOUT     10000L

char CLIENTID, TOPIC_CONTROL, TOPIC_CLIENT;
int ERRORCODE;

pthread_mutex_t topThread = PTHREAD_MUTEX_INITIALIZER;  //       topics thread
pthread_mutex_t pubThread = PTHREAD_MUTEX_INITIALIZER;  //  publishment thread
pthread_mutex_t subThread = PTHREAD_MUTEX_INITIALIZER;  // subscription thread

void nameTopics() {
    strncat(TOPIC_CONTROL, CLIENTID, 2);
    strcat(TOPIC_CONTROL, "_Control");
    strncat(TOPIC_CLIENT, CLIENTID, 2);
    strcat(TOPIC_CLIENT, "_Cliente");
}

void printError(char message, int error) {
    printf(message)
    printf("\nError code: %d.\n", error);
}