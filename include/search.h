#ifndef __SEARCHH__
	#define __SEARCHH__
	#include "../include/user.h"


/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b);

/*
	return a table whith books id in odd and books titles in even
	to get the list of evey titles, name = ""
*/
char** search_title(char* name);
	
/*
	return a table whith books id in odd and books authors in even
	to get the list of evey authors, name = ""
*/	
char** search_author(char* author);
	
/*
	return a table whith books id in odd and books date in even
	to get the list of evey dates, name = ""
*/
char** search_date(char* date);

/*
	return a table whith books id in odd and books types in even
	to get the list of evey types, name = ""
*/
char** search_type(char* type);

/* Sub module of search
	print the ojects in index and handle the borrowing part of search */
void sub_searchM(int* pos, int* query, char** index, User us);

/*
	start the search module
	This module is an interface to search a books and borrow a book
*/	
void search(User us);
	
#endif