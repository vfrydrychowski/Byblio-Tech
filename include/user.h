#define __USERH__

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
int return_back(char* id, char* idObject, User util);
	/*
	update status of the object and remove it of the current user’s borrowing list  
	*/
int return_back_all(char* id, User util);
	/*
	update status of all objects and remove it of the current user’s borrowing list  
	*/
int suppr_all_possession(char* id,User user);
	/*
	update status of the object and remove it of the current user’s borrowing list
	*/
int add_possession(User user, char* idObject, char* name, int pagenb, char* author, int date, char* owner, int kind);
	/*
	add idObject to the user’s possesion list 
	*/
int suppr_possession(char* id, char* idObject, User user);
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
void dupilcate_table(char** tab);
	/*
	dupilcate tab of ID using a malloc
	*/