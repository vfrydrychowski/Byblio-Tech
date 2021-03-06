#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/search.h"
#include "../include/Json.h"
#include "../include/SISO.h"
#include "../include/user.h"


/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b) 
{ 
    char* a2 = (char*)a;
    char* b2 = (char*)b;

    return strcmp(a2,b2);
}


/*
	return a table whith books id in odd and books titles in even
	to get the list of evey titles, name = ""
*/
char** search_title(char* name){
    //initialization of index
    char** tab = get_gen_table("data/object/obj.json", "obj"); //fill the array with all object ID
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search_title failed");
        exit(EXIT_FAILURE);
    }
    //size init of index
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
            //put the title
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
    char** sep_index = (char**)malloc(sizeof(char*)*(size+1));
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
    size = get_table_size(index)*2;
    char** sep_index = (char**)malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate authors and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search failed");
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
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search failed");
        exit(EXIT_FAILURE);
    }
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    if (index[0] == NULL){
        perror("malloc index[0] in search failed");
        exit(EXIT_FAILURE);
    }
    int size=0;
    char* csize = (char*)malloc(sizeof(char)*5);
    if (csize == NULL){
        perror("malloc csize in search failed");
        exit(EXIT_FAILURE);
    }
    sprintf(csize, "%d", size);
    strcpy(index[0], csize);

    //retrieving the book's dates that contains d    te
    char* d;
    char* title;
    for(int i = 1; i<=get_table_size(tab); i++){
        d = get_date(tab[i]);
        if (strstr(d, date) != NULL || cstring_cmp(date, "")==0){
            size++;
            //rezise index
            index = (char**)realloc(index, sizeof(char*)*(size+2));
            if (index == NULL){
                perror("realloc index in search failed");
                exit(EXIT_FAILURE);
            }
            sprintf(csize, "%d", size);
            strcpy(index[0], csize);
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE*2 +4));
            if (index[size] == NULL){
                perror("malloc index[size] in search failed");
                exit(EXIT_FAILURE);
            }
            //we put the date
            strcpy(index[size], d);
            //then the title in case of multiple books per date
            title = get_title(tab[i]);
            strcat(index[size], " : ");
            strcat(index[size], title);
            free(title);
            //adding separator token
            strcat(index[size], "¤");
            //adding the ID
            strcat(index[size], tab[i]);
        }
        free(d);
    }
    //sorting the index
    if (get_table_size(index)>1){
        qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    }
    

    //array initialazing
    size = get_table_size(index)*2;
    char** sep_index = (char**)malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate authors and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search failed");
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



