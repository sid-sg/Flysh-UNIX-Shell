
#include "../include/parser.h"
#include "../include/node.h"

struct node *parseCommand(struct token *token){
    if(!token){
        return NULL;
    }

    struct node *commandNode = newNode(NODE_COMMAND);
    if(!commandNode){
        freeToken(token);
        return NULL;
    }

    struct source *src = token->src;

    do{
        if(token->text[0] == '\n'){
            freeToken(token);
            break;
        }

        struct node *word = newNode(NODE_VAR);
        if(!word){
            freeTree(commandNode);
            freeToken(token);
            return NULL;
        }

        setNodeVal(word, token->text);
        addChildNode(commandNode, word);

        freeToken(token);
    } while( (token = tokenize(src)) != &EOFtoken );

    return commandNode;
}