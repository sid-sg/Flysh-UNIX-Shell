#include<errno.h>
#include "../include/source.h"

char getNextChar(struct scannerSource *src){
   if( !src || !src->buffer){
        errno = ENODATA;
        return ERRCHAR;
   } 

   ++src->currentPosition;

   if(src->currentPosition >= src->bufferSize){
        src->currentPosition = src->bufferSize;
        return EOF;
   }

   return src->buffer[src->currentPosition];

}

void ungetNextChar(struct scannerSource *src){
    if(src->currentPosition < 0){
        return;
    }
    --src->currentPosition; 
}

char peekNextChar(struct scannerSource *src){
    if( !src || !src->buffer){
            errno = ENODATA;
            return ERRCHAR;
    } 
    
    size_t nextPosition = src->currentPosition + 1;
 
    if(nextPosition >= src->bufferSize){
            nextPosition = src->bufferSize;
            return EOF;
    }

    return src->buffer[nextPosition]; 
}

void skipWhitespace(struct scannerSource *src){
    if( !src || !src->buffer){
        return;    
    }

    char nextChar;

    while( ( (nextChar = peekNextChar(src) ) != EOF) && ( nextChar == ' ' || nextChar == '\t')  ){
        getNextChar(src);
    }
}