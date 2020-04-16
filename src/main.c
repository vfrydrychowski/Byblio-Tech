#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"



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