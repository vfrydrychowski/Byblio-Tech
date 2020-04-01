#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../include/Json.h"
#define JSMN_HEADER
#include "../include/jsmn.h"


//TOFREE
char* user_path(char* iduser){
    char*path = (char*)malloc(sizeof("data/user/")+strlen(iduser)*sizeof(char)+sizeof(".json"));//TOFREE
    strcat(path,"data/user/");
    strcat(path, iduser);
    strcat(path, ".json");
    return path;
}

//TOFREE
char* object_path(char* idObject){
    char*path = (char*)malloc(sizeof("data/object/")+strlen(idObject)*sizeof(char)+sizeof(".json"));//TOFREE
    strcat(path,"data/object/");
    strcat(path, idObject);
    strcat(path, ".json");
    return path;
}

//generic getters for json file
//TOFREE
char *get_gen(char* ID, char* arg){
    jsmn_parser p;
    jsmntok_t t[128];
    jsmn_init(&p);
    char* JSON_STRING = jsontochar(ID);//TOFREE
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
    while (jsoneq(JSON_STRING, &t[i], arg)!=0 && i<=r){
        i++;
    }
    if(i>r){
        printf("no keys found\n");
        exit(3);
    }
    char* dup = strndup(JSON_STRING + t[i+1].start, t[i+1].end - t[i+1].start);//TOFREE
    free(JSON_STRING);
    return dup;
}

int get_table_size(char** table){
	return atoi(*table);
}

//TOFREE_TAB
char** get_gen_table(char* ID, char* arg){
    jsmn_parser p;
    jsmntok_t t[128];
    jsmn_init(&p);
    char* JSON_STRING = jsontochar(ID);//TOFREE
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

    
    int i =1;
    while ((jsoneq(JSON_STRING, &t[i-1], arg) !=0 ) && (i<=r)){
        i++;
    }
    if(i>r){
        printf("no keys found\n");
        exit(3);
    }
    char ** tab=(char**)malloc(sizeof(char*)*(t[i].size+1));//TOFREE
    sprintf(tab[0], "%d", t[i].size);
    for(int j = 1; j<= t[i].size; j++){
        tab[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        tab[j]=strndup(JSON_STRING + t[i + j].start, t[i+ j].end - t[i+ j].start);//TOFREE
    }
    free(JSON_STRING);
    return tab;
}

void free_table(char** tab){
    int size = atoi(*tab);
    for(int j = 1; j<= size; j++){
        free(tab[j]);
    }
    free(tab);
}

//getters for users
char* get_pwd(char* idUser){
    idUser = user_path(idUser);
    return get_gen(idUser, "pwd");
}


char* get_name(char* idUser){
    idUser = user_path(idUser);
    return get_gen(idUser, "name");
}


char* get_forename(char* idUser){
    idUser = user_path(idUser);
    return get_gen(idUser, "forename");
}


char* get_mail(char* idUser){
    idUser = user_path(idUser);
    return get_gen(idUser, "mail");
}


char** get_possession(char* idUser){
    idUser = user_path(idUser);
    return get_gen_table(idUser, "possession");
}


char** get_borrowlist(char* idUser){
    idUser = user_path(idUser);
    return get_gen_table(idUser, "borrowlist");
}


int get_grade(char* idUser){
    idUser = user_path(idUser);
    char*cpy = get_gen(idUser, "pwd");
    return atoi(cpy);
}



//getters for objects
char* get_title(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "title");
}


char* get_author(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "author");
}


char* get_date(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "date");
}


char* get_borrower(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "borrower");
}


char* get_owner(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "owner");
}


char* get_type(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "type");
}


void set_gen_string(char*ID, char* arg, char* str){
    jsmn_parser p;
    jsmntok_t t[128];
    jsmn_init(&p);
    char* JSON_STRING = jsontochar(ID);//TOFREE
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

    
    int i =1;
    while ((jsoneq(JSON_STRING, &t[i], arg) !=0 ) && (i<=r)){
        i++;
    }
    if(i>r){
        printf("no keys found\n");
        exit(3);
    }

    
    char* new_string = strndup(JSON_STRING, t[i+ 1].start);//TOFREE
    new_string = realloc(new_string, sizeof(char)*strlen(JSON_STRING) + sizeof(char)+strlen(str));
    strcat(new_string, str);
    strcat(new_string, JSON_STRING + t[i+1].end);
    printf("%s\n", new_string);
    chartojson(ID, new_string);
    free(new_string);
    free(JSON_STRING);
}

//setters for users
void set_pwd(char* idUser, char* pwd){
    idUser = user_path(idUser);
    set_gen_string(idUser, "pwd", pwd);
    free(idUser);
}

void set_name(char* idUser, char* name){
    idUser = user_path(idUser);
    set_gen_string(idUser, "name", name);
    free(idUser);
}

void set_forename(char* idUser, char* forename){
    idUser = user_path(idUser);
    set_gen_string(idUser, "forename", forename);
    free(idUser);
}

void set_mail(char* idUser, char* mail){
    idUser = user_path(idUser);
    set_gen_string(idUser, "mail", mail);
    free(idUser);
}

void set_possesion(char* idUser, char** possesion){
    //TODO
}
void set_borrowlist(char* idUser, char ** borrowlist){
    //TODO
    return 0;
}

void set_grade(char* idUser, char* grade){
    idUser = user_path(idUser);
    set_gen_string(idUser, "grade", grade);
    free(idUser);
}


//setters for object
void set_title(char* idObject, char* title){
    idObject = object_path(idObject);
    set_gen_string(idObject, "title", title);
    free(idObject);
}

void set_pagenb(char* idObject, char* pagenb){
    idObject = user_path(idObject);
    set_gen_string(idObject, "pagenb", pagenb);
    free(idObject);
}

void set_author(char* idObject, char* author){
    idObject = user_path(idObject);
    set_gen_string(idObject, "author", author);
    free(idObject);
}

void set_date(char* idObject, char* date){
    idObject = user_path(idObject);
    set_gen_string(idObject, "date", date);
    free(idObject);
}

void set_owner(char* idObject, char* owner){
    idObject = user_path(idObject);
    set_gen_string(idObject, "owner", owner);
    free(idObject);
}

void set_borrower(char* idObject, char* borrower){
    idObject = user_path(idObject);
    set_gen_string(idObject, "borrower", borrower);
    free(idObject);
}

void set_type(char* idObject, char* type){
    idObject = user_path(idObject);
    set_gen_string(idObject, "type", type);
    free(idObject);
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

int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
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

//TOFREE
char* jsontochar(char * file_path){
    FILE *jsptr;
    if ((jsptr = fopen(file_path, "r")) == NULL){
       printf("Error opening file!\n");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }

    int i;
    char* c;
    int size_file = findSize(jsptr);
    c = (void*)malloc(sizeof(char)*size_file);//TOFREE
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
       printf("Error opening file!\n");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
    fprintf(jsptr, "%s", json_text);
    fclose(jsptr);
}