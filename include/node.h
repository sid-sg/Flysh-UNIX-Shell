#ifndef NODE_H
#define NODE_H

enum nodeType{
    NODE_COMMAND, //root node type
    NODE_VAR //child nodes type
};


enum valType{
    VAL_SINT = 1,
    VAL_UINT,
    VAL_SLL,
    VAL_ULL,
    VAL_FLOAT,
    VAL_DOUBLE,
    VAL_LDOUBLE,
    VAL_CHAR,
    VAL_STRING
};

union valSymbol{
    long sint;
    unsigned long uint;
    long long sll;
    unsigned long long ull;
    double sfloat;
    long double ldouble;
    char chr;
    char *str;
};

struct node{
    enum nodeType nodetype;
    enum valType valType;
    union valSymbol valSymbol;
    int noOfChildren;
    struct node *firstChild;
    struct node *nextSibling, *prevSibling;
};

struct node *newNode(enum nodeType nodeType);
void addChildNode(struct node *parent, struct node *child);
void freeNodeTree(struct node *node);
void setNodeVal(struct node *node, char *val);

#endif