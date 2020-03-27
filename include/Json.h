#ifndef __JSONH__
     #define __JSONH__
#endif // !__JSONH__

#include "user.h"

//getters for users
char* get_pwd(char* idUser);
char* get_name(char* idUser);
char* get_surname(char* idUser);
char* get_mail(char* idUser);
char** get_possession(char* idUser);
char** get_borrowlist(char* idUser);
char* get_grade(char* idUser);

//getters for objects
char* get_title(char* idObject);
char* get_pagenb(char* idObject);
char* get_author(char* idObject);
char* get_date(char* idObject);
char* get_borrower(char* idObject);
char* get_owner(char* idObject);
char* get_type(char* idObject);

//setters for users
int set_pwd(char* idUser, char* pwd);
int set_name(char* idUser, char* name);
int set_surname(char* idUser, char* surname);
int set_mail(char* idUser, char* mail);
int set_possesion(char* idUser, char** possesion);
int set_borrowlist(char* idUser, char ** borrowlist);
int set_grade(char* idUser, char* status);

//setters for users
int set_title(char* idObject, char* title);
int set_pagenb(char* idObject, char* pagenb);
int set_author(char* idObject, char* author);
int set_date(char* idObject, char* date);
int set_owner(char* idObject, char* owner);
int set_borrower(char* idObject, char* borrower);
int set_type(char* idObject, char* type);
int add_us(User us);


int add_livre(char*ID, char* name, int pagenb, char* author, int date, char* owner, int kind);
/*
         create the json file with the infos passed
    */

int suppr_json(char*ID);
/*
         delete the json file name by the passed ID
    */

int add_blackList(char*mail);
/*
         add the given mail to the black list
    */

