#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/shell.h"
#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/source.h"
#include "../include/executor.h"

#define BUFFER_SIZE 1024
#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"


int main(int argc, char **argv){

    char* inputCmd;
    
    printASCII();

    do{
       
        PS1();

        inputCmd = readInput();

        if(!inputCmd){
            exit(EXIT_SUCCESS);
        }

        if(inputCmd[0] == '\0' || strcmp(inputCmd, "\n") == 0){
            free(inputCmd);
            continue;
        }

        if(strcmp(inputCmd, "exit\n") == 0){
            free(inputCmd);
            break;
        }

        struct source src;
        src.buffer = inputCmd;
        src.bufferLength = strlen(inputCmd);
        src.currentPosition = 0;

        parseAndExecute(&src);

        free(inputCmd);

    } while(1);

    exit(EXIT_SUCCESS);
}


void printASCII(void){
    printf("%s", KGRN);
    printf("  _____.__               .__     \n");
    printf("_/ ____\\  | ___.__. _____|  |__  \n");
    printf("\\   __\\|  |<   |  |/  ___/  |  \\ \n");
    printf(" |  |  |  |_\\___  |\\___ \\|   Y  \\ \n");
    printf(" |__|  |____/ ____/____  >___|  / \n");
    printf("            \\/         \\/     \\/ \n"); 
    printf("%s", KNRM);  
    fflush(stdout);
}

char* readInput(void){
    char buffer[BUFFER_SIZE];
    char *cmd = NULL;
    size_t cmdLen = 0;

    while(fgets(buffer, BUFFER_SIZE, stdin)){
        size_t bufferLen = strlen(buffer);
        
        if(cmd == NULL){
            cmd = malloc(bufferLen+1);
        }
        else{
            char *newCmd = realloc(cmd, cmdLen+bufferLen+1);

            if(newCmd){
                cmd = newCmd;
            }
            else{
                free(cmd);
                cmd = NULL;
            }
        }

        if(cmd == NULL){
            fprintf(stderr,"Error: memory allocation failed, %s", strerror(errno));
        }

        strcpy(cmd+cmdLen, buffer);
        cmdLen += bufferLen;

        if(buffer[bufferLen-1] =='\n'){
            if(bufferLen == 1 || buffer[bufferLen-2] != '\\'){
                return cmd;
            }

            cmd[cmdLen-2] = '\0';
            cmdLen -= 2;

            PS2();
        }
    }

    return cmd;   
}

int parseAndExecute(struct source *src){
    skipWhitespace(src);

    struct token *token = tokenize(src);

    if(token == &EOFtoken){
        return 0;
    }

    while(token && token != &EOFtoken){
        struct node *command = parseCommand(token);

        if(!command){
            break;
        }

        doCommand(command);
        freeNodeTree(command);
        token = tokenize(src);
    }

    return 1;
}
