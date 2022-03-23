#include "./utils_consts.h"

void sendDirectMessage(MQTTAsync mqttClient){
    char idUser;

    printf("Digite a ID do usuário que você deseja conversar:\n");
    scanf("%d", idUser);

    printf("Iniciando conversa...\n");


    strncat(rec_topic, rec_id, 2);
    strcat(rec_topic, "_Control");

    printf("Requisitando inicio de sessão...\n");

    pthread_mutex_lock(&pub_msg_mutex);
    pub_msg(rec_topic, CLIENTID, mqttClient);
    pthread_mutex_unlock(&pub_msg_mutex);
}

void requestDirectMessage(MQTTAsync mqttClient){

}

void acceptDirectMessage(MQTTAsync mqttClient){

}