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
    util->possession = possession;
}

int exist_user(char* id){
    //search if this id has a json
    char* path = user_path(id);//path : data/user/id.json
    FILE*ptf = fopen(path,"r");
    if (ptf== NULL){
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(ptf);
    
}

int crea_user(User* util, char* id, char* forename, char* name, char* mail, int grade, char* Pwd){
    if(exist_in_list(mail,"blacklist") == 0){//search if the mail is in blacklist
        return 1;
    }
    if(exist_in_list(mail,"m") == 0){//search if an other user has already this mail
        return 2;
    }
    if(exist_in_list(id,"u") == 0){//search if an other users has alerady this id
        return 3;
    }
    else{
        *util= malloc(sizeof(struct user_s));//alloue le pointeur *util
        //fill the struct
        uset_id(id,*util);
        uset_forename(forename,*util);
        uset_name(name,*util);
        uset_mail(mail, *util);
        uset_grade(grade,*util);
        char* cryptedpwd = (char*)malloc(PWSIZE * sizeof(char));
        encrypt(Pwd,cryptedpwd);
        uset_cryptedPwd(cryptedpwd,*util);

    
        char** rand=(char**)malloc(sizeof(char*)*(1));//TOFREE
        *rand = (char*)malloc(sizeof(char)*(IDSIZE));
        sprintf(rand[0], "%d", 0);

    
        uset_brw(duplicate_table(rand),*util);
        uset_possession(rand,*util);

        //update userlist and mail list
        add_userlist(id);
        add_usermail(mail);
        //create the json for *util
        add_us(*util);
    	return 0;
    }
}

int possession_borrow(User user){
    int result = 0;
    char** pos = uget_possession(user);//get the possession list
    int size = get_table_size(pos);
    for(int j = 1; j<= size; j++){
        char* borrower_id = get_borrower(pos[j]);//get the borrower of the item J
        if(strcmp("", borrower_id) != 0){
            result ++;//add 1 if there is a borrower
        }
        free(borrower_id);
    }
    free_table(pos);
    return result;
}

int exist_in_list(char* substring,char* listname){
    char* path = user_path(listname);//get the list path
    if(strstr(jsontochar(path),substring) == NULL){//look for an occurence of substring in the list
        return 1;
    }
    else
    {
        return 0;
    }
}

int suppr_us(User user){
    if (possession_borrow(user)==0){//check if a possession is borrow
        //update possession and borrow
        suppr_all_possession(user);
        return_back_all(user);
        //update list
        supr_userlist(user->id);
        supr_usermail(user->mail);
        //suppr the json of user
        char* path = user_path(user->id);
        suppr_json(path);
        free(path);
        return 0;
    }
    else{
        return 1;
    }    
}

int ban(char* id,User user){
    if (exist_in_list(id,"u") == 0){//check if the user exist
        if(uget_grade(user)>get_grade(id)){//check if the grade of user is high enough
            User ban = charge_user(id);//charge the struct of the user to ban
            //update of possession an borrow
            suppr_all_possession(ban);
            return_back_all(ban);
            //utpdate the list
            supr_userlist(id);
            char* mail = get_mail(id);
            supr_usermail(mail);
            add_blackList(mail);
            free(mail);
            //supr the json
            char* path = user_path(id);
            suppr_json(path);
            free(path);
            free_user(ban);
            return 0;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 1;
    }
    
        
}

int login(User* util,char* id, char* pwd){
    if(exist_user(id) == 1){//check if the user exist
        return 1;
    }
    char crypwd[PWSIZE];
    char* pass = get_pwd (id);
    encrypt(pwd, crypwd);
	if(strcmp (crypwd, pass) ){//check if the password is correct
        free(pass);
        return 2;
    }
    free(pass);
    *util = malloc(sizeof(struct user_s));//alloue le pointeur *util
    //fill the struct with json's data
    uset_id(id,*util);
    char* pointer = get_forename(id);
    uset_forename(pointer,*util);
    free(pointer);
    pointer = get_name(id);
    uset_name(pointer,*util);
    free(pointer);
    pointer = get_mail(id);
    uset_mail(pointer,*util);
    free(pointer);
    char**pointer_tab = get_borrowlist(id);     
    uset_brw(get_borrowlist(id),*util);
    free(pointer_tab);
    uset_grade(get_grade(id),*util);
    pointer = get_pwd(id);
    uset_cryptedPwd(pointer,*util);
    free(pointer);
    pointer_tab = get_possession(id);
    uset_possession(get_possession(id),*util);
    free(pointer_tab);
    return 0;
}

User charge_user(char* id){
    User util = malloc(sizeof(struct user_s));//alloue le pointeur util
    //fill the struct with json's data
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
    return util;//retourne le pointeur
}

void logout(User user){
    free_user(user);
}

void free_user(User user){
    free_table(user->brw);
    free_table(user->possession);

    free(user);
}

int exist_in_table(char* id,char** table){
    int occurence = 0;
    int size = get_table_size(table);
    for(int i = 1; i <= size; i++){
        if(strcmp(table[i],id) == 0){
            occurence ++;
        }
    }
    return occurence;
}

int borrowing(User util, char* idObject){
    char* current_borrower = get_borrower(idObject);
    if(strcmp("",current_borrower) != 0){//check if the object is already borrow
        return 1;
    }
    free(current_borrower);
    //create a new table of borrow
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

    //update the struct the user json and the object json
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

    //check if the user has borrow this object
    for(int j = 1; j<= size; j++){
        if (!(strcmp(brw[j],idObject))){
            p = j;
        }
    }
    if (p==-1){
        return 1;
    }

    //create the new table of borrow
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

    //update the struc the json of user an the json of object
    uset_brw(nv_brw, util);
    set_borrower(idObject,"");    
    set_borrowlist(util->id, nv_brw);

    free_table(brw);
	return 0;
}

void return_back_all(User util){
	//create the new table of borrow
    int size = 0;
    char ** nv_brw=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_brw = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_brw[0], "%d", size);

    //update object's json
    char** brw = uget_brw(util);
    size = get_table_size(brw);
    for (int i = 1; i<=size; i++){
        set_borrower(brw[i],"");
    }

    //update the stuct and the user's json
    uset_brw(duplicate_table(nv_brw), util);
    set_borrowlist(util->id, nv_brw);


}

void add_possession(User user,char* name, int pagenb, char* author, int date, char* kind){
    //create an idObject based on time
    time_t t = time(NULL);
    char* time = ctime(&t);
    char* idObject = malloc(sizeof(char)*IDSIZE);
    strncpy(idObject,time,24);
    char** pos = uget_possession(user);
	int size = get_table_size(pos);

    //create the new table of possession
    char ** nv_pos=(char**)malloc(sizeof(char*)*(size+1));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size+1);

    for(int j = 1; j<= size; j++){
        nv_pos[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_pos[j],pos[j]);
    }

    nv_pos[size+1]=(char*)malloc(sizeof(char)*(IDSIZE));
    strcpy(nv_pos[size+1],idObject);

    //create the json of the object and update the list of object
    add_livre(idObject, name, pagenb, author, date, user->id,kind);
    add_objlist(idObject);
    //update the struct and the user's json
    set_possesion(user->id, duplicate_table(nv_pos));
    uset_possession(nv_pos,user);
    free_table(pos);
}

