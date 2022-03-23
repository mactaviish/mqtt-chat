#include "./utils_consts.h"

void menuInvoke(MQTTAsync mqttClient, MQTTAsync_disconnectOptions disconnectOptions){
    printMenu();
    doSelection(mqttClient, disconnectOptions);
}

void printMenu(){
    printf("Bem-vind@ novamente!\n\n");

    printf("[1] Enviar mensagem para um usuário...\n");
    printf("[2] Aceitar um novo chat...\n");
    printf("[3] Solicitar um novo chat...\n");
    printf("[4] Enviar mensagem para um grupo...\n");
    printf("[5] Entrar ou criar um grupo...\n");
	printf("[6] Desconectar do broker ...\n");
    printf("[0] Sair...\n");
}

void doSelection(MQTTAsync mqttClient, MQTTAsync_disconnectOptions disconnectOptions){
    int choice;

    while(true){
        scanf("%d", choice);

        switch(choice){
            case 1:
                sendDirectMessage(mqttClient);
                break;
            case 2:
                acceptDirectMessage(mqttClient);
                break;
            case 3:
                requestDirectMessage(mqttClient);
                break;
            case 4:
                sendGroupMessage(mqttClient);
                break;
            case 5:
                enterOrCreateGroup(mqttClient);
                break;
            case 6:
                stopBroker(mqttClient, disconnectOptions);
                break;
            case 0:
                printf("Valeu falou!\n");
                break;
        }
    }
}

void getClientID(){
    printf("Digite seu ID:\n");

    while(true){
        scanf("%d", CLIENTID);
        if (CLIENTID > 0) {
            break;
        }
    }
}

void stopBroker(MQTTAsync mqttClient, MQTTAsync_disconnectOptions disconnectOptions){
	if ((errorCode = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS){
        printError("Falha ao desconectar!", errorCode);
		errorCode = EXIT_FAILURE;
		destroyExit(mqttClient);
	}
}