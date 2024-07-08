#include <stdio.h>
#include "../include/shell.h"

//prompt statements

void PS1(void){
    printf("$ ");
    fflush(stdout);
}

void PS2(void){
    printf("> ");
    fflush(stdout);
}

