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

int crea_user(User user,char* id, char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession){
    uset_id(id,user);
    uset_forename(forename,user);
    uset_name(name,user);
    uset_mail(mail, user);
    uset_grade(grade,user);
    uset_cryptedPwd(cryptedPw,user);
    uset_brw(brw,user);
    uset_possession(possession,user);

    add_us(user);
	return 0;
}

void suppr_us(char* id,User user){
	if (!(strcmp(user->id, id))){
        if(suppr_all_possession(user)== 0){
            return_back_all(user);
            suppr_json(id);
        }
    }
}

void ban(char* id,User user){
    if(uget_grade(user)>get_grade(id)){
        if(suppr_all_possession(user)== 0){
            return_back_all(user);
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
        return 0;
    }
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

    uset_brw(duplicate_table(nv_brw), util);
    set_borrower(idObject,util->id);    
    set_borrowlist(util->id, nv_brw);

    free_table(brw);
	return 0;
}

int return_back_all(User util){
	int size = 0;
    char ** nv_brw=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    uset_brw(duplicate_table(nv_brw), util);
    set_borrowlist(util->id, nv_brw);

    return 0;
}

int add_possession(User user, char* idObject, char* name, int pagenb, char* author, int date, char* owner, int kind){
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

    add_livre(idObject, name, pagenb, author, date, owner,kind);
    set_possesion(user->id, duplicate_table(nv_pos));
    uset_possession(nv_pos,user);
    free_table(pos);
	return 0;
}

int suppr_possession(char* idObject, User user){
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
    suppr_object(idObject,user->id);   
    set_possesion(user->id, nv_pos);

    free_table(pos);
	return 0;
}

int suppr_all_possession(User user){
    int size = 1;
    char ** nv_pos=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size-1);

    uset_brw(duplicate_table(nv_pos), user);
    set_borrowlist(user->id, nv_pos);

    return 0;
}

int get_size(char** tableau){
	return ((int) tableau[0][0]) - 48;
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

void print_user(User user){
    printf("id = %s\n",uget_id(user));
    printf("forename = %s\n",uget_forename(user));
    printf("name = %s\n",uget_name(user));
    printf("grade = %d\n",uget_grade(user));
    printf("cryptedPw = %s\n",uget_cryptedPwd(user));

    char** tab = uget_brw(user);
    int taille = get_size(tab);
    printf("borrow : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("id %d = %s\n",i,tab[i]);
    }
    free_table(tab);

    tab = uget_possession(user);
    taille = get_size(tab);
    printf("possession : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("id %d = %s\n",i,tab[i]);
    }
    free_table(tab);


}








