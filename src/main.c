#include <stdio.h>
#include <string.h>

int main(){
    
    
    printf("  _____.__               .__     \n");
    printf("_/ ____\\  | ___.__. _____|  |__  \n");
    printf("\\   __\\|  |<   |  |/  ___/  |  \\ \n");
    printf(" |  |  |  |_\\___  |\\___ \\|   Y  \\ \n");
    printf(" |__|  |____/ ____/____  >___|  / \n");
    printf("            \\/         \\/     \\/ \n");

    while(1){
        printf("$ ");
        fflush(stdout);

        char inputBuffer[100];
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        inputBuffer[ strlen(inputBuffer)-1 ] = '\0';

        printf("%s: command not found\n", inputBuffer);
    }
    return 0;
}