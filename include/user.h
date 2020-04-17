#ifndef __USERH__
	#define __USERH__
	#define IDSIZE 64
	#define NAMESIZE 64
	#define PWSIZE 64
	#define MAILSIZE 64


typedef struct user_s* User;

//getters for users
char* uget_id(User util);
char* uget_forename(User util);
char* uget_name(User util);
char* uget_mail(User util);
char* uget_cryptedPwd(User util);
int uget_grade(User util);
char** uget_brw(User util);
char** uget_possession(User util);

//setters for users
void uset_id(char* id, User util);
void uset_forename(char* forename, User util);
void uset_name(char* name, User util);
void uset_mail(char* mail, User util);
void uset_cryptedPwd(char* cryptedPwd, User util);
void uset_grade(int grade, User util);
void uset_brw(char** brw, User util);
void uset_possession(char** possession, User util);

	/*
	if the user exist return 0
	else return 1
	*/
int exist_user(char* id);
	/*
	charge the User struct util and fill it with the arguments
	create a Json for util
	return 0 if everything goes well
	return 1 if the mail is in the black list
	return 2 if an other user has alreary this mail
	return 3 if an other user has already this id
	*/
int crea_user(User* util, char* id, char* forename, char* name, char* mail, int grade, char* Pwd);
	/*
	return the number of possession witch has a borrower
	*/
int possession_borrow(User user);
	/*
	return 0 if all the possession of user are not borrow
	else return the number of possession witch have a borrower
	*/
int exist_in_list(char* substring,char* listname);
	/*
	suppr all object file of id possessions
	return back all the borrowing of id
	add the mail to the black list
	return 0 if all goes well
	return 1 if one of the possession of user has been borrow
	*/
int suppr_us(User user);
	/*
	suppr all object file of id possessions
	return back all the borrowing of id
	add the mail to the black list
	return 0 if all goes well
	return 1 if the id do not exist
	return 2 if user has higher or the same grade than id  
	*/
int ban(char* id,User user);
	/*
	check the user identity and fill util with infos in user’s json and return 0
	return 1 if the user do not exist
	return 2 if pwd (after being crypted) don't match the one in the json
	*/
int login(User* user, char* id, char* pwd);
	/*
	create au user struc whith data of the correponding json
	*/
User charge_user(char* id);
	/*
	free the struct user
	*/
void logout(User user);
	/*
	free the struct user
	*/
void free_user(User user);
	/*
	return the number of occurence of chaine in table
	*/
int exist_in_table(char* chaine,char** table);
	/*
	update status of the object, add it of the current user’s borrowing list and return 0
	return 1 if the object is already borrow
	*/
int borrowing(User util, char* idObject);
	/*
	update status of the object, remove it of the current user’s borrowing list and return 0
	return 1 if user hasn't borrow the object 
	*/
int return_back(char* idObject, User util);
	/*
	update status of all objects, remove it of the current user’s borrowing list
	*/
void return_back_all(User util);
	/*
	update status of the object and remove it of the current user’s borrowing list
	*/
void suppr_all_possession(User user);
	/*
	add idObject to the user’s possesion list 
	*/
void add_possession(User user, char* name, int pagenb, char* author, int date, char* kind);
	/*
	remove idObject of the user’s possesion list and return 0 
	if Object is borrow by an other user return 1
	if the user don't possess the Object return 2
	*/
int suppr_possession(char* idObject, User user);
	/*
	encrypt pwd and put it in crywd
	*/
void encrypt(char* pwd, char* crypwd);
	/*
	change the crypted password in the user's json
	return 0 if everything goes well
	return 1 if pwd do not match whith the password in the json
	*/
int new_pwd(User user, char* pwd, char* nv_pwd);
	/*
	change the id in struct user
	change the json of the user
	change the borrower in his borrow's json
	change the owner in his possession json
	return 0 if everything goes well
	return 1 if an other user as already new_usermane as id
	*/
int new_username(User user,char* new_username);
	/*
	change the grade of the user id
	return 0 if everything goes well
	return 1 if id has higher grade than user
	return 2 if the newgrade is higher than user's grade
	*/
int change_grade(User user,char* id,int newgrade);
	/*
	dupilcate tab of ID using a malloc
	*/
char** duplicate_table(char** tab);

#endif