#include <stdio.h>
#include <stdlib.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"


int main(int argc, char const *argv[])
{
    printf("rose are red\nviolets are blue\nthis main is on the edge\nof a new and wonderfull youth\n");
    char** tab = search_date("20");
    printf("%s\n", jsontochar("data/object/222222222.json"));
    for(int i = 0; i<= get_table_size(tab); i++){
        printf("%s\n", tab[i]);
    } 
    return 0;
}
