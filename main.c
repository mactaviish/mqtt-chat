#include "./utils_menu.c"
#include "./utils_direct.c"
#include "./utils_group.c"
#include "./utils_consts.h"

int main(int argc, char *argv[]){
    int choice;
    MQTTAsync mqttClient;
    MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;

    /* ini */
    printf("Digite seu ID:\n"); // pegar id do usuario "login"
    while(true){
        scanf("%d", CLIENTID);
        if (CLIENTID > 0) {
            break;
        }
    }
    /* end */

    /* ini */
	if ((errorCode = MQTTAsync_create(&mqttClient, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao criar o cliente!", errorCode);
		errorCode = EXIT_FAILURE;
        goto exit;
	}
	if ((errorCode = MQTTAsync_setCallbacks(mqttClient, mqttClient, connectionLost, messageReceived, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao configurar os callbacks!", errorCode);
		errorCode = EXIT_FAILURE;
		goto destroy_exit;
	}
    /* end */

    /* ini - connection config */
	connectOptions.keepAliveInterval = 20;              // tempo maximo sem comunicacao entre o cliente e o servidor
	connectOptions.cleansession = 0;                    // manter a sessao anterior do usuario
    connectOptions.onSuccess = onConnect;
    connectOptions.onFailure = onConnectionFailure;
    connectOptions.context = mqttClient;

	if ((errorCode = MQTTAsync_connect(mqttClient, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao iniciar conexão.", errorCode);
		errorCode = EXIT_FAILURE;
		goto destroy_exit;
	}
    /* end - connection config */

    /* ini - disconnection config */
    disconnectOptions.onSuccess = onDisconnect;
    disconnectOptions.onFailure = onDisconnectionFailure;
    /* end - disconnection config */

    /* ini - menu */
    printMenu();
    
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
                if ((errorCode = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS){
                    printError("Falha ao desconectar!", errorCode);
                    errorCode = EXIT_FAILURE;
                    goto destroy_exit;
                }
                break;
            case 0:
                printf("Valeu falou!\n");
                break;
        }
    }
    /* end - menu */
    menuInvoke(mqttClient, disconnectOptions);

destroy_exit:
    MQTTAsync_destroy(&client);
exit:
    return errorCode;
}