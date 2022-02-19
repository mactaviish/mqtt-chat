#include ...

void menu(){
    printf("[1] Mensagens diretas...\n");
    printf("[2] Grupos...\n");
	printf("[3] Desconectar do broker ...\n");
    printf("[0] Sair...\n");
}

void direct(){
    printf("[1] Enviar mensagem para um usuário...\n");
    printf("[2] Aceitar um novo chat...\n");
    printf("[3] Solicitar um novo chat...\n");
    printf("[0] Voltar...\n");
 }

 void group(){
    printf("[1] Enviar mensagem para um grupo...\n");
    printf("[2] Entrar ou criar um grupo...\n");
    printf("[0] Voltar...\n");
}