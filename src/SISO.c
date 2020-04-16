#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../include/SISO.h"
#define JSMN_HEADER
#include "../include/Json.h"

void cleanscr(){
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

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

    read_string(temp,9);
    //ASCII check
    for(int i=0; i<strlen(temp); i++){
        if (((int)temp[i] < 48 || (int)temp[i] > 57) && (int)temp[i] != 45){
            bool = 0;
        }
    }
    if (bool== 0 || temp[0] == '\0') return 1;    

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
        string[size_str] = '\0';
        cleanbuff();
    }
    else{
        *enter = '\0';
    }
}


void print_user(char* id){
    printf("id = %s\n",id);
    char* arg = get_forename(id);
    printf("forename = %s\n",arg);
    free(arg);
    arg = get_name(id);
    printf("name = %s\n",arg);
    free(arg);
    printf("grade = %d\n",get_grade(id));
    arg = get_pwd(id);
    printf("cryptedPw = %s\n",arg);
    free(arg);
    arg = get_mail(id);
    printf("mail = %s\n",arg);
    free(arg);

    
    char** tab2 = get_possession(id);
    int taille = get_table_size(tab2);
    printf("possession : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("%d = %s\n",i,tab2[i]);
    }
    free_table(tab2);
    
    char** tab = get_borrowlist(id);
    taille = get_table_size(tab);
    printf("borrow : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("%d = %s\n",i,tab[i]);
    }
    free_table(tab);
}

void print_object(char* id){
    printf("id = %s\n",id);
    char* data = get_title(id);
    printf("tiltle : %s\n",data);
    free(data);
    data = get_pagenb(id);
    printf("number of pages : %s\n",data);
    free(data);
    data = get_author(id);
    printf("author : %s\n",data);
    free(data);
    data = get_date(id);
    printf("date : %s\n",data);
    free(data);
    data = get_borrower(id);
    printf("borrower : %s\n",data);
    free(data);
    data = get_owner(id);
    printf("owner : %s\n",data);
    free(data);
    data = get_type(id);
    printf("type : %s\n",data);
    free(data);

}