char** search_type(char* type){
    char** tab = get_gen_table("data/object/obj.json", "obj");
    char** index = (char**)malloc(sizeof(char*));
    if (index == NULL){
        perror("malloc index in search failed");
        exit(EXIT_FAILURE);
    }
    index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    if (index[0] == NULL){
        perror("malloc index[0] in search failed");
        exit(EXIT_FAILURE);
    }
    int size=0;
    char* csize = (char*)malloc(sizeof(char)*5);
    if (csize == NULL){
        perror("malloc csize in search failed");
        exit(EXIT_FAILURE);
    }
    sprintf(csize, "%d", size);
    strcpy(index[0], csize);

    //retrieving the book's type that contains type
    char* t;
    char* title;
    for(int i = 1; i<=get_table_size(tab); i++){
        t = get_type(tab[i]);
        if (strstr(t, type) != NULL || cstring_cmp(type, "")==0){
            size++;
            //rezise index
            index = (char**)realloc(index, sizeof(char*)*(size+2));
            if (index == NULL){
                perror("realloc index in search failed");
                exit(EXIT_FAILURE);
            }
            sprintf(csize, "%d", size);
            strcpy(index[0], csize);
            index[size] = (char*)malloc(sizeof(char)*(IDSIZE + NAMESIZE*2 +4));
            if (index[size] == NULL){
                perror("malloc index[size] in search failed");
                exit(EXIT_FAILURE);
            }
            //we put the type
            strcpy(index[size], t);
            //then the title in case of multiple books per type
            title = get_title(tab[i]);
            strcat(index[size], " : ");
            strcat(index[size], title);
            free(title);
            //adding separator token
            strcat(index[size], "¤");
            //adding the ID
            strcat(index[size], tab[i]);
        }
        free(t);
    }
    //sorting the index
    if (get_table_size(index)>1){
        qsort(index+1, get_table_size(index), sizeof(char*), cstring_cmp);
    }
    

    //array initialazing
    size = get_table_size(index)*2;
    char** sep_index = (char**)malloc(sizeof(char*)*(size+1));
    sprintf(csize, "%d", size);
    sep_index[0] = (char*)malloc(sizeof(char)*IDSIZE);
    strcpy(sep_index[0], csize);
    
    //separate type and id
    char* strToken;
    for(int i = 1; i<=get_table_size(sep_index); i=i+2){
        strToken = strtok(index[i/2+1], "¤");
        sep_index[i] = (char*)malloc(sizeof(char)*NAMESIZE);
        if (sep_index[i] == NULL){
            perror("sep_index[i] in search failed");
            exit(EXIT_FAILURE);
        }
        strcpy(sep_index[i], strToken);
        sep_index[i+1] = (char*)malloc(sizeof(char)*IDSIZE);
        if (sep_index[i+1] == NULL){
            perror("sep_index[i+1] in search failed");
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


void sub_searchM(int* pos, int* query, char** index, User us){
    while(*pos == -3){
        cleanscr();
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
        *query = -3;
        read_int(query);
        if (*query == 0) {
            *pos = -1;
            cleanscr();
            printf("                         --------------\n");
            printf("                        | Back to menu |\n");
            printf("                         --------------\n");
            //cleanscr();
        }
        else if (*query <= get_table_size(index) && *query > 0){ //if the chosen number is a book
            *pos = -4;
            while(*pos == -4){
                //print the selected object
                printf(" ----------------------------------------------------------------------\n");
                printf("|   1 : borrow                                               0 : back  |\n");
                printf(" ----------------------------------------------------------------------\n");
                print_object(index[*query*2]);
                read_int(pos);
                switch (*pos){
                    case 0:
                        *pos = -3;
                    break;
                    
                    case 1://try to borrow
                        switch(borrowing(us, index[*query*2])){
                            case 1://already borrowed
                                printf(" ----------------------------------------------------------------------\n");
                                printf("|         Already borrow, sorry, you may connect another day :)        |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                *pos = -1;
                                cleanbuff();
                            break;

                            case 0://back
                                *pos = -3;
                            break;

                            default:
                            break;
                        }

                    break;

                    default://go to books selection
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

void search(User us){
    int query = -1;
    int pos = -1;
    char* arg = (char*)malloc(sizeof(char)*NAMESIZE);
    strcpy(arg, "");
    char** index;
    //home's search
    while (pos == -1){
        cleanscr();
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
        printf("| 5 : ID                                                               |\n");
        printf(" ----------------------------------------------------------------------\n");
        pos = -2;
        while (pos == -2){
            printf("  Your query : ");
            read_int(&query);
            switch (query)
            {
                case 1://search by title
                    
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted title (to list them all just press enter)   |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    printf("  title : ");
                    read_string(arg, NAMESIZE);
                    index = search_title(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index, us);
                    break;

                case 2://search by author
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted author (to list them all just press enter)  |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    printf("  Author : ");
                    read_string(arg, NAMESIZE);
                    index = search_author(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index, us);
                    break;
                
                case 3://search by date
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted date (to list them all just press enter)    |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    read_string(arg, NAMESIZE);
                    index = search_date(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index, us);
                    break;

                case 4://search by type
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|  Please enter the wanted type (to list them all just press enter)    |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    read_string(arg, NAMESIZE);
                    index = search_type(arg);
                    pos = -3;
                    sub_searchM(&pos, &query, index, us);
                    break;

                case 5://search by id
                    pos = -3;
                    char* id = (char*)malloc(sizeof(char)*IDSIZE);
                    char* objlist;
                    while(pos == -3){
                        printf(" ----------------------------------------------------------------------\n");
                        printf("|                     Please enter the wanted ID                       |\n");
                        printf(" ----------------------------------------------------------------------\n");
                        printf("  ID : ");
                        read_string(id, IDSIZE);
                        objlist = jsontochar("data/object/obj.json");//TOFREE
                        if (strstr(objlist, id) == NULL){//si l'objet n'existe pas
                            printf("                       This ID does not exist          ");
                            pos = -2;
                            cleanbuff();
                        }
                        else{
                            pos = -4;
                            while(pos == -4){
                                //print the selected object
                                printf(" ----------------------------------------------------------------------\n");
                                printf("|   1 : borrow                                               0 : back  |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                print_object(id);
                                read_int(&pos);
                                switch (pos){
                                    case 0:
                                        pos = -1;
                                    break;
                                    
                                    case 1://try to borrow
                                        switch(borrowing(us, id)){
                                            case 1:
                                                printf(" ----------------------------------------------------------------------\n");
                                                printf("|         Already borrow, sorry, you may connect another day :)        |\n");
                                                printf(" ----------------------------------------------------------------------\n");
                                                cleanbuff();
                                                pos=-1;
                                            break;

                                            case 0:
                                                pos = -1;
                                            break;

                                            default:
                                            break;
                                        }

                                    break;

                                    default:
                                        pos = -4;
                                    break;
                                }
                            }
                        }
                    free(objlist);
                    }
                    
                break;

                case 0://back
                    pos = 1;
                    break;

                default://ask a nex query
                    query= -2;
                    break;
            }
        }
    }
    free(arg);
    
}