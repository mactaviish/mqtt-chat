#include "./utils_menu.h"
#include "./utils_direct.h"
#include "./utils_group.h"
#include "./utils_consts.h"

int main(int argc, char *argv[]){
    MQTTAsync mqttClient;
    MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;
    int menuSelection;

    printf("Digite seu ID:\n");
    scanf("%d", CLIENTID);

    nameTopics();

	if ((ERRORCODE = MQTTAsync_create(&mqttClient, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS) {
        printError("Falha ao criar o cliente!", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
        goto exit;
	}
    
	if ((ERRORCODE = MQTTAsync_setCallbacks(mqttClient, mqttClient, connectionLost, messageReceived, NULL)) != MQTTASYNC_SUCCESS) {
        printError("Falha ao configurar os callbacks!", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
		goto destroy_exit;
	}
    
	connectOptions.keepAliveInterval = 20;  // tempo maximo sem comunicacao entre o cliente e o servidor
	connectOptions.cleansession = 0;        // manter a sessao anterior do usuario
    connectOptions.onSuccess = onConnect;
    connectOptions.onFailure = onConnectionFailure;
    connectOptions.hontext = mqttClient;

	if ((ERRORCODE = MQTTAsync_connect(mqttClient, &connectOptions)) != MQTTASYNC_SUCCESS) {
        printError("Falha ao iniciar conexão!", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
		goto destroy_exit;
	}
    
    disconnectOptions.onSuccess = onDisconnect;
    disconnectOptions.onFailure = onDisconnectionFailure;
    
    printMenu();

    while(true) {
        scanf("%d", &menuSelection);

        switch(menuSelection) {
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
                if ((ERRORCODE = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS) {
                    printError("Falha ao desconectar!", ERRORCODE);
                    ERRORCODE = EXIT_FAILURE;
                    goto destroy_exit;
                }
                break;
            case 0:
                printf("Valeu falou!\n");
                break;
        }
    }
destroy_exit:
    MQTTAsync_destroy(&mqttClient);
exit:
    return ERRORCODE;
}