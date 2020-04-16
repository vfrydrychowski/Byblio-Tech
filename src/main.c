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
                    char* pwd = malloc(sizeof(char)*PWSIZE);
                    char* username= malloc(sizeof(char)*NAMESIZE);
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
                                printf("|                        0 : back and logout                           |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                printf("  Choice : ");
                                x = -1;
                                read_int(&x);
                                switch(x){
                                    case 1:

                                    break;

                                    case 2:

                                    break;

                                    case 3:

                                    break;

                                    case 4:

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
                            //error processing
                            printf("                          retry?\n");
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
                            }

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
