#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"

void Menu(){
    int x = 0;
    int pos = -1;
    while(pos == -1){
        cleanscr();
        printf(" ----------------------------------------------------------------------\n");
        printf("|                       Welcome to Byblio-Tech!!                       |\n");
        printf(" ----------------------------------------------------------------------\n");
        printf("|                         1 : Login                                    |\n");
        printf("|                                                                      |\n");
        printf("|                         2 : Register                                 |\n");
        printf("|                                                                      |\n");
        printf("|                         0 : Quit                                     |\n");
        printf(" ----------------------------------------------------------------------\n");
        printf(" Choice : ");
        read_int(&x);
        switch(x){
            case 1 :
                pos = -2;
                while(pos == -2){
                    cleanscr();
                    User us;
                    char* pwd = malloc(sizeof(char)*PWSIZE);//TOFREE
                    char* username= malloc(sizeof(char)*NAMESIZE);//TOFREE
                    printf(" ----------------------------------------------------------------------\n");
                    printf("|                      Please enter your infos                         |\n");
                    printf(" ----------------------------------------------------------------------\n");
                    printf("  Username : ");
                    read_string(username, NAMESIZE);
                    printf("\n  Password : ");
                    read_string(pwd, PWSIZE);
                    printf("\n");
                    switch (login(username, pwd, &us)){
                        case 0:
                            pos = -3;
                            while(pos==-3){
                                cleanscr();
                                printf(" ----------------------------------------------------------------------\n");
                                printf("|                              Welcome                                 |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                printf("|                        1 : Search a book                             |\n");
                                printf("|                                                                      |\n");
                                printf("|                        2 : return a book                             |\n");
                                printf("|                                                                      |\n");
                                printf("|                        3 : get back a book                           |\n");
                                printf("|                                                                      |\n");
                                printf("|                        4 : settings                                  |\n");
                                printf("|                                                                      |\n");
                                //only admins can see this option
                                if (uget_grade(us)>=5){
                                    printf("|          ( ☉̅ 益 ☉̅ )     5 : *Privileges*     ( ☉̅ 益 ☉̅ )               |\n");
                                    printf("|                                                                      |\n");
                                }
                                printf("|                        0 : back and logout                           |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                printf("  Choice : ");
                                x = -1;
                                read_int(&x);
                                switch(x){
                                    case 1:
                                            search(us);
                                    break;

                                    case 2:
                                        pos=-4;
                                        while(pos == -4){
                                            cleanscr();
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                  Wich one do you wish to return ?           0 : back |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                            char** brlist = uget_brw(us);//TOFREE
                                            char* title;
                                            char* author;
                                            for (int i = 1; i<= get_table_size(brlist); i++){
                                                title = get_title(brlist[i]);
                                                author = get_author(brlist[i]);
                                                printf("  %d, : %s   *   %s\n", i, title, author);
                                                free(title);
                                                free(author);
                                            }
                                            printf("  Choice : ");
                                            x = -1;
                                            read_int(&x);
                                            if(x==0){
                                                pos = -3;
                                                free_table(brlist);
                                            }
                                            else if(x < get_table_size(brlist) && x > 0){
                                                pos = -5;
                                                int curr = x; //current object
                                                while(pos == -5){
                                                    cleanscr();
                                                    printf(" ----------------------------------------------------------------------\n");
                                                    printf("|                      Is it the one to return ?                       |\n");
                                                    printf("|                 0 : no                      1 : yes                  |\n");
                                                    printf(" ----------------------------------------------------------------------\n");                    
                                                    print_object(brlist[curr]);
                                                    printf("  Choice : ");
                                                    read_int(&x);
                                                    switch(x){
                                                        case 0:
                                                            pos = -4;
                                                        break;

                                                        case 1:
                                                            //returnback
                                                            pos = -3;
                                                        break;

                                                        default:
                                                        break;
                                                    }

                                                }
                                            }
                                        }
                                        
                                    break;

                                    case 3:

                                    break;

                                    case 4:
                                        pos = -3;
                                        while(pos == -3){
                                            cleanscr();
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                              Settings                                |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                        1 : Change username                           |\n");
                                            printf("|                                                                      |\n");
                                            printf("|                        2 : Change password                           |\n");
                                            printf("|                                                                      |\n");
                                            printf("|                        3 : Close account                             |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                        }
                                        
                                    break;

                                    case 0:
                                        pos = -1;
                                    break;

                                    default:
                                    break;
                                }
                            }
                            


                        break;

                        default:
                            pos = -1;
                            //error processing
                            /* printf("                          retry?\n");
                            printf("                1 : yes                 0 : no\n");
                            printf("  : ");
                            x=0;
                            read_int(&x);
                            switch(x){
                                case 1:
                                    pos = -2;
                                    break;

                                default :
                                    pos = -1;
                                    break;
                            } */

                        break;
                    }
                }

            break;

            case 2 :

            break;
            
            case 0 :
                printf("                             Goodbye\n");
                pos = 0;
            break;

            default :
            break;


        }
    }
    



}


int main(int argc, char const *argv[])
{
    printf("rose are red\nviolets are blue\nthis main is on the edge\nof a new and wonderfull youth\n");
    Menu();
    return 0;
}
