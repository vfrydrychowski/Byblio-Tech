#ifndef __SEARCHH__
	#define __SEARCHH__




void upd_index();
	/*
	update an index file were books are listed ready to be sort
	*/
char* search_name(char* name);
	/*
	return the books infos fitting the passed name;
	*/
char* search_author(char* author);
	/*
	return the books infos fitting the passed author;
	*/
char* search_date(int date);
	/*
	return the books infos fitting the passed date;
	*/
void search();
	/*
	start the search module
	*/
#endif