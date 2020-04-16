#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
    char** brw; //list of current borrowings 	
    int grade; //define the amount of power of the user
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
    return (int) util->grade;
}

void uset_grade(int grade, User util){
    util->grade = grade;
}

char** uget_brw(User util){
    char** brw = util->brw;
	int size = get_table_size(brw);

    char** nv_brw=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }

	return nv_brw;
}

void uset_brw(char** brw, User util){
    /*char** tab= util->brw;
    if ( tab != NULL){
        free_table(tab);
    }*/
    util->brw = brw;
}

char** uget_possession(User util){
    char** pos= util->possession;
	int size = get_table_size(pos);
    char** nv_pos=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_pos[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_pos[j],pos[j]);
    }

	return nv_pos;
}

void uset_possession(char** possession, User util){
    /*char** tab= util->possession;
    if ( tab != NULL){
        free_table(tab);
    }*/
    util->possession = possession;
}

User crea_user(char* id, char* forename, char* name, char* mail, int grade, char* cryptedPw){
    User user = malloc(sizeof(struct user_s));
    uset_id(id,user);
    uset_forename(forename,user);
    uset_name(name,user);
    uset_mail(mail, user);
    uset_grade(grade,user);
    uset_cryptedPwd(cryptedPw,user);

    
    char** rand=(char**)malloc(sizeof(char*)*(1));//TOFREE
    *rand = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(rand[0], "%d", 0);
    
    uset_brw(duplicate_table(rand),user);
    uset_possession(rand,user);

    add_userlist(id);
    add_usermail(mail);
    add_us(user);
	return user;
}

int possession_free(User user){
    int result = 0;
    char** pos = uget_possession(user);
    int size = get_table_size(pos);
    for(int j = 1; j<= size; j++){
        printf("%s\n",pos[j]);
        char* borrower_id = get_borrower(pos[j]);
        printf("%s borrower .%s.\n",pos[j],borrower_id);
        if(strcmp("", borrower_id) != 0){
            result ++;
        }
        free(borrower_id);
    }
    free_table(pos);
    return result;
}

void suppr_us(char* id,User user){
	if (!(strcmp(user->id, id))){
        suppr_all_possession(user);
        return_back_all(user);
        supr_userlist(id);
        supr_usermail(id);
        add_blackList(get_mail(id));
        char* path = user_path(id);
        suppr_json(path);
        free(path);
    }
    else
    {
        printf("you can only suppr your own accout!\n");
    }
    
}

void ban(char* id,User user){
    if(uget_grade(user)>get_grade(id)){
        suppr_all_possession(user);
        return_back_all(user);
        supr_userlist(id);
        supr_usermail(id);
        add_blackList(get_mail(id));
        char* path = user_path(id);
        suppr_json(path);
        free(path);
    }
    else
    {
        printf("grade insufficient\n");
    }
    
}

User login(char* id, char* pwd){
    char crypwd[PWSIZE];
    encrypt(pwd, crypwd);
	if(strcmp (crypwd ,get_pwd (id) ) ){
        exit(1);
    }
    else
    {
        User util = malloc(sizeof(struct user_s));
        uset_id(id,util);
        char* pointer = get_name(id);
        uset_forename(pointer,util);
        free(pointer);
        pointer = get_forename(id);
        uset_name(pointer,util);
        free(pointer);
        pointer = get_mail(id);
        uset_mail(pointer,util);
        free(pointer);
        char**pointer_tab = get_borrowlist(id);     
        uset_brw(get_borrowlist(id),util);
        free(pointer_tab);
        uset_grade(get_grade(id),util);
        pointer = get_pwd(id);
        uset_cryptedPwd(pointer,util);
        free(pointer);
        pointer_tab = get_possession(id);
        uset_possession(get_possession(id),util);
        free(pointer_tab);
        return util;
    }
}

User charge_user(char* id){
    User util = malloc(sizeof(struct user_s));
    uset_id(id,util);
    char* pointer = get_name(id);
    uset_forename(pointer,util);
    free(pointer);
    pointer = get_forename(id);
    uset_name(pointer,util);
    free(pointer);
    pointer = get_mail(id);
    uset_mail(pointer,util);
    free(pointer);
    char**pointer_tab = get_borrowlist(id);     
    uset_brw(get_borrowlist(id),util);
    free(pointer_tab);
    uset_grade(get_grade(id),util);
    pointer = get_pwd(id);
    uset_cryptedPwd(pointer,util);
    free(pointer);
    pointer_tab = get_possession(id);
    uset_possession(get_possession(id),util);
    free(pointer_tab);
    return util;
}

void logout(User user){
    uset_id("",user);
    uset_forename("",user);
    uset_name("",user);
    uset_mail("",user);
    uset_grade(0,user);
    uset_cryptedPwd("",user);

    int size = 0;
    char** tab=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *tab = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(tab[0], "%d", size);
    
    uset_brw(duplicate_table(tab),user);
    uset_possession(tab,user);
}