int suppr_possession(char* idObject, User user){
    //check if the object has a borrower
    if(strcmp("", get_borrower(idObject)) != 0){
        return 1;
    }
    char** pos = uget_possession(user);
	int size = get_table_size(pos);
    int p = -1;
    int i = 1;

    //check if the user possess the object 
    for(int j = 1; j<= size; j++){
        if (!(strcmp(pos[j],idObject))){
            p = j;
        }
    }

    if (p==-1){
        return 2;
    }

    //create the new table of possession
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

    //update the struct, suppr the json of the object,update the object list and user's json
    uset_possession(duplicate_table(nv_pos), user);
    char* path = object_path(idObject);
    suppr_json(path);
    free(path); 
    supr_objlist(idObject); 
    set_possesion(user->id, nv_pos);

    free_table(pos);
	return 0;
}

void suppr_all_possession(User user){
    char** pos = uget_possession(user);
    int size = get_table_size(pos);
    //free all the possession of user
    for(int j = 1; j<= size; j++){
        char* borrower_id = get_borrower(pos[j]);
        if(strcmp("", borrower_id) != 0){//if a possession is borrow, get back the object
            User borrower = charge_user(borrower_id);
            return_back(pos[j], borrower);
            free_user(borrower);
        }
        free(borrower_id);
        //suppr the json of the object and update the object list
        char* path = object_path(pos[j]);
        suppr_json(path);
        free(path); 
        supr_objlist(pos[j]);
    }
    free_table(pos);

    //create the new possession table
    size = 1;
    char ** nv_pos=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_pos = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_pos[0], "%d", size-1);
    
    //update the struct and the user's json
    set_possesion(user->id,nv_pos);
    uset_possession(nv_pos, user);
}


