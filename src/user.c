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
	return 0;
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

int get_size(char** tableau){
	// TODO
	return 0;
}

void encrypt(char* pwd){

}

















