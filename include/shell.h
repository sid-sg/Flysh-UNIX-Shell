#ifndef SHELL_H
#define SHELL_H

#include "./source.h"

void PS1();
void PS2();
void printASCII(void);
char* readInput(void);
int parseAndExecute(struct source *src);

#endif