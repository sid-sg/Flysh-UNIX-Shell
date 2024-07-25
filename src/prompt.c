#include <stdio.h>
#include "../include/shell.h"

#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"


//prompt statements

void PS1(void){
    printf("%s", KGRN);
    printf("$ ");
    printf("%s", KNRM);  
    fflush(stdout);
}

void PS2(void){
    printf("%s", KGRN);
    printf("> ");
    printf("%s", KNRM);  
    fflush(stdout);
}