void free_user(User user){
    free_table(user->brw);
    free_table(user->possession);

    free(user);
}

int borrowing(User util, char* idObject){
    char** brw = uget_brw(util);
	int size = get_table_size(brw);

    char ** nv_brw=(char**)malloc(sizeof(char*)*(size+2));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size+1);

    for(int j = 1; j<= size; j++){
        nv_brw[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_brw[j],brw[j]);
    }
    nv_brw[size+1]=(char*)malloc(sizeof(char)*(IDSIZE));
    strcpy(nv_brw[size+1],idObject);

    set_borrowlist(util->id,nv_brw);
    set_borrower(idObject,util->id);
    uset_brw(nv_brw,util);

    free_table(brw);
	return 0;
}

int return_back(char* idObject, User util){
    char** brw = uget_brw(util);
	int size = get_table_size(brw);
    int p = -1;
    int i = 1;


    for(int j = 1; j<= size; j++){
        if (!(strcmp(brw[j],idObject))){
            p = j;
        }
    }

    if (p==-1){
        return 1;
    }
    char ** nv_brw=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size-1);

    for(int j = 1; j<= size; j++){
        if (p!=j){
            nv_brw[i]=(char*)malloc(sizeof(char)*(IDSIZE));
            strcpy(nv_brw[i],brw[j]);

            i++;
        }        
    } 

    uset_brw(nv_brw, util);
    set_borrower(idObject,"");    
    set_borrowlist(util->id, nv_brw);

    free_table(brw);
	return 0;
}

int return_back_all(User util){
	int size = 0;
    char ** nv_brw=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    char** brw = uget_brw(util);
    size = get_table_size(brw);
    for (int i = 1; i<=size; i++){
        set_borrower(brw[i],"");
    }

    uset_brw(duplicate_table(nv_brw), util);
    set_borrowlist(util->id, nv_brw);

    return 0;
}

int add_possession(User user, char* idObject, char* name, int pagenb, char* author, int date, char* kind){
    char** pos = uget_possession(user);
	int size = get_table_size(pos);

    char ** nv_pos=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size+1);

    for(int j = 1; j<= size; j++){
        nv_pos[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_pos[j],pos[j]);
    }

    nv_pos[size+1]=(char*)malloc(sizeof(char)*(IDSIZE));
    strcpy(nv_pos[size+1],idObject);

    add_livre(idObject, name, pagenb, author, date, user->id,kind);
    set_possesion(user->id, duplicate_table(nv_pos));
    uset_possession(nv_pos,user);
    free_table(pos);
	return 0;
}

int suppr_possession(char* idObject, User user){
    if(strcmp("", get_borrower(idObject))){
        return 2;
    }
    char** pos = uget_possession(user);
	int size = get_table_size(pos);
    int p = -1;
    int i = 1;


    for(int j = 1; j<= size; j++){
        if (!(strcmp(pos[j],idObject))){
            p = j;
        }
    }

    if (p==-1){
        return 1;
    }
    char ** nv_pos=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size-1);

    for(int j = 1; j<= size; j++){
        if (p!=j){
            nv_pos[i]=(char*)malloc(sizeof(char)*(IDSIZE));
            strcpy(nv_pos[i],pos[j]);

            i++;
        }        
    } 

    uset_possession(duplicate_table(nv_pos), user);
    char* path = object_path(idObject);
    suppr_json(path);
    free(path);  
    set_possesion(user->id, nv_pos);

    free_table(pos);
	return 0;
}

int suppr_all_possession(User user){
    char** pos = uget_possession(user);
    int size = get_table_size(pos);
    for(int j = 1; j<= size; j++){
        char* borrower_id = get_borrower(pos[j]);
        if(strcmp("", borrower_id) != 0){
            User borrower = charge_user(borrower_id);
            return_back(pos[j], borrower);
            free_user(borrower);
        }
        free(borrower_id);
        char* path = object_path(pos[j]);
        suppr_json(path);
        free(path); 
    }
    free_table(pos);

    size = 1;
    char ** nv_pos=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size-1);
    
    set_possesion(user->id,duplicate_table(nv_pos));
    uset_possession(nv_pos, user);

    return 0;
}


void encrypt(char* pwd,char* crypwd){
    int p;
    int cle = 0;
    for(int i = 0; i < strlen(pwd); i++){
        p = pwd[i] - 32;
        cle = cle + p;
    } 
    cle = cle%95;
    for(int i = 0; i < strlen(pwd); i++){
        int p = pwd[i] -32;
        crypwd[i] = (char)((cle+p)%95+32);
    } 
}

char** duplicate_table(char** tab){
	int size = get_table_size(tab);

    char ** nv_tab=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_tab = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_tab[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_tab[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_tab[j],tab[j]);
    }

	return nv_tab;
}








