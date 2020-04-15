#ifndef __SEARCHH__
	#define __SEARCHH__



/*
	update an index file were books are listed ready to be sort
*/
void upd_index();
	
/*
	return a table whith books id in odd and books titles in even
	to get the list of evey titles, name = ""
*/
char** search_title(char* name);
	
/*
	return a table whith books id in odd and books authors in even
*/	
char** search_author(char* author);
	
/*
	return a table whith books id in odd and books date in even
*/
char** search_date(char* date);
	
void search();
	/*
	start the search module
	*/
#endif