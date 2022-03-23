#include "./utils_consts.h"

void configConnection(MQTTAsync_connectOptions connectOptions, MQTTAsync mqttClient){
	connectOptions.keepAliveInterval = 20;              // tempo maximo sem comunicacao entre o cliente e o servidor
	connectOptions.cleansession = 0;                    // manter a sessao anterior do usuario
    connectOptions.onSuccess = onConnect;
    connectOptions.onFailure = onConnectionFailure;
    connectOptions.context = mqttClient;

	if ((errorCode = MQTTAsync_connect(mqttClient, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao iniciar conexão.", errorCode);
		errorCode = EXIT_FAILURE;
		destroyExit(mqttClient);
	}
}

void onConnect(void* context, MQTTAsync_successData* response){
    printf("Conectado com sucesso!\n");
}

void onConnectionFailure(void* context, MQTTAsync_failureData* response){
    printError("Falha ao conectar!", response-code);
}

void configDisconnection(MQTTAsync_disconnectOptions disconnectOptions){
    disconnectOptions.onSuccess = onDisconnect;
    disconnectOptions.onFailure = onDisconnectionFailure;
}

void connectionLost(void *context, char *cause)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;

	printf("\nConexão perdida!\n");
	if (cause)
	    printf("     Causa: %s\n", cause);
	printf("Reconectando...\n");

	connectOptions.keepAliveInterval = 20;
	connectOptions.cleansession = 1;

	if ((errorCode = MQTTAsync_connect(client, &connectOptions)) != MQTTASYNC_SUCCESS)
	{
        printError("Falha ao iniciar conexão!", errorCode);
		finished = 1;
	}
}

void onDisconnect(void* context, MQTTAsync_successData* response){
    printf("Desconectado com sucesso!\n");
}

void onDisconnectionFailure(void* context, MQTTAsync_failureData* response){
    printError("Falha ao desconectar!", response-code);
}

int messageReceived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    printf("Você recebeu uma mensagem de %s!\n", topicName);
    printf("   Mensagem: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}