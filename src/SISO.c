#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/SISO.h"

void cleanbuff(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}


int read_int(int* nb){
    //set the maximum size to write an integer + '\n'
    int bool = 1;
    char* temp = malloc(sizeof(char)*9);
    if (temp == NULL){
        perror("ERR MALLOC\n");
        exit(1);
    }

    //ASCII check
    read_string(temp,sizeof(char)*9);
    for(int i=0; i<strlen(temp); i++){
        if (((int)temp[i] < 48 || (int)temp[i] > 57) && (int)temp[i] != 45){
            bool = 0;
        }
    }
    if (bool== 0) return 1;    

    //int cast
    *nb = atoi(temp);
    free(temp);
    return 0;
}

//assume string has already been allocate
void read_string(char* string, int size_str){
    fgets(string, size_str, stdin);
    if (string == NULL){
        perror("ERR fgets()\n");
        cleanbuff();
        exit(1);
    }
    //replace enter char by end of string char
    char* enter = NULL;
    enter = strchr(string, '\n');
    if (enter == NULL){
        cleanbuff();
    }
    *enter = '\0';
}