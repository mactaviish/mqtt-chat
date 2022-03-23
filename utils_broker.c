#include "./utils_consts.h"
/* ini - connection */
void onConnect(void* context, MQTTAsync_successData* response){
    printf("Conectado com sucesso!\n");
}

void onConnectionFailure(void* context, MQTTAsync_failureData* response){
    printError("Falha ao conectar!", response-code);
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
/* end - connection */

/* ini - disconnection */
void onDisconnect(void* context, MQTTAsync_successData* response){
    printf("Desconectado com sucesso!\n");
}

void onDisconnectionFailure(void* context, MQTTAsync_failureData* response){
    printError("Falha ao desconectar!", response-code);
}
/* end - disconection */

int messageReceived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    printf("Você recebeu uma mensagem de %s!\n", topicName);
    printf("   Mensagem: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}