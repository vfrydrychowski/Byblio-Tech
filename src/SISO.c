#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/SISO.h"

void cleanbuff(){
    int c = 0;
    while (c != 0 && c != EOF){
        c = getchar();
    }
}
void read_int(int* nb){
    //set the maximu size to write an integer + '\n'
    char* temp = malloc(sizeof(char)*9);
    if (temp == NULL){
        perror("ERR MALLOC\n");
        exit(1);
    }

    fgets(temp, 9, stdin);
    if (temp == NULL){
        perror("ERR fgets()\n");
        exit(1);
    }
    cleanbuff();
    //replace enter char by end of string char
    char* enter = NULL;
    enter = strchr(temp, '\n');
    if (enter != NULL) *enter = '\0';

    *nb = atoi(temp);
    free(temp);
}

//assume string has already been allocate
void read_string(char* string){
    fgets(string, strlen(string), stdin);
    if (string == NULL){
        perror("ERR fgets()\n");
        exit(1);
    }
    cleanbuff();
    //replace enter char by end of string char
    char* enter = NULL;
    enter = strchr(string, '\n');
    if (enter != NULL) *enter = '\0';
}