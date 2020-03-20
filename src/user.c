#include <stdlib.h>
#include <stdio.h>

#define IDSIZE 64
#define NAMESIZE 64
#define PWSIZE 64

typedef struct user_s {

    char* id; //ID of a user 

    //info user	
    char* forename;
    char* name;
    char* mail;
    char** brw; //list of current borrowings 	
    int grade; //define the amount of power of the user
    char* cryptedPw; //crypted password
    char** possession;  //list of all possesed books
}user;



