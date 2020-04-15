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
    add_livre("0","2", 3, "4", 5, "6", "7");
    return 0;
}

int main()
{
    printf("hello world\n");
    User current_user = crea_user("007","james","bond","jamesbond@gmail.com",4,"motdepasse");
    /*print_User(current_user);
    logout(current_user);
    print_User(current_user);
    supr_userlist("007");
    supr_usermail("jamesbond@gmail.com");
    free_user(current_user); */ 
    return 0;
}