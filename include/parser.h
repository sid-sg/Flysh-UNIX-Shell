#ifndef PARSER_H
#define PARSER_H

#include "./source.h"
#include "./scanner.h"

struct node *parseCommand(struct token *token);

#endif