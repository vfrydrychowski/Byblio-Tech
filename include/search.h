#ifndef __SEARCHH__
	#define __SEARCHH__




void upd_index();
	/*
	update an index file were books are listed ready to be sort
	*/
/*
	return a table whith books id in odd and books titles in even
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