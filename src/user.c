#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "../include/user.h"
#include "../include/object.h"
#include "../include/SISO.h"
#include "../include/Json.h"

#define IDSIZE 64
#define NAMESIZE 64
#define PWSIZE 64
#define MAILSIZE 64

typedef struct user_s {

    char id[IDSIZE]; //ID of a user 

    //info user	
    char forename[NAMESIZE];
    char name[NAMESIZE];
    char mail[MAILSIZE];
    char* brw[IDSIZE]; //list of current borrowings 	
    int grade; //define the amount of power of the user
    char cryptedPw[PWSIZE]; //crypted password
    char* possession[IDSIZE];  //list of all possesed books
}User;

int crea_user(char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession){
	// TODO
	return 0;
}

void suppr_us(char* id,User user){
	if (!(strcmp(user.id, id))){
        if(suppr_all_possession(id)== 0){
            return_back_all(id);
            suppr_json(id);
        }
    }
}

void ban(char* id,User user){
    if(user.grade>get_grade(id)){
        if(suppr_all_possession(id)== 0){
            return_back_all(id);
            add_blackList(get_mail(id));
            suppr_json(id);
        }
    }
}

int login(char* id, char* pwd, User util){
    char crypwd[PWSIZE];
    encrypt(pwd, crypwd);
	if(strcmp (crypwd ,get_pwd (id) ) ){
        return 1;
    }
    else
    {
        strcpy(util.id, id);
        strcpy(util.forename, get_name(id));
        strcpy(util.name, get_surname(id));
        strcpy(util.mail, get_mail(id));
        strcpy(util.brw, get_borrowlist(id));
        util.grade = get_grade(id);
        strcpy(util.cryptedPw, crypwd);
        strcpy(util.possession, get_possession(id));
        return 0;
    }
}

void logout(User util){
	// TODO
	return 0;
}

int borrowing(User util, char* idObject){
	// TODO
	return 0;
}

int return_back(char* id, char* idObject){
	// TODO
	return 0;
}

int return_back_all(char* id){
    // TODO
    return 0;
}

int suppr_all_possession(char* id){
    // TODO
    return 0;
}

int add_possession(User user, char* idObject){
	// TODO
	return 0;
}

int suppr_possession(char* id, char* idObject){
	// TODO
	return 0;
}

int get_size(char** tableau){
	// TODO
	return 0;
}

void encrypt(char* pwd,char* crypwd){
    int p;
    int cle = 0;
    for(int i = 0; i < strlen(pwd); i++){
        int p = pwd[i] - 32;
        cle = cle + p;
    } 
    cle = cle%95;
    for(int i = 0; i < strlen(pwd); i++){
        int p = pwd[i] -32;
        crypwd[i] = (char)((cle+p)%95+32);
    } 
}

















