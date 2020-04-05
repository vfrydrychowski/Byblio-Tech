#ifndef __JSONH__
     #define __JSONH__
     #include <stdio.h>
     #ifndef __USERH__
          #include "user.h"
     #endif
     
     #ifndef JSMN_H
          #include "jsmn.h"
          #define JSMN_HEADER
     #endif



//build the path to the user folder
char* user_path(char* iduser);
//build the path to the object folder
char* object_path(char* idObject);
//generic getters for json file
char *get_gen(char* ID, char* arg);
/* return the number of elements in an table of char 
whom the first element is the number of elements exept himself  */
int get_table_size(char** table);
//genneric getters of array for json files
char** get_gen_table(char* ID, char* arg);
//function to properly free a table of our design
void free_table(char** tab);
//transform a tab into a string of a json array type
char *tab_to_string(char** tab);


//getters for users
char* get_pwd(char* idUser);
char* get_name(char* idUser);
char* get_forename(char* idUser);
char* get_mail(char* idUser);
char** get_possession(char* idUser);
char** get_borrowlist(char* idUser);
int get_grade(char* idUser);

//getters for objects
char* get_title(char* idObject);
char* get_pagenb(char* idObject);
char* get_author(char* idObject);
char* get_date(char* idObject);
char* get_borrower(char* idObject);
char* get_owner(char* idObject);
char* get_type(char* idObject);

//generic setter of strings for json
void set_gen_string(char*ID, char* arg, char* str);
//generic setter of table for json
void set_gen_table(char* ID, char* arg, char ** tab);

//setters for users
void set_pwd(char* idUser, char* pwd);
void set_name(char* idUser, char* name);
void set_forename(char* idUser, char* surname);
void set_mail(char* idUser, char* mail);
void set_possesion(char* idUser, char** possesion);
void set_borrowlist(char* idUser, char ** borrowlist);
void set_grade(char* idUser, char* grade);

//setters for objects
void set_title(char* idObject, char* title);
void set_pagenb(char* idObject, char* pagenb);
void set_author(char* idObject, char* author);
void set_date(char* idObject, char* date);
void set_owner(char* idObject, char* owner);
void set_borrower(char* idObject, char* borrower);
void set_type(char* idObject, char* type);

//add user file, return 1 if user already exist 
int add_us(User user);


int add_livre(char*ID, char* name, int pagenb, char* author, int date, char* owner, int kind);
/*
         create the json file with the infos passed
    */

int suppr_json(char*path);
/*
         delete the json file name by the passed ID
    */

int add_blackList(char*mail);
/*
         add the given mail to the black list
    */



//compare the given string with the name of the given token
int jsoneq(const char *json, jsmntok_t *tok, const char *s);

int findSize(FILE *fp);


char* jsontochar(char * file_path);

void chartojson(char * file_path, char * json_text);
#endif