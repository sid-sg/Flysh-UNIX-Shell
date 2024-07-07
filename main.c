#include <stdio.h>
#include <string.h>

int main(){

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