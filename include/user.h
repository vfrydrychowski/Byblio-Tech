#define __USERH__

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

int crea_user(User user, char* id, char* forename, char* name, char* mail, char** brw, int grade, char* cryptedPw, char** possession);

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
int return_back(char* idObject, User util);
	/*
	update status of the object and remove it of the current user’s borrowing list  
	*/
int return_back_all(User util);
	/*
	update status of all objects and remove it of the current user’s borrowing list  
	*/
int suppr_all_possession(User user);
	/*
	update status of the object and remove it of the current user’s borrowing list
	*/
int add_possession(User user, char* idObject, char* name, int pagenb, char* author, int date, char* owner, int kind);
	/*
	add idObject to the user’s possesion list 
	*/
int suppr_possession(char* idObject, User user);
	/*
	remove idObject of the user’s possesion list 
	*/
int get_size(char** tableau);
	/*
	return the number of element in the tableau
	*/

void encrypt(char* pwd, char* crypwd);
	/*
	encrypt pwd and put it in crywd
	*/

void free_table(char** tab);
	/*
	free le tableau
	*/
char** duplicate_table(char** tab);
	/*
	dupilcate tab of ID using a malloc
	*/