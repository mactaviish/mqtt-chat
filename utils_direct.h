#include "./utils_consts.h"

void sendDirectMessage(MQTTAsync mqttClient){
    char idUser, idTopic;

    printf("Digite a ID do usuário que você deseja conversar:\n");
    scanf("%d", idUser);

    printf("Iniciando sessão...\n");
    strncat(idTopic, idUser, 2);
    strcat(idTopic, "_Control");

    pthread_mutex_trylock(&pubThread);
    pub_msg(idTopic, CLIENTID, mqttClient);
    pthread_mutex_unlock(&pubThread);
}

void requestDirectMessage(MQTTAsync mqttClient){

}

void acceptDirectMessage(MQTTAsync mqttClient){

}