#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../include/Json.h"
#define JSMN_HEADER
#include "../include/jsmn.h"


//TOFREE
char* user_path(char* iduser){
    char*path = (char*)malloc(sizeof("data/user/")+strlen(iduser)*sizeof(char)+sizeof(".json"));//TOFREE
    if (path == NULL){
        perror("user_path MALLOC ERROR");
        exit(1);
    }
    strcpy(path,"data/user/");
    strcat(path, iduser);
    strcat(path, ".json");
    return path;
}

//TOFREE
char* object_path(char* idObject){
    char*path = (char*)malloc(sizeof("data/object/")+strlen(idObject)*sizeof(char)+sizeof(".json"));//TOFREE
    if (path == NULL){
        perror("object_path MALLOC ERROR");
        exit(1);
    }
    strcpy(path, "data/object/");
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
     if (tab == NULL){
        perror("get_gen_table tab MALLOC ERROR");
        exit(1);
    }
    *tab = (char*)malloc(sizeof(char)*(IDSIZE));
     if (*tab == NULL){
        perror("get_gen_table *tab MALLOC ERROR");
        exit(1);
    }
    sprintf(tab[0], "%d", t[i].size);
    for(int j = 1; j<= t[i].size; j++){
        tab[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        if (tab[j] == NULL){
            perror("get_gen_table tab[j] MALLOC ERROR");
            exit(1);
        }
        tab[j]=strndup(JSON_STRING + t[i + j].start, t[i+ j].end - t[i+ j].start);//TOFREE
    }
    free(JSON_STRING);
    return tab;
}

char *tab_to_string(char** tab){
    if (get_table_size(tab) == 0) return "[]";
    char* str = (char*)malloc((sizeof(char)*IDSIZE+4)*(atoi(tab[0])+1));
    if (str == NULL){
            perror("tab_to_string str MALLOC ERROR");
            exit(1);
        }
    strcpy(str,"[\"");
    int sizetab = atoi(tab[0]);
    for (int i =1; i <= sizetab; i++){
        strcat(str, tab[i]);
        strcat(str, "\", \"");
    }
    char*temp = strndup(str, strlen(str)-3);
    free(str);
    str = (char*)realloc(temp, (sizeof(char)*IDSIZE+4)*(atoi(tab[0])+1));
    if (str == NULL){
            perror("tab_to_string str MALLOC ERROR");
            exit(1);
        }
    strcat(str, "]");
    return str;
}

void free_table(char** tab){
    int size = atoi(*tab);
    for(int j = 0; j<= size; j++){
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

char* get_pagenb(char* idObject){
    idObject = object_path(idObject);
    return get_gen(idObject, "pagenb");
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
    new_string = (char*)realloc(new_string, sizeof(char)*strlen(JSON_STRING) + sizeof(char)+strlen(str));
    if (new_string == NULL){
            perror("set_gen_string new_string MALLOC ERROR");
            exit(1);
        }
    strcat(new_string, str);
    strcat(new_string, JSON_STRING + t[i+1].end);
    chartojson(ID, new_string);
    free(new_string);
    free(JSON_STRING);
}

void set_gen_table(char* ID, char* arg, char ** tab){
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
    i++;
    char* strtab = tab_to_string(tab);
    char* pos = strndup(JSON_STRING, t[i].start);
    pos = (char*)realloc(pos, sizeof(char)*strlen(strtab)+sizeof(char)*strlen(JSON_STRING));
    if (pos == NULL){
        perror("set_gen_table pos MALLOC ERROR");
        exit(1);
    }
    strcat(pos, strtab);
    strcat(pos, JSON_STRING + t[i].end);
    chartojson(ID, pos);
    free(JSON_STRING);
    free(pos);
}

//setters for users
void set_pwd(char* idUser, char* pwd){
    idUser = user_path(idUser);
    set_gen_string(idUser, "pwd", pwd);
}

void set_name(char* idUser, char* name){
    idUser = user_path(idUser);
    set_gen_string(idUser, "name", name);
}

void set_forename(char* idUser, char* forename){
    idUser = user_path(idUser);
    set_gen_string(idUser, "forename", forename);
}

void set_mail(char* idUser, char* mail){
    idUser = user_path(idUser);
    set_gen_string(idUser, "mail", mail);
}

void set_possesion(char* idUser, char** possesion){
    idUser = user_path(idUser);
    set_gen_table(idUser, "possession", possesion);
}

void set_borrowlist(char* idUser, char ** borrowlist){
    idUser = user_path(idUser);
    set_gen_table(idUser, "borrowlist", borrowlist);
}

void set_grade(char* idUser, char* grade){
    idUser = user_path(idUser);
    set_gen_string(idUser, "grade", grade);
}


//setters for object
void set_title(char* idObject, char* title){
    idObject = object_path(idObject);
    set_gen_string(idObject, "title", title);
}

void set_pagenb(char* idObject, char* pagenb){
    idObject = object_path(idObject);
    set_gen_string(idObject, "pagenb", pagenb);
}

void set_author(char* idObject, char* author){
    idObject = object_path(idObject);
    set_gen_string(idObject, "author", author);
}

void set_date(char* idObject, char* date){
    idObject = object_path(idObject);
    set_gen_string(idObject, "date", date);
}

void set_owner(char* idObject, char* owner){
    idObject = object_path(idObject);
    set_gen_string(idObject, "owner", owner);
}

void set_borrower(char* idObject, char* borrower){
    idObject = object_path(idObject);
    set_gen_string(idObject, "borrower", borrower);
}

void set_type(char* idObject, char* type){
    idObject = object_path(idObject);
    set_gen_string(idObject, "type", type);
}

int add_us(User user){
    //existence check of user
    char*i = uget_id(user);
    char* id = user_path(i);
    FILE*ptf = fopen(id,"r");
    if (ptf!= NULL) {
        //fclose(ptf);
        fclose(ptf);
        return 1;
    }

    //add_userlist(i);
    

    char* JSON_user = "{\n  \"forename\" : \"\",\n  \"name\" : \"\",\n  \"mail\" : \"\",\n  \"borrowlist\" : [],\n  \"possession\" : [],\n  \"grade\" : 0,\n  \"pwd\" : \"\"\n}";
    chartojson(id, JSON_user);
    free(id);
    char* forename = uget_forename(user);
    set_forename(i, forename);
    //free(forename);
    char* name = uget_forename(user);
    set_name(i, name);
    //free(name);
    char* mail = uget_mail(user);
    //add_usermail(mail);
    set_mail(i, mail);
    //free(mail);
    char** borrowings = uget_brw(user);
    set_borrowlist(i, borrowings);
    //free_table(borrowings);
    char** possession = uget_possession(user);
    set_possesion(i, possession);
    //free_table(possession);
    char* grade = malloc(sizeof(char)*2);
    sprintf(grade,"%d",uget_grade(user));
    set_grade(i, grade);
    //free(grade);
    char* pwd = uget_cryptedPwd(user);
    set_pwd(i, pwd);
    //free(pwd);
    free(i);
    return 0;
} 

void add_livre(char*ID, char* title, int pagenb, char* author, int date, char* owner, char* type){
    //add_objlist(ID);
    ID = object_path(ID);
    char*JSON_obj = "{\n    \"title\" : \"\",\n    \"author\" : \"\",\n    \"date\" : 0,\n    \"pagenb\" : 0,\n    \"borrower\" : \"\",\n    \"owner\": \"\",\n    \"type\" : \"\"\n}";
    chartojson(ID, JSON_obj);
    set_title(ID, title);
    set_author(ID, author);
    char* d = malloc(sizeof(char)*5);
    sprintf(d, "%d", date);
    set_date(ID, d);
    sprintf(d, "%d", pagenb);
    set_pagenb(ID, d);
    set_borrower(ID, "NULL");
    set_owner(ID, owner);
    set_type(ID, type);
    free(d);
}

int suppr_json(char*path){
    FILE*ptf = fopen(path,"r");
    if (ptf== NULL) return 1;
    fclose(ptf);
    remove(path);
    return 0;
}


void add_blackList(char*mail){
    add_List("data/user/blacklist.json", mail);
}

void add_objlist(char*id){
    add_List("data/object/obj.json", id);
}

void add_userlist(char*id){
    add_List("data/user/u.json", id);
}

void add_usermail(char*mail){
    add_List("data/user/m.json", mail);
}

int add_List(char* path, char* arg){
    char* list=jsontochar(path);
    if (strstr(list, arg) != NULL) return 1;
    char* n_list = strndup(list, strlen(list) - 3);
    n_list = realloc(n_list, sizeof(char)*(strlen(list)+strlen(arg)+5));
    if (n_list == NULL){
        perror("add_List n_list MALLOC ERROR");
        exit(1);
    }
    strcat(strcat(strcat(n_list, ", \""), arg), "\"]\n}");
    chartojson(path, n_list);
    free(n_list);
    free(list);
    return 0;
}

void supr_blackList(char*mail){
    supr_List("data/user/blacklist.json", mail);
}

void supr_objlist(char*id){
    supr_List("data/object/obj.json", id);
}

void supr_userlist(char*id){
    supr_List("data/user/u.json", id);
}

void supr_usermail(char*id){
    supr_List("data/user/m.json", id);
}

int supr_List(char* path, char* arg){
    
    char* list = jsontochar(path);
    char* n_list;
    char* argpt = strstr(list, arg);
    if (argpt == NULL) return 1;
    if (argpt[-2] == '[' && argpt[1 + strlen(arg)] == ']') {
        n_list = "{\n    \"user\" : []\n}";
        chartojson(path, n_list);
        free(list);
        return 0;
    }
    else {
        int i = 0;
        while (list + i != argpt) i++;
        int j = 3;
        int g = 1;
        if (argpt[-2] == '['){
            j = 1;
            g = 3;
        }
        n_list = strndup(list, i-j);
        n_list = realloc(n_list, sizeof(char)*strlen(list));
        strcat(n_list, argpt + strlen(arg)+g);
        chartojson(path, n_list);
        free(n_list);
        free(list);
    }
    
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
    c = (char*)malloc(sizeof(char)*(size_file+1));//TOFREE
    if (c == NULL){
            perror("jsontochar c MALLOC ERROR");
            exit(1);
        }
    //fill c with the text in the json file
    for (int j = 0;(i = getc(jsptr)) != EOF && j<size_file;j++){
        c[j] = i;
    }
    c[size_file] = '\0'; //ensure that the string has an ending
    fclose(jsptr);
    return c;
}

void chartojson(char * file_path, char * json_text){
    FILE *jsptr;
    if ((jsptr = fopen(file_path, "w+")) == NULL){
       printf("Error opening file!\n");
       // Program exits if the file pointer returns NULL.
       exit(1);
    }
    fprintf(jsptr, "%s", json_text);
    fclose(jsptr);
}
