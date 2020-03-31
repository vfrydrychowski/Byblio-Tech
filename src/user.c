#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
#include "../include/user.h"
#include "../include/object.h"
#include "../include/SISO.h"
#define JSMN_HEADER
#include "../include/Json.h"



typedef struct user_s {

    char id[IDSIZE]; //ID of a user 

    //info user	
    char forename[NAMESIZE];
    char name[NAMESIZE];
    char mail[MAILSIZE];
    char* brw[IDSIZE]; //list of current borrowings
	char* possession[IDSIZE];  //list of all possesed books 	
    int grade; //define the amount of power of the user
    char cryptedPw[PWSIZE]; //crypted password
}user;

int crea_user(char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession){
	// TODO
	return 0;
}

void suppr_us(char* id){
	// TODO
}

void ban(char* id){
	// TODO
}

int login(char* id, char* pwd, User util){
	// TODO
	return 0;
}

void logout(User util){
	// TODO
}

int borrowing(User util, char* idObject){
	// TODO
	return 0;
}

int return_back(User util, char* idObject){
	// TODO
	return 0;
}

int add_possession(User util, char* idObject){
	// TODO
	return 0;
}

int suppr_possession(User util, char* idObject){
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

