void encrypt(char* pwd,char* crypwd){
    int p;
    int cle = 0;
    //create the key
    for(int i = 0; i < strlen(pwd); i++){
        p = pwd[i] - 32;
        cle = cle + p;
    } 
    cle = cle%95;
    //crypte the password
    for(int i = 0; i < strlen(pwd); i++){
        int p = pwd[i] -32;
        crypwd[i] = (char)((cle*(i+1)+p)%95+32);
    }
    crypwd[strlen(pwd)] = '\0';
}

int new_pwd(User user, char* pwd, char* nv_pwd){
    char crypwd[PWSIZE];
    char* pass = get_pwd(user->id);
    encrypt(pwd, crypwd);
	if(strcmp (crypwd , pass ) ){//check the password
        free(pass);
        return 1;
    }
    free(pass);
    encrypt(nv_pwd,crypwd);
    //update the user's json
    set_pwd(user->id, crypwd);
    return 0;
}

int new_username(User user,char* new_username){
    if (exist_in_list(new_username,"u") == 0){//check if an other user has alredy this user name
        return 1;
    }
    supr_userlist(user->id);
    add_userlist(new_username);
    char* path = user_path(user->id);
    suppr_json(path);
    free(path);
    uset_id(new_username, user);
    add_us(user);
    
    char** possession = uget_possession(user);
    char** borrow = uget_brw(user);
    
    int size = get_table_size(possession);
    for (int i = 1; i <= size; i++){
        set_owner(possession[i],new_username);
    }
    size = get_table_size(borrow);
    for (int i = 1; i <= size; i++){
        set_borrower(borrow[i],new_username);
    }
    return 0;
}

int change_grade(User user,char* id,int newgrade){
    if (user->grade <= get_grade(id)){
        return 1;
    }
    if (user->grade < newgrade){
        return 2;
    }
    char* grade = malloc(sizeof(char)*5);
    sprintf(grade, "%d", newgrade);
    set_grade(id,grade);
    free(grade);
    return 0;
}

char** duplicate_table(char** tab){
	int size = get_table_size(tab);
    //copie the table
    char ** nv_tab=(char**)malloc(sizeof(char*)*(size));//TOFREE
    *nv_tab = (char*)malloc(sizeof(char)*(IDSIZE));
    sprintf(nv_tab[0], "%d", size);

    for(int j = 1; j<= size; j++){
        nv_tab[j]=(char*)malloc(sizeof(char)*(IDSIZE));
        strcpy(nv_tab[j],tab[j]);
    }

	return nv_tab;
}








