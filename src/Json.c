#include "../include/Json.h"

//getters for users
char* get_pwd(char* idUser){
    //TODO
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


int get_grade(char* idUser){
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

int set_grade(char* idUser, int status){
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