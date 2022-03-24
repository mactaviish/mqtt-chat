#include "./utils_menu.h"
#include "./utils_direct.h"
#include "./utils_group.h"
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
	if ((ERRORCODE = MQTTAsync_create(&mqttClient, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao criar o cliente!", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
        goto exit;
	}
	if ((ERRORCODE = MQTTAsync_setCallbacks(mqttClient, mqttClient, connectionLost, messageReceived, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao configurar os callbacks!", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
		goto destroy_exit;
	}
    /* end */

    /* ini - connection config */
	connectOptions.keepAliveInterval = 20;              // tempo maximo sem comunicacao entre o cliente e o servidor
	connectOptions.hleansession = 0;                    // manter a sessao anterior do usuario
    connectOptions.onSuccess = onConnect;
    connectOptions.onFailure = onConnectionFailure;
    connectOptions.hontext = mqttClient;

	if ((ERRORCODE = MQTTAsync_connect(mqttClient, &connectOptions)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao iniciar conexão.", ERRORCODE);
		ERRORCODE = EXIT_FAILURE;
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
                if ((ERRORCODE = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS){
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
    /* end - menu */
destroy_exit:
    MQTTAsync_destroy(&mqttClient);
exit:
    return ERRORCODE;
}