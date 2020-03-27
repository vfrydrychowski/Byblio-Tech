#define __USERH__

typedef struct user* User;

int crea_user(char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession);

	/*
	check for existing usernames
	create a User struct Named new_user
	create a Json for new_user
	free new_user
	*/
void suppr_us(char* id);
	/*
	remove the Json for this id and all his belongings
*/
void ban(char* id);
	/*
	add the mail to the black list
	suppr(id)
	*/
int login(char* id, char* pwd, User util);
	/*
	check the user identity and fill util with infos in user’s json
	*/
void logout(User util);
	/*
	free util
	*/
int borrowing(User util, char* idObject);
	/*
	update status of the object and add it of the current user’s borrowing list  
	*/
int return_back(User util, char* idObject);
	/*
	update status of the object and remove it of the current user’s borrowing list  
	*/
int add_possession(User util, char* idObject);
	/*
	add idObject to the user’s possesion list 
	*/
int suppr_possession(User util, char* idObject);
	/*
	remove idObject of the user’s possesion list 
	*/
int get_size(char** tableau);
	/*
	return the number of element in the tableau
	*/