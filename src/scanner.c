#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/scanner.h"
#include "../include/source.h"
#include "../include/shell.h"

char *tokenBuffer = NULL;
size_t tokenBufferLength = 0;
size_t tokenBufferIndex = -1;


struct token EOFtoken = {
    .textLength = 0
};

void addToBuffer(char charToAdd){ 
    tokenBuffer[tokenBufferIndex] = charToAdd;
    tokenBufferIndex++;  

    if(tokenBufferIndex >= tokenBufferLength){
        char *temp = realloc(tokenBuffer, tokenBufferLength*2);

        if(!temp){
            errno = ENOMEM;
            return; 
        }

        tokenBuffer = temp;
        tokenBufferLength *= 2;
    }
}

struct token *createToken(char *bufferString){
    struct token *tokenCreated = malloc(sizeof(struct token));

    if(!tokenCreated){
        return NULL;
    }    

    memset(tokenCreated, 0, sizeof(struct token));
    tokenCreated->textLength = strlen(bufferString);

    char *createdTokenString = malloc(tokenCreated->textLength + 1);

    if(!createdTokenString){
        free(tokenCreated);
        return NULL;
    }

    strcpy(createdTokenString, bufferString);
    tokenCreated->text = createdTokenString;

    return tokenCreated;
}

void freeToken (struct token *tokenCreated){
    if(tokenCreated->text){
        free(tokenCreated->text);
    }
    free(tokenCreated);
}

struct token *tokenize(struct source *src){
    
    if(!src || !src->buffer || !src->bufferLength){
        errno = ENODATA;
        return &EOFtoken;
    }

    if(!tokenBuffer){
        tokenBufferLength = 1024;
        tokenBuffer = malloc(tokenBufferLength);

        if(!tokenBuffer){
            errno = ENOMEM;
            return &EOFtoken;
        } 
    }

    char nextChar = getNextChar(src);

    if(nextChar == ERRCHAR || nextChar == EOF){
        return &EOFtoken;
    }

    int endloop = 0;
    tokenBufferIndex = 0;
    tokenBuffer[0] ='\0';

    do{
        switch(nextChar){
            case ' ':
            case '\t':
                if(tokenBufferIndex > 0){
                    endloop = 1;
                }
                break;
            case '\n':                
                if(tokenBufferIndex > 0){
                    ungetChar(src);
                }
                else{
                    addToBuffer(nextChar);
                }
                endloop = 1;
                break;
            default:
                addToBuffer(nextChar);
                break;
        }

        if(endloop){
            break;
        }

    } while( (nextChar = getNextChar(src)) != EOF );

    if(endloop == 0){
        return &EOFtoken;
    } 

    if(tokenBufferIndex >= tokenBufferLength){
        tokenBufferIndex--;
    }

    tokenBuffer[tokenBufferIndex] = '\0';

    struct token *newToken = createToken(tokenBuffer);

    if(!newToken){
        fprintf(stderr, "error: memory allocation failed to buffer, %s\n", strerror(errno));
        return &EOFtoken;
    }

    newToken->src = src;
    
    return newToken;    
}


