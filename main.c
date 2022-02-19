#include utils_menu.c
#include utils_direct.c;
#include utils_group.c;
#include utils_broker.c;

int FEscolha;

int main(int argc, char *argv[]){
    while(true){
        menu();
        scanf("%d", FEscolha);

        switch(FEscolha){
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