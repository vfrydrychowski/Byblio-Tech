#ifndef __SEARCHH__
	#define __SEARCHH__


/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b);

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

/*
	start the search module
*/	
void search();
	
#endif