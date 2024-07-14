#include<errno.h>
#include <stdio.h>
#include "../include/source.h"

char getNextChar(struct source *src) {
    if(!src || !src->buffer || src->currentPosition >= src->bufferLength){
        return EOF;
    }

    char c = src->buffer[src->currentPosition++];
    if(c == '\0'){
        return EOF;
    }
    return c;
}

void ungetChar(struct source *src){
    if(src->currentPosition < 0){
        return;
    }
    --src->currentPosition; 
}

char peekNextChar(struct source *src){
    if( !src || !src->buffer){
            errno = ENODATA;
            return ERRCHAR;
    } 
    
    size_t nextPosition = src->currentPosition + 1;
 
    if(nextPosition >= src->bufferLength){
            nextPosition = src->bufferLength;
            return EOF;
    }

    return src->buffer[nextPosition]; 
}

void skipWhitespace(struct source *src){
    if( !src || !src->buffer){
        return;    
    }

    char nextChar;

    while( ( (nextChar = peekNextChar(src) ) != EOF) && ( nextChar == ' ' || nextChar == '\t')  ){
        getNextChar(src);
    }
}