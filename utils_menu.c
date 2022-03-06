void printMenu(){
    printf("Bem-vind@!\n\n");

    printf("[1] Enviar mensagem para um usuário...\n");
    printf("[2] Aceitar um novo chat...\n");
    printf("[3] Solicitar um novo chat...\n");
    printf("[4] Enviar mensagem para um grupo...\n");
    printf("[5] Entrar ou criar um grupo...\n");
	printf("[6] Desconectar do broker ...\n");
    printf("[0] Sair...\n");
}

void doSelection(){
    while(true){
        scanf("%d", escolha);

        switch(escolha){
            case 1:
                sendDirectMessage();
                break;
            case 2:
                acceptDirectMessage();
                break;
            case 3:
                requestDirectMessage();
                break;
            case 4:
                sendGroupMessage();
                break;
            case 5:
                enterOrCreateGroup();
                break;
            case 6:
                stopBroker();
                break;
            case 0:
                printf("Valeu falou!\n");
                break;
        }
    }
}