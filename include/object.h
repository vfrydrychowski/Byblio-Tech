#ifndef __OBJECTH__
	#define __OBJECTH__


int borrowing_object(char* idObject, char* idUser);
	/*
update borrower of the Object in the JSON
	*/

int return_object(char* idObject, char* idUser);
	/*
	update borrower to NULL if idUser==Object borrower
	*/
int create_object(char* ID, char* name, int pagenb, char* author, int date, char* owner, int kind);
	/*
	create the JSON file and update the current user possessions
	*/
int suppr_object(char* idObject, char* idUser);
	/*
	if object borrower==NULL and idUser==object possesor  :  
		-remove the Json of object
		-update possession of user
	*/
#endif