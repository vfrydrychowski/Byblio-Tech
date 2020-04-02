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
    char** brw; //list of current borrowings 	
    int grade; //define the amounfree_table(nv_brw);t of power of the user
    char cryptedPw[PWSIZE]; //crypted password
    char** possession;  //list of all possesed books
}user;

char* uget_id(User util){
    return util->id;
}

void uset_id(char* id, User util){
    strcpy(util->id,id);
}

char* uget_forename(User util){
    return util->forename;
}

void uset_forename(char* forename, User util){
    strcpy(util->forename,forename);
}

char* uget_name(User util){
    return util->name;
}

void uset_name(char* name, User util){
    strcpy(util->name,name);
}

char* uget_mail(User util){
    return util->mail;
}

void uset_mail(char* mail, User util){
    strcpy(util->mail,mail);
}

char* uget_cryptedPwd(User util){
    return util->cryptedPw;
}

void uset_cryptedPwd(char* cryptedPwd, User util){
    strcpy(util->cryptedPw,cryptedPwd);
}

int uget_grade(User util){
    return util->grade;
}

void uset_grade(char* grade, User util){
    strcpy(util->grade,grade);
}

char* uget_brw(User util){
    char** brw = util->brw);
	int size = get_size(brw);

    char * nv_brw=(char*)malloc(sizeof(char*)*(size));//TOFREE
    nv_brw = (char)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

	return nv_brw;
}

void uset_brw(char** brw, User util){
	int size = get_size(brw);

    char * nv_brw=(char*)malloc(sizeof(char*)*(size));//TOFREE
    nv_brw = (char)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

    util->brw = nv_brw;

    free_table(brw);
	return 0;
}

char* uget_brw(User util){
    char** brw = util->brw);
	int size = get_size(brw);

    char * nv_brw=(char*)malloc(sizeof(char*)*(size));//TOFREE
    nv_brw = (char)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

	return nv_brw;
}

void uset_id(char** brw, User util){
	int size = get_size(brw);

    char * nv_brw=(char*)malloc(sizeof(char*)*(size));//TOFREE
    nv_brw = (char)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

    util->brw = nv_brw;

    free_table(brw);
	return 0;
}

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

int borrowing(User util, char* idObject){
    char** brw = get_borrowlist(util->id);
	int size = get_size(brw);

    char * nv_brw=(char*)malloc(sizeof(char*)*(size+2));//TOFREE
    nv_brw = (char)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size+1);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

    strcpy(nv_brw[size+1],idObject);

    set_borrowlist(util->id, nv_brw);

    free_table(nv_brw);
    free_table(brw);
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


void free_table(char** tab){
    int size = atoi(*tab);
    for(int j = 0; j<= size; j++){
        free(tab[j]);
    }
    free(tab);
}














