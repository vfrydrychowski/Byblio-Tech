#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"


void print_User(User user){
    printf("id = %s\n",uget_id(user));
    printf("forename = %s\n",uget_forename(user));
    printf("name = %s\n",uget_name(user));
    printf("grade = %d\n",uget_grade(user));
    printf("cryptedPw = %s\n",uget_cryptedPwd(user));

    char** tab = uget_brw(user);
    int taille = get_table_size(tab);
    printf("borrow : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("id %d = %s\n",i,tab[i]);
    }
    free_table(tab);

    tab = uget_possession(user);
    taille = get_table_size(tab);
    printf("possession : %d\n",taille);
    for (int i = 1; i<= taille;i++){
        printf("id %d = %s\n",i,tab[i]);
    }
    free_table(tab);


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