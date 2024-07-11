#include <stddef.h>
#ifndef SCANNER_H
#define SCANNER_H

struct token{
    struct source *src;
    size_t textLength;
    char *text;
};

extern struct token EOFtoken; 

struct token *tokenize(struct source *src);
void freeToken (struct source *src);

#endif