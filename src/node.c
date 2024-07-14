#include <stdlib.h>
#include <string.h>
#include "../include/node.h"

struct node *newNode(enum nodeType nodeType){
    struct node *node = malloc(sizeof(struct node));
    if(!node){
        return NULL;
    }

    memset(node, 0, sizeof(struct node));
    node->nodetype = nodeType;

    return node;
}

void addChildNode(struct node *parent, struct node *child){
    if(!parent || !child){
        return;
    }

    if(!parent->firstChild){
        parent->firstChild = child;                                                        
    }
    else{
        struct node* sibling = parent->firstChild;
        while(sibling->nextSibling){
            sibling = sibling->nextSibling;
        }

        sibling->nextSibling = child;
        child->prevSibling = sibling;                
    }
    parent->noOfChildren++;
}

void freeNodeTree(struct node *node){
    if(!node){
        return;
    }
    struct node* child = node->firstChild;
    while(child){
        struct node* next = child->nextSibling;
        freeNodeTree(child);
        child = next;
    }
    
    if(node->valType == VAL_STRING){
        if(node->valSymbol.str){
            free(node->valSymbol.str); //freeing only string since dynamically allocated
        }
    }

    free(node);
}


void setNodeVal(struct node *node, char *val){
    node->valType = VAL_STRING;
    if(!val){
        node->valSymbol.str = NULL;
    }
    else{
        char *nodeString = malloc(strlen(val) + 1);
        if(!nodeString){
            node->valSymbol.str = NULL;
        }
        else{
            strcpy(nodeString, val);
            node->valSymbol.str = nodeString;
        }
    }

}