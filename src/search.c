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
    }
    
    char** index = malloc(sizeof(char*)*(size+1)*2);
    index[0] = malloc(sizeof(char)*IDSIZE);
    char* csize = malloc(sizeof(char)*5);
    sprintf(csize, "%d", size*2);
    index[0] = csize;

    size=1;
    for(int i = 1; i<=get_table_size(tab) && size<(get_table_size(index)); i++){
        title = get_title(tab[i]);
        if (strstr(title, name) != NULL){
            index[size] = malloc(sizeof(char)*IDSIZE);
            strcpy(index[size], tab[i]);
            size++;
            index[size] = malloc(sizeof(char)*NAMESIZE);
            strcpy(index[size], title);
            size++;
            
        }
        /* printf("%s\n", tab[i]);
        strcat(index, tab[i]);
        strcat(index, " ");
        title = get_title(tab[i]);
        strcat(index, title);
        strcat(index, "\n"); */
    }
    free_table(tab);
    return index;
}
char* search_author(char* author){
    //TODO
    return "";
}
char* search_date(int date){
    //TODO
    return "";
}
void search(){
    //TODO
}