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


/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    if (strcmp(*ia, *ib) == 0) return cstring_cmp(*ia+1,*ib+1);
    return strcmp(*ia, *ib);
}

char** search_title(char* name){
    //initialization of index
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search_title failed");
        exit(EXIT_FAILURE);
    }
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    if (index[0] == NULL){
        perror("malloc index[0] in search_title failed");
        exit(EXIT_FAILURE);
    }
    int size=0;
    char* csize = (char*)malloc(sizeof(char)*5);
    if (csize == NULL){
        perror("malloc csize in search_title failed");
        exit(EXIT_FAILURE);
    }
    sprintf(csize, "%d", size);
    strcpy(index[0], csize);

    //retrieving the book's titles that contains name
    char* title;
    for(int i = 1; i<=get_table_size(tab); i++){
        title = get_title(tab[i]);
        if (strstr(title, name) != NULL || cstring_cmp(name, "")==0){
            size++;
            //rezise index
            index = (char**)realloc(index, sizeof(char*)*(size+2));
            if (index == NULL){
                perror("realloc index in search_title failed");
                exit(EXIT_FAILURE);
            }
            sprintf(csize, "%d", size);
            strcpy(index[0], csize);
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE +1));
            if (index[size] == NULL){
                perror("malloc index[size] in search_title failed");
                exit(EXIT_FAILURE);
            }
            strcpy(index[size], title);
            //adding a separator token
            strcat(index[size], "¤");
            strcat(index[size], tab[i]);
        }
        free(title);
    }
    //sorting the index
    qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    
    

    //array initialazing
    size = get_table_size(tab)*2;
    char** sep_index = malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate name and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strToken = strtok(NULL, "¤");
        strcpy(sep_index[i+1], strToken);
    }

    free_table(tab);
    free_table(index);
    free(csize);
    return sep_index;
    
}



char** search_author(char* author){
        //initialization of index
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search_title failed");
        exit(EXIT_FAILURE);
    }
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    if (index[0] == NULL){
        perror("malloc index[0] in search_title failed");
        exit(EXIT_FAILURE);
    }
    int size=0;
    char* csize = (char*)malloc(sizeof(char)*5);
    if (csize == NULL){
        perror("malloc csize in search_title failed");
        exit(EXIT_FAILURE);
    }
    sprintf(csize, "%d", size);
    strcpy(index[0], csize);

    //retrieving the book's authors that contains name
    char* auth;
    for(int i = 1; i<=get_table_size(tab); i++){
        auth = get_author(tab[i]);
        if (strstr(auth, author) != NULL || cstring_cmp(author, "")==0){
            size++;
            //rezise index
            index = (char**)realloc(index, sizeof(char*)*(size+2));
            if (index == NULL){
                perror("realloc index in search_title failed");
                exit(EXIT_FAILURE);
            }
            sprintf(csize, "%d", size);
            strcpy(index[0], csize);
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE +1));
            if (index[size] == NULL){
                perror("malloc index[size] in search_title failed");
                exit(EXIT_FAILURE);
            }
            strcpy(index[size], auth);
            //adding a separator token
            strcat(index[size], "¤");
            strcat(index[size], tab[i]);
        }
        free(auth);
    }
    //sorting the index
    qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    
    

    //array initialazing
    size = get_table_size(tab)*2;
    char** sep_index = malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate authors and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strToken = strtok(NULL, "¤");
        strcpy(sep_index[i+1], strToken);
    }

    free_table(tab);
    free_table(index);
    free(csize);
    return sep_index;
   
}

char** search_date(char* date){
        //initialization of index
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search_title failed");
        exit(EXIT_FAILURE);
    }
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    if (index[0] == NULL){
        perror("malloc index[0] in search_title failed");
        exit(EXIT_FAILURE);
    }
    int size=0;
    char* csize = (char*)malloc(sizeof(char)*5);
    if (csize == NULL){
        perror("malloc csize in search_title failed");
        exit(EXIT_FAILURE);
    }
    sprintf(csize, "%d", size);
    strcpy(index[0], csize);

    //retrieving the book's date that contains name
    char* d;
    for(int i = 1; i<=get_table_size(tab); i++){
        d = get_date(tab[i]);
        if (strstr(d, date) != NULL || cstring_cmp(date, "")==0){
            size++;
            //rezise index
            index = (char**)realloc(index, sizeof(char*)*(size+2));
            if (index == NULL){
                perror("realloc index in search_title failed");
                exit(EXIT_FAILURE);
            }
            sprintf(csize, "%d", size);
            strcpy(index[0], csize);
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE +1));
            if (index[size] == NULL){
                perror("malloc index[size] in search_title failed");
                exit(EXIT_FAILURE);
            }
            strcpy(index[size], d);
            //adding a separator token
            strcat(index[size], "¤");
            strcat(index[size], tab[i]);
        }
        free(d);
    }
    //sorting the index
    qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    
    

    //array initialazing
    size = get_table_size(tab)*2;
    char** sep_index = malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate authors and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search_title failed");
            exit(EXIT_FAILURE);
        }
        strToken = strtok(NULL, "¤");
        strcpy(sep_index[i+1], strToken);
    }

    free_table(tab);
    free_table(index);
    free(csize);
    return sep_index;
}

void search(){
    //TODO
}