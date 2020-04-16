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
    char *ia = (char *)a;
    char *ib = (char *)b;
    if(*ia < *ib) return -1;
    if(*ia > *ib) return 1;
    if (*(ia + 1) != '\0' && *(ib + 1) != '\0') return cstring_cmp(ia+1, ib+1);
    return 0;
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
    if (get_table_size(index)>1){
        qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    }
    

    //array initialazing
    size = get_table_size(index)*2;
    char** sep_index = malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);

    //separate name and id
    char* strToken;
    for(int i = 1; i<=(get_table_size(sep_index)); i=i+2){
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
    char* title;
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
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE*2 +4));
            if (index[size] == NULL){
                perror("malloc index[size] in search_title failed");
                exit(EXIT_FAILURE);
            }
            //we put the author
            strcpy(index[size], auth);
            //then the title in case of multiple books per author
            title = get_title(tab[i]);
            strcat(index[size], " : ");
            strcat(index[size], title);
            free(title);
            //adding separator token
            strcat(index[size], "¤");
            //adding the ID
            strcat(index[size], tab[i]);
        }
        free(auth);
    }
    //sorting the index
    if (get_table_size(index)>1){
        qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    }
    

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

void sub_searchM(int* pos, int* query, char** index){
    while(*pos == -3){
        //print the found list
        printf(" ----------------------------------------------------------------------\n");
        printf("|  Select one, to rule them all                              0 : back  |\n");
        printf(" ----------------------------------------------------------------------\n");
                        
        for (int i = 1; i<get_table_size(index); i=i+2){
            printf("  %d : %s\n", i/2+1, index[i]);
        }
        if (get_table_size(index) == 0){
            printf("                           There is no such thing\n");
        }
        printf("Selection : ");
        read_int(query);
        if (*query == 0) {
            *pos = -1;
            cleanscr();
            printf("                         --------------\n");
            printf("                        | Back to menu |\n");
            printf("                         --------------\n");
            //cleanscr();
        }
        else if (*query < get_table_size(index) && *query > 0){
            *pos = -4;
            while(*pos == -4){
                //print the selected object
                printf(" ----------------------------------------------------------------------\n");
                printf("|                                                            0 : back  |\n");
                printf(" ----------------------------------------------------------------------\n");
                print_object(index[*query*2]);
                read_int(pos);
                switch (*pos){
                    case 0:
                        *pos = -3;
                        break;
                                
                    default:
                        *pos = -4;
                        break;
                }
            }
        }
        else{
            *pos = -3;
        }
    }
}

void search(){
    int query = -1;
    int pos = -1;
    char* arg = (char*)malloc(sizeof(char)*NAMESIZE);
    strcpy(arg, "");
    char** index;
    while (pos == -1){
        printf(" ----------------------------------------------------------------------\n");
        printf("|             Welcome to the quantum search algorithme!!               |\n");
        printf(" ----------------------------------------------------------------------\n");
        printf("| Please define the type of algorithm in order to find your happiness: |\n");
        printf("|                                                                      |\n");
        printf("| Search by:                                                 Quit : 0  |\n");
        printf("| 1 : Title                                                            |\n");
        printf("| 2 : Author                                                           |\n");
        printf("| 3 : Date                                                             |\n");
        printf("| 4 : Type                                                             |\n");
        printf(" ----------------------------------------------------------------------\n");
        pos = -2;
        while (pos == -2){
            printf("  Your query : ");
            read_int(&query);
            //printf("\n%d\n", query);
            switch (query)
            {
                case 1:
                    
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted title (to list them all just press enter)   |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    printf("  title : ");
                    read_string(arg, NAMESIZE);
                    index = search_title(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index);
                    break;

                case 2:
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted author (to list them all just press enter)  |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    printf("  Author : ");
                    read_string(arg, NAMESIZE);
                    index = search_author(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index);
                    break;
                
                case 3:
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted date (to list them all just press enter)    |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    break;

                case 4:
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted type (to list them all just press enter)    |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    break;
                case 0:
                    pos = 1;
                    printf("                             Goodby\n");
                    break;

                default:
                    query= -2;
                    break;
            }
        }
    }
    
    
}