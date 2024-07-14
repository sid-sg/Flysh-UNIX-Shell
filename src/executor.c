#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/executor.h"

#define maxArgs 255

// char *searchPath(char *file){
//     char *PATH = getenv("PATH");
//     char *p1 = PATH;
//     char *p2;

//     while(p1 && p2){
//         p2 = p1;

//         while(*p2 && *p2 != ':'){
//             p2++;
//         }

//         int plen = p2 - p1;
//         if(!plen){
//             plen = 1;
//         }

//         int alen = strlen(file);
//         char path[plen+1+alen+1];

//         strncpy(path, p1, p2-p1);
//         path[p2-p1] = '\0';

//         if(p2[-1] != '/'){
//             strcat(path, "/");
//         }
//         strcat(path, file);

//         struct stat st;
//         if(stat(path, &st) ==0){
//             if(!S_ISREG(st.st_mode)){
//                 errno = ENOENT;
//                 p1 = p2;
//                 if(*p2 == ':'){
//                     p1++;
//                 }
//                 continue;
//             }

//             p1 = malloc(strlen(path)+1);
//             if(!p1){
//                 return NULL;
//             }

//             strcpy(p1, path);
//             return p1;
//         }
//         else{
//             p1 = p2;
//             if(*p2 == ':'){
//                 p1++;
//             }
//         }
//     }
//     errno = ENOENT;
//     return NULL;
// }

char *searchPath(char *file) {
    char *PATH = getenv("PATH");
    char *p1 = PATH;
    char *p2;

    while (p1) {
        p2 = strchr(p1, ':');
        if (p2) {
            *p2 = '\0';
        }

        int plen = strlen(p1);
        int alen = strlen(file);
        char path[plen + 1 + alen + 1];

        strcpy(path, p1);
        if (p1[plen - 1] != '/') {
            strcat(path, "/");
        }
        strcat(path, file);

        struct stat st;
        if (stat(path, &st) == 0) {
            if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
                if (p2) {
                    *p2 = ':';
                }
                char *result = malloc(strlen(path) + 1);
                strcpy(result, path);
                return result;
            }
        }

        if (p2) {
            *p2 = ':';
            p1 = p2 + 1;
        } else {
            p1 = NULL;
        }
    }

    errno = ENOENT;
    return NULL;
}


int doExecvCommand(int argc, char **argv){
    if(strrchr(argv[0], '/')){
        execv(argv[0], argv);
    }
    else{
        char *path = searchPath(argv[0]);
        if(!path){
            return 0;
        }
        execv(path, argv);
        free(path);
    }
    return 0;
}


static inline void freeArgv(int argc, char **argv){
    if(!argc){
        return;
    }
    while(argc--){
        free(argv[argc]);
    }
}

int doCommand(struct node *node){
    if(!node){
        return 0;
    }

    struct node *child = node->firstChild;
    if(!child){
        return 0;
    }

    int argc = 0;
    char *argv[maxArgs+1];
    char *str;

    while(child){
        str = child->valSymbol.str;
        argv[argc] = malloc(strlen(str)+1);

        if(!argv[argc]){
            freeArgv(argc, argv);
            return 0;
        }
        strcpy(argv[argc], str);
        argc++;
        if(argc >= maxArgs){
            break;
        }
        child = child->nextSibling;
    }
    argv[argc] = NULL;

    pid_t childPid = 0;
    if( (childPid = fork()) ==0 ){
        doExecvCommand(argc, argv);
        
        fprintf(stderr, "error: failed to execute command, %s\n", strerror(errno));
        if(errno == ENOEXEC){
            exit(126);
        }
        else if(errno == ENOENT){
            exit(127);
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    else if(childPid < 0){
        fprintf(stderr, "error: failed to fork command, %s\n", strerror(errno));
        return 0;
    }

    int status = 0;
    waitpid(childPid, &status, 0);
    freeArgv(argc, argv);

    return 1;
}
// int doCommand(struct node *node){
//     if(!node){
//         printf("No node to execute\n");
//         return 0;
//     }

//     struct node *child = node->firstChild;
//     if(!child){
//         printf("No child node to execute\n");
//         return 0;
//     }

//     int argc = 0;
//     char *argv[maxArgs+1];
//     char *str;

//     while(child){
//         str = child->valSymbol.str;
//         argv[argc] = malloc(strlen(str)+1);

//         if(!argv[argc]){
//             freeArgv(argc, argv);
//             return 0;
//         }
//         strcpy(argv[argc], str);
//         argc++;
//         if(argc >= maxArgs){
//             break;
//         }
//         child = child->nextSibling;
//     }
//     argv[argc] = NULL;

//     printf("Executing command: ");
//     for (int i = 0; i < argc; i++) {
//         printf("%s ", argv[i]);
//     }
//     printf("\n");

//     pid_t childPid = 0;
//     if((childPid = fork()) == 0){
//         doExecvCommand(argc, argv);
        
//         fprintf(stderr, "error: failed to execute command, %s\n", strerror(errno));
//         if(errno == ENOEXEC){
//             exit(126);
//         }
//         else if(errno == ENOENT){
//             exit(127);
//         }
//         else{
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if(childPid < 0){
//         fprintf(stderr, "error: failed to fork command, %s\n", strerror(errno));
//         return 0;
//     }

//     int status = 0;
//     waitpid(childPid, &status, 0);
//     freeArgv(argc, argv);

//     return 1;
// }
