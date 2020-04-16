#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/user.h"
#include "../include/object.h"
#include "../include/SISO.h"
#define JSMN_HEADER
#include "../include/Json.h"

void print_User(User user){
    printf("User = %s\n",uget_id(user));
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

    printf("\n");

}

int main()
{
    /*char* path = user_path("007");
    suppr_json(path);
    free(path);*/
    printf("hello world\n");
    User current_user = crea_user("007","james","bond","jamesbond@gmail.com",1,"motdepasse");
    char* name = get_name("007");
    printf("id : %s\n",uget_id(current_user));
    free(name);
    printf("%s %s\n",uget_name(current_user),uget_forename(current_user));
    borrowing(current_user, "1");
    borrowing(current_user, "444444444");
    print_object("1");
    print_object("444444444");
    add_possession(current_user,"2","The name of the Wind", 549, "Patrick Rothfus", 2007,"fantasy novel");
    add_possession(current_user,"21","The Wise Man's Fear", 549, "Patrick Rothfus", 2011,"fantasy novel");
    add_possession(current_user,"22","The Music of Silence", 218, "Patrick Rothfus", 2014,"fantasy novel");
    printf("ok\n");
    set_borrower("21","j");
    set_borrower("2","j");

    printf("ok\n");

    //test des fonction borrow

    print_object("2");
    print_object("21");
    print_object("22");


    print_user("007");
    suppr_all_possession(current_user);
    //return_back_all(current_user);
    
    suppr_us(current_user);

    logout(current_user);

    current_user = charge_user("j");
    //ban("007",current_user);
    free_user(current_user);

    /*char* path = user_path("007");
    suppr_json(path);
    free(path);*/

    
    return 0;
}
