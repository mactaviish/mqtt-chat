#include "./utils_consts.h"

/* ini - connection */
void onConnect(void* context, MQTTAsync_successData* response) {
	MQTTAsync mqttClient = (MQTTAsync)context;
	MQTTAsync_responseOptions responseOptions = MQTTAsync_responseOptions_initializer;

    printf("Conectado com sucesso!\n");
	
	responseOptions.onSuccess = onSubscribe;
	responseOptions.onFailure = onSubscribeFailure;
	responseOptions.context = mqttClient;

	if ((ERRORCODE = MQTTAsync_subscribe(mqttClient, TOPIC_CONTROL, QOS, &responseOptions)) != MQTTASYNC_SUCCESS) {
		printError("Falha ao iniciar assinatura no tópico de controle.", ERRORCODE);
		finished = 1;
	}
	if ((ERRORCODE = MQTTAsync_subscribe(mqttClient, TOPIC_CLIENT, QOS, &responseOptions)) != MQTTASYNC_SUCCESS) {
		printError("Falha ao iniciar assinatura no tópico de controle.", ERRORCODE);
		finished = 1;
	}
}

void onSubscribe(void* context, MQTTAsync_successData* response) {
	printf("Assinado com sucesso!\n");
	subscribed = 1;
}
void onSubscribeFailure(void* context, MQTTAsync_failureData* response) {
	printError("Falha ao assinar.", ERRORCODE)
	finished = 1;
}

void onConnectionFailure(void* context, MQTTAsync_failureData* response) {
    printError("Falha ao conectar!", ERRORCODE);
	finished = 1;
}

void connectionLost(void *context, char *cause) {
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
	
	printf("\nConexão Perdida!\n");
	printf("     causa: %s\n", cause);
	printf("Reconectando...\n");

	connectOptions.keepAliveInterval = 20;              // tempo maximo sem comunicacao entre o cliente e o servidor
	connectOptions.cleansession = 1;                    // manter a sessao anterior do usuario

	if ((rc = MQTTAsync_connect(client, &connectOptions)) != MQTTASYNC_SUCCESS) {
		printError("Falha ao iniciar conexão!", ERRORCODE);
 		finished = 1;
	}
}
/* end - connection */

/* ini - disconnection */
void onDisconnect(void* context, MQTTAsync_successData* response) {
    printf("Desconectado com sucesso!\n");
	disc_finished = 1;
}

void onDisconnectionFailure(void* context, MQTTAsync_failureData* response) {
    printError("Falha ao desconectar!", response-code);
	disc_finished = 1;
}
/* end - disconection */

void messagePublish(char * topic, char * payload, MQTTAsync mqttClient) {
    MQTTAsync_message message = MQTTAsync_message_initializer;
    MQTTAsync_responseOptions responseOptions = MQTTAsync_responseOptions_initializer;

    responseOptions.onSuccess = onSend;
    responseOptions.onFailure = onSendFailure;
    responseOptions.context = mqttClient;

    message.payload = payload;
    message.payloadlen = (int)strlen(payload);
    message.qos = QOS;

    if ((ERRORCODE = MQTTAsync_sendMessage(mqttClient, topic, &message, &responseOptions)) != MQTTASYNC_SUCCESS) {
		printError("Erro ao enviar mensagem!", ERRORCODE);
        MQTTAsync_destroy(mqttClient);
        exit(0);
    }

}

int messageReceived(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
    printf("Você recebeu uma mensagem de %s!\n", topicName);
    printf("   Mensagem: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void onSend(void* context, MQTTAsync_successData* response) {
	MQTTAsync mqttClient = (MQTTAsync)context;
	MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;

	printf("Mensagem entregue com sucesso!\n", response->token);

	disconnectOptions.onSuccess = onDisconnect;
	disconnectOptions.onFailure = onDisconnectFailure;
	disconnectOptions.context = mqttClient;

	if ((ERRORCODE = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS) {
		printError("Falha ao iniciar desconexão", ERRORCODE);
		exit(EXIT_FAILURE);
	}
}

void onSendFailure(void* context, MQTTAsync_failureData* response) {
	MQTTAsync mqttClient = (MQTTAsync)context;
	MQTTAsync_disconnectOptions disconnectOptions = MQTTAsync_disconnectOptions_initializer;
	
	printError("Falha ao enviar mensagem", response->code);
	
	disconnectOptions.onSuccess = onDisconnect;
	disconnectOptions.onFailure = onDisconnectFailure;
	disconnectOptions.context = mqttClient;

	if ((ERRORCODE = MQTTAsync_disconnect(mqttClient, &disconnectOptions)) != MQTTASYNC_SUCCESS) {
		printError("Falha ao iniciar desconexão", ERRORCODE);
		exit(EXIT_FAILURE);
	}
}