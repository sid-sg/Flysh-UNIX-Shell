#include <stddef.h>

#ifndef SOURCE_H
#define SOURCE_H

#define EOF (-1)  //error: end of file
#define ERRCHAR (0)  //error: NULL source or empty buffer
#define INIT_SRC_POS (-2)  //initial position of source string

struct source{
    char* buffer;
    size_t bufferLength;
    size_t currentPosition;
};

char getNextChar(struct source *src);
void ungetChar(struct source *src);
char peekNextChar(struct source *src);
void skipWhitespace(struct source *src);

#endif