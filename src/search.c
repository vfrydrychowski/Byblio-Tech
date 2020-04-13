#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/search.h"
#include "../include/Json.h"
#include "../include/SISO.h"


void upd_index(){
    //TODO
}
char** search_title(char* name){
    char** tab = get_gen_table("data/object/obj.json", "obj");
    //first loop to find the size of index
    int size=0;
    char* title;
    for(int i = 1; i<=get_table_size(tab); i++){
        title = get_title(tab[i]);
        if (strstr(title, name) != NULL){
            size++;
        }
        free(title);
    }
    
    char** index = (char**)malloc(sizeof(char*)*(size+1)*2);
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    char* csize = (char*)malloc(sizeof(char)*5);
    sprintf(csize, "%d", size*2);
    strcpy(index[0], csize);
    //for each titles that match name, we put the title and the id in the table
    size=1;
    for(int i = 1; i<=get_table_size(tab) && size<(get_table_size(index)); i++){
        title = get_title(tab[i]);
        if (strstr(title, name) != NULL){
            index[size] = (char*)malloc(sizeof(char)*IDSIZE);
            strcpy(index[size], tab[i]);
            size++;
            index[size] = (char*)malloc(sizeof(char)*NAMESIZE);
            strcpy(index[size], title);
            size++;
        }
        free(title);
        /* printf("%s\n", tab[i]);
        strcat(index, tab[i]);
        strcat(index, " ");
        title = get_title(tab[i]);
        strcat(index, title);
        strcat(index, "\n"); */
    }
    free_table(tab);
    free(csize);
    return index;
}

char** search_author(char* author){
    char** tab = get_gen_table("data/object/obj.json", "obj");
    //first loop to find the size of index
    int size=0;
    char* auth;
    for(int i = 1; i<=get_table_size(tab); i++){
        auth = get_author(tab[i]);
        if (strstr(auth, author) != NULL){
            size++;
        }
        free(auth);
    }
    
    char** index = (char**)malloc(sizeof(char*)*(size+1)*2);
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    char* csize = (char*)malloc(sizeof(char)*5);
    sprintf(csize, "%d", size*2);
    strcpy(index[0], csize);
    //for each author that match name, we put the author and the id in the table
    size=1;
    for(int i = 1; i<=get_table_size(tab) && size<(get_table_size(index)); i++){
        auth = get_author(tab[i]);
        if (strstr(auth, author) != NULL){
            index[size] = (char*)malloc(sizeof(char)*IDSIZE);
            strcpy(index[size], tab[i]);
            size++;
            index[size] = (char*)malloc(sizeof(char)*NAMESIZE);
            strcpy(index[size], auth);
            size++; 
        }
        free(auth);
    }
    free_table(tab);
    free(csize);
    return index;
}

char** search_date(char* date){
    char** tab = get_gen_table("data/object/obj.json", "obj");
    //first loop to find the size of index
    int size=0;
    char* d;
    for(int i = 1; i<=get_table_size(tab); i++){
        d = get_date(tab[i]);
        if (strstr(d, date) != NULL){
            size++;
        }
        free(d);
    }
    
    char** index = (char**)malloc(sizeof(char*)*(size+1)*2);
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    char* csize = (char*)malloc(sizeof(char)*5);
    sprintf(csize, "%d", size*2);
    strcpy(index[0], csize);
    //for each author that match name, we put the author and the id in the table
    size=1;
    for(int i = 1; i<=get_table_size(tab) && size<(get_table_size(index)); i++){
        d = get_date(tab[i]);
        if (strstr(d, date) != NULL){
            index[size] = (char*)malloc(sizeof(char)*IDSIZE);
            strcpy(index[size], tab[i]);
            size++;
            index[size] = (char*)malloc(sizeof(char)*NAMESIZE);
            strcpy(index[size], d);
            size++; 
        }
        free(d);
    }
    free_table(tab);
    free(csize);
    return index;
}

void search(){
    //TODO
}