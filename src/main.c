#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"


int main(int argc, char const *argv[])
{
    printf("rose are red\nviolets are blue\nthis main is on the edge\nof a new and wonderfull youth\n");
    char** tab = get_possession("j");
    free_table(tab);
    
    printf("ok\n");

    char** tab2 = get_borrowlist("j");
    free_table(tab2);
    return 0;
}
