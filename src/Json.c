#include "../include/Json.h"
#include "../include/jsmn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//getters for users
char* get_pwd(char* idUser){
    jsmn_parser p;
    jsmntok_t t[128];
    jsmn_init(&p);
    char* JSON_STRING = jsontochar(idUser);
    int r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));
    if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    exit(2);
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    exit(2);
    }
    int i =0;
    while (jsoneq(JSON_STRING, &t[i], "psw")!=0){
        i++;
    }

    return strndup(JSON_STRING + t[i+1].start, t[i+1].end - t[i+1].start);
    return "";
}


char* get_name(char* idUser){
    //TODO
    return "";
}


char* get_surname(char* idUser){
    //TODO
    return "";
}


char* get_mail(char* idUser){
    //TODO
    return "";
}


char** get_possession(char* idUser){
    //TODO
    return "";
}


char** get_borrowlist(char* idUser){
    //TODO
    return "";
}


char* get_grade(char* idUser){
    //TODO
    return "";
}



//getters for objects
char* get_title(char* idObject){
    //TODO
    return "";
}


char* get_pagenb(char* idObject){
    //TODO
    return "";
}


char* get_author(char* idObject){
    //TODO
    return "";
}


char* get_date(char* idObject){
    //TODO
    return "";
}


char* get_borrower(char* idObject){
    //TODO
    return "";
}


char* get_owner(char* idObject){
    //TODO
    return "";
}


char* get_type(char* idObject){
    //TODO
    return "";
}



//setters for users
int set_pwd(char* idUser, char* pwd){
    //TODO
    return 0;
}

int set_name(char* idUser, char* name){
    //TODO
    return 0;
}

int set_surname(char* idUser, char* surname){
    //TODO
    return 0;
}

int set_mail(char* idUser, char* mail){
    //TODO
    return 0;
}

int set_possesion(char* idUser, char** possesion){
    //TODO
    return 0;
}

int set_borrowlist(char* idUser, char ** borrowlist){
    //TODO
    return 0;
}

int set_grade(char* idUser, char* status){
    //TODO
    return 0;
}


//setters for users
int set_title(char* idObject, char* title){
    //TODO
    return 0;
}

int set_pagenb(char* idObject, char* pagenb){
    //TODO
    return 0;
}

int set_author(char* idObject, char* author){
    //TODO
    return 0;
}

int set_date(char* idObject, char* date){
    //TODO
    return 0;
}

int set_owner(char* idObject, char* owner){
    //TODO
    return 0;
}

int set_borrower(char* idObject, char* borrower){
    //TODO
    return 0;
}

int set_type(char* idObject, char* type){
    //TODO
    return 0;
}

int add_us(User us){
    //TODO
    return 0;
}

int add_livre(char*ID, char* name, int pagenb, char* author, int date, char* owner, int kind){
    //TODO
    return 0;
}

int suppr_json(char*ID){
    //TODO
    return 0;
}


int add_blackList(char*mail){
    //TODO
    return 0;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int findSize(FILE *fp) 
{ 
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    int res = ftell(fp); 
    fseek(fp, 0L, SEEK_SET);
    return res; 
} 

char* jsontochar(char * file_path){
    FILE *jsptr;
    if ((jsptr = fopen(file_path, "r")) == NULL){
       printf("Error opening file!");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }

    int i;
    char* c;
    int size_file = findSize(jsptr);
    c = malloc(sizeof(char)*size_file);
    //fill c with the text in the json file
    for (int j = 0;(i = getc(jsptr)) != EOF;j++){
        c[j] = i;
    }
    fclose(jsptr);
    return c;
}

void chartojson(char * file_path, char * json_text){
    FILE *jsptr;
    if ((jsptr = fopen(file_path, "w")) == NULL){
       printf("Error opening file!");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
    fprintf(jsptr, "%s", json_text);
    fclose(jsptr);
}