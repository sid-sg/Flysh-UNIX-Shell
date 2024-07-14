#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "node.h"

char *searchPath(char *file);
int doExecvCommand(int argc, char **argv);
int doCommand(struct node *node);

#endif