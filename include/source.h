#include <stddef.h>

#ifndef SOURCE_H
#define SOURCE_H

#define EOF (-1)  //error: end of file
#define ERRCHAR (0)  //error: NULL scannerSource or empty buffer
#define INIT_SRC_POS (-2)  //initial position of source string

struct scannerSource{
    char* buffer;
    size_t bufferSize;
    size_t currentPosition;
};

char getNextChar(struct scannerSource *src);
void ungetNextChar(struct scannerSource *src);
char peekNextChar(struct scannerSource *src);
void skipWhitespace(struct scannerSource *src);

#endif