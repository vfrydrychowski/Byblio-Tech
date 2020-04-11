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
char* search_name(char* name){
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char* index = malloc(sizeof(char)*get_table_size(tab)*(IDSIZE*2+2));
    strcpy(index, "");
    char* title;
    for(int i = 1; i<=get_table_size(tab); i++){
        
        /* printf("%s\n", tab[i]);
        strcat(index, tab[i]);
        strcat(index, " ");
        title = get_title(tab[i]);
        strcat(index, title);
        strcat(index, "\n"); */
    }
    free(title);
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