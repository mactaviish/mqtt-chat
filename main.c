#include "./utils_menu.c"
#include "./utils_direct.c"
#include "./utils_group.c"
#include "./utils_consts.h"

int main(int argc, char *argv[]){
    MQTTAsync mqttClient;
    MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;

    getClientID();

	if ((errorCode = MQTTAsync_create(&mqttClient, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao criar o cliente!", errorCode);
		errorCode = EXIT_FAILURE;
		exit:
            return errorCode;
	}

	if ((errorCode = MQTTAsync_setCallbacks(mqttClient, mqttClient, connectionLost, messageReceived, NULL)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao configurar os callbacks!", errorCode);
		errorCode = EXIT_FAILURE;
		destroyExit(mqttClient);
	}

    configConnection(connectOptions);
    configDisconnection(disconnectOptions);
    menuInvoke(mqttClient, disconnectOptions);
}