#ifndef __SISOH__
#define __SISOH__

/* 
    clean the buffer
*/
void cleanbuff();

/*
    get safely an int
    return 1 if stdin is not a num
    */
int read_int(int* nb);
    
/*
    get safely a string
    assumed that string has already been allocate
    */
void read_string(char* string, int size_str);
    

#endif