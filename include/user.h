#ifndef __USERH__
	#define __USERH__
	#define IDSIZE 64
	#define NAMESIZE 64
	#define PWSIZE 64
	#define MAILSIZE 64


typedef struct user_s* User;

int crea_user(char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession);

	/*
	check for existing usernames
	create a User struct Named new_user
	create a Json for new_user
	free new_user
	*/
void suppr_us(char* id,User user);
	/*
	remove the Json for this id and all his belongings
*/
void ban(char* id,User user);
	/*
	add the mail to the black list
	suppr(id)
	*/
int login(char* id, char* pwd, User util);
	/*
	check the user identity and fill util with infos in user’s json
	*/
int borrowing(User util, char* idObject);
	/*
	update status of the object and add it of the current user’s borrowing list  
	*/
int return_back(char* id, char* idObject);
	/*
	update status of the object and remove it of the current user’s borrowing list  
	*/
int return_back_all(char* id);
	/*
	update status of all objects and remove it of the current user’s borrowing list  
	*/
int suppr_all_possession(char* id);
	/*
	update status of the object and remove it of the current user’s borrowing list
	*/
int add_possession(User util, char* idObject);
	/*
	add idObject to the user’s possesion list 
	*/
int suppr_possession(char* id, char* idObject);
	/*
	remove idObject of the user’s possesion list 
	*/

void encrypt(char* pwd, char* crypwd);
#endif
