void stopBroker(){
    
}

void configConnection(MQTTAsync_connectOptions connectOptions){
    connectOptions.onSuccess = onConnect;
    connectOptions.onFailure = onConnectionFailure;
}

void configDisconnection(MQTTAsync_disconnectOptions disconnectOptions){
    disconnectOptions.onSuccess = onDisconnect;
    disconnectOptions.onFailure = onDisconnectionFailure;
}

void onConnect(void* context, MQTTAsync_successData* response){
    printf("Conectado com sucesso!\n");
}

void onConnectionFailure(void* context, MQTTAsync_failureData* response){
    printf("Falha ao conectar! Erro: %d\n", response-code);
}

void onDisconnect(void* context, MQTTAsync_successData* response){
    printf("Desconectado com sucesso!\n");
}

void onDisconnectionFailure(void* context, MQTTAsync_failureData* response){
    printf("Falha ao desconectar! Erro: %d\n", response-code);
}