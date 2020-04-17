#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "../include/Json.h"
#include "../include/object.h"
#include "../include/search.h"
#include "../include/SISO.h"
#include "../include/user.h"

int retry(int pos){
    printf("                          retry?\n");
    printf("                1 : yes                 0 : no\n");
    printf("  :  ");
    int x=0;
    read_int(&x);
    switch(x){
        case 1:
            return pos;
        break;

        default :
            return pos+1;
        break;
    } 
}

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
            case 1 ://login
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
                    switch (login(&us, username, pwd)){
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
                                printf("|                        5 : Lend us a book                            |\n");
                                printf("|                                                                      |\n");
                                //only admins can see this option
                                if (uget_grade(us)>=5){
                                    printf("|        ( ☉̅ 益 ☉̅ )     666 : *Privileges*     ( ☉̅ 益 ☉̅ )               |\n");
                                    printf("|                                                                      |\n");
                                }
                                printf("|                        0 : back and logout                           |\n");
                                printf(" ----------------------------------------------------------------------\n");
                                printf("  Choice : ");
                                x = -1;
                                read_int(&x);
                                char* title;
                                char* author;
                                switch(x){
                                    case 1://search a book
                                            search(us);
                                    break;

                                    case 2://return a book
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
                                                            return_back(brlist[curr], us);
                                                            pos = -3;
                                                        break;

                                                        default:
                                                        break;
                                                    }

                                                }
                                            }
                                        }
                                        
                                    break;

                                    case 3://get back a book
                                        cleanscr();
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                  Wich one do you wish to get back ?         0 : back |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                            char** poss = uget_brw(us);//TOFREE
                                            
                                            for (int i = 1; i<= get_table_size(poss); i++){
                                                title = get_title(poss[i]);
                                                author = get_author(poss[i]);
                                                printf("  %d, : %s   *   %s\n", i, title, author);
                                                free(title);
                                                free(author);
                                            }
                                            printf("  Choice : ");
                                            x = -1;
                                            read_int(&x);
                                            if(x==0){
                                                pos = -3;
                                            }
                                            else if(x < get_table_size(poss) && x > 0){
                                                pos = -5;
                                                int curr = x; //current object
                                                while(pos == -5){
                                                    cleanscr();
                                                    printf(" ----------------------------------------------------------------------\n");
                                                    printf("|                      Is it the one to ge back ?                      |\n");
                                                    printf("|                 0 : no                      1 : yes                  |\n");
                                                    printf(" ----------------------------------------------------------------------\n");                    
                                                    print_object(poss[curr]);
                                                    printf("  Choice : ");
                                                    read_int(&x);
                                                    switch(x){
                                                        case 0:
                                                            pos = -4;
                                                        break;

                                                        case 1:
                                                            switch(suppr_possession(poss[curr], us)){
                                                                case 1:
                                                                    printf(" ----------------------------------------------------------------------\n");
                                                                    printf("|                  this books is  currently borrowed                   |\n");
                                                
                                                                break;

                                                                case 0:
                                                                    printf(" ----------------------------------------------------------------------\n");
                                                                    printf("|                         Et voila, thanks !                           |\n");
                                                                break;

                                                                default:
                                                                break;
                                                            }
                                                            printf("|                              Press any key                           |\n");
                                                            printf(" ----------------------------------------------------------------------\n");
                                                            cleanbuff();
                                                            pos = -2;
                                                        break;

                                                        default:
                                                        break;
                                                    }

                                                }
                                            }
                                            free_table(poss);
                                        
                                    break;

                                    case 4://Settings
                                        pos = -4;
                                        while(pos == -4){
                                            cleanscr();
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                              Settings                                |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("|                        1 : Change username                           |\n");
                                            printf("|                                                                      |\n");
                                            printf("|                        2 : Change password                           |\n");
                                            printf("|                                                                      |\n");
                                            printf("|                        3 : Close account                             |\n");
                                            printf("|                                                                      |\n");
                                            printf("|                        0 : Back                                      |\n");
                                            printf(" ----------------------------------------------------------------------\n");
                                            printf("Choice : ");
                                            x=-1;
                                            read_int(&x);
                                            switch(x){
                                                case 1://change username
                                                    pos = -5;
                                                    while(pos == -5){
                                                        cleanscr();
                                                        char* username = malloc(sizeof(char)*IDSIZE);//TOFREE
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("       Your current username is : %s\n", uget_id(us));
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("  New user name : ");
                                                        read_string(username, IDSIZE);
                                                        switch(new_username(us, username)){
                                                            

                                                            
                                                            case 0:
                                                                pos=-4;
                                                            break;

                                                            case 1:
                                                                printf(" ----------------------------------------------------------------------\n");
                                                                printf("|                   Sorry this username is taken      press any : back |\n");
                                                                printf(" ----------------------------------------------------------------------\n");
                                                                pos = retry(pos);
                                                            break;
                                                        }
                                                        free(username);
                                                    }
                                                break;

                                                case 2://change password
                                                    pos = -5;
                                                    while(pos == -5){
                                                        cleanscr();
                                                        char* pwd = malloc(sizeof(char)*PWSIZE);//TOFREE
                                                        char* oldpwd = malloc(sizeof(char)*PWSIZE);//TOFREE
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("|                           Changing password                          |\n");
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("  Current password : ");
                                                        read_string(oldpwd, IDSIZE);
                                                        printf("  Current password : ");
                                                        read_string(pwd, IDSIZE);

                                                        switch(new_pwd(us, oldpwd, pwd)){
                                                            case 0 :
                                                                pos =-4;
                                                            break;

                                                            case 1:
                                                                printf("                      ----------------\n");
                                                                printf("                     | Wrong password |\n");
                                                                printf("                      ----------------\n");
                                                                pos = retry(pos);
                                                            break;
                                                        }


                                                    }
                                                    
                                                    

                                                    
                                                break;

                                                case 3:
                                                    pos = -4 ;
                                                    while(pos == -4){
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("|                          Are you sure ?                              |\n");
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("|⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿                                        |\n");
                                                        printf("|⣿⣿⣿⣿⣿⣿⣿⠛⢩⣴⣶⣶⣶⣌⠙⠫⠛⢋⣭⣤⣤⣤⣤⡙⣿⣿⣿⣿⣿⣿   Think wisely and consider            |\n");
                                                        printf("|⣿⣿⣿⣿⣿⡟⢡⣾⣿⠿⣛⣛⣛⣛⣛⡳⠆⢻⣿⣿⣿⠿⠿⠷⡌⠻⣿⣿⣿⣿   staying with us                      |\n");
                                                        printf("|⣿⣿⣿⣿⠏⣰⣿⣿⣴⣿⣿⣿⡿⠟⠛⠛⠒⠄⢶⣶⣶⣾⡿⠶⠒⠲⠌⢻⣿⣿                                        |\n");
                                                        printf("|⣿⣿⠏⣡⢨⣝⡻⠿⣿⢛⣩⡵⠞⡫⠭⠭⣭⠭⠤⠈⠭⠒⣒⠩⠭⠭⣍⠒⠈⠛                                        |\n");
                                                        printf("|⡿⢁⣾⣿⣸⣿⣿⣷⣬⡉⠁⠄⠁⠄⠄⠄⠄⠄⠄⠄⣶⠄⠄⠄⠄⠄⠄⠄⠄⢀                                        |\n");
                                                        printf("|⢡⣾⣿⣿⣿⣿⣿⣿⣿⣧⡀⠄⠄⠄⠄⠄⠄⠄⢀⣠⣿⣦⣤⣀⣀⣀⣀⠄⣤⣾     1 : Yes        0 : No              |\n");
                                                        printf("|⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⡶⢇⣰⣿⣿⣟⠿⠿⠿⠿⠟⠁⣾⣿⣿                                        |\n");
                                                        printf("|⣿⣿⣿⣿⣿⣿⣿⡟⢛⡛⠿⠿⣿⣧⣶⣶⣿⣿⣿⣿⣿⣷⣼⣿⣿⣿⣧⠸⣿⣿                                        |\n");
                                                        printf("|⠘⢿⣿⣿⣿⣿⣿⡇⢿⡿⠿⠦⣤⣈⣙⡛⠿⠿⠿⣿⣿⣿⣿⠿⠿⠟⠛⡀⢻⣿                                        |\n");
                                                        printf("|⠄⠄⠉⠻⢿⣿⣿⣷⣬⣙⠳⠶⢶⣤⣍⣙⡛⠓⠒⠶⠶⠶⠶⠖⢒⣛⣛⠁⣾⣿                                        |\n");
                                                        printf("|⠄⠄⠄⠄⠄⠈⠛⠛⠿⠿⣿⣷⣤⣤⣈⣉⣛⣛⣛⡛⠛⠛⠿⠿⠿⠟⢋⣼⣿⣿                                        |\n");
                                                        printf("|⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠉⣻⣿⣿⣿⣿⡿⠿⠛⠃⠄⠙⠛⠿⢿⣿                                        |\n");
                                                        printf("|⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢬⣭⣭⡶⠖⣢⣦⣀⠄⠄⠄⠄⢀⣤⣾⣿                                        |\n");
                                                        printf("|⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢰⣶⣶⣶⣾⣿⣿⣿⣿⣷⡄⠄⢠⣾⣿⣿⣿                                        |\n");
                                                        printf(" ----------------------------------------------------------------------\n");
                                                        printf("  Choice : ");

                                                        x=-1;
                                                        read_int(&x);
                                                        switch(x){
                                                            case 1:
                                                                switch(suppr_us(us)){
                                                                    case 1:
                                                                        printf(" ----------------------------------------------------------------------\n");
                                                                        printf("|             Some of your belongings are currently borrowed           |\n");
                                                                        printf("|            please get them back before deleting your account         |\n");
                                                                    break;

                                                                    case 0:
                                                                        printf(" ----------------------------------------------------------------------\n");
                                                                        printf("|            Farewell my friends, may your future be bright            |\n");
                                                                    break;

                                                                    default:
                                                                    break;
                                                                }
                                                                    printf("|                              Press any key                           |\n");
                                                                    printf(" ----------------------------------------------------------------------\n");
                                                                pos = -1;
                                                                cleanbuff();
                                                            break;

                                                            case 0:
                                                                pos = -3;
                                                            break;

                                                            default:
                                                            break;

                                                        }
                                                    }
                                                    
                                                    

                                                break;

                                                

                                                case 0://back
                                                    pos = -3;
                                                break;

                                                default:
                                                break;
                                            }
                                        }
                                        
                                    break;

                                    case 5://lend us a book
                                        cleanscr();
                                        title = malloc(sizeof(char*)*NAMESIZE);//TOFREE
                                        author = malloc(sizeof(char*)*NAMESIZE);//TOFREE
                                        char* kind = malloc(sizeof(char*)*NAMESIZE);//TOFREE
                                        int nbpage;
                                        int date;
                                        printf(" ----------------------------------------------------------------------\n");
                                        printf("|                      Please enter the book's infos                   |\n");
                                        printf(" ----------------------------------------------------------------------\n");
                                        printf(" Title : ");
                                        read_string(title, NAMESIZE);
                                        printf(" Author : ");
                                        read_string(author, NAMESIZE);
                                        printf(" Kind : ");
                                        read_string(kind, NAMESIZE);
                                        printf(" Date : ");
                                        read_int(&date);
                                        printf(" Number of pages : ");
                                        read_int(&nbpage);
                                        add_possession(us, title, nbpage, author, date, kind);
                                        printf(" ----------------------------------------------------------------------\n");
                                        printf("|                      Sucess, thank you :)           Press any : back |\n");
                                        printf(" ----------------------------------------------------------------------\n");
                                        cleanbuff();
                                        pos = -2;

                                    break;

                                    case 666://Privilege

                                    break;


                                    case 0://Back
                                        pos = -1;
                                    break;

                                    default:
                                    break;
                                }
                            }
                            


                        break;
                        //error processing
                        case 1:
                            printf("                      --------------\n");
                            printf("                     | No such user |\n");
                            printf("                      --------------\n");
                            pos = retry(pos);
                        break;

                        case 2:
                            printf("                      ----------------\n");
                            printf("                     | Wrong password |\n");
                            printf("                      ----------------\n");
                            pos = retry(pos);
                        default:
                            pos = -1;
                        break;
                    }
                    free(username);
                    free(pwd);
                }

            break;

            case 2 ://register
                cleanscr();
                User u;
                char* username = malloc(sizeof(char)*IDSIZE);
                char* forename = malloc(sizeof(char)*NAMESIZE);
                char* name = malloc(sizeof(char)*NAMESIZE);
                char* mail = malloc(sizeof(char)*NAMESIZE);
                int grade = 0;
                char* pwd = malloc(sizeof(char)*PWSIZE);
                printf(" ----------------------------------------------------------------------\n");
                printf("|                      Please enter your infos                         |\n");
                printf(" ----------------------------------------------------------------------\n");
                printf(" Username : ");
                read_string(username, IDSIZE);
                printf(" Forename : ");
                read_string(forename, NAMESIZE);
                printf(" Name : ");
                read_string(name, NAMESIZE);
                printf(" Mail : ");
                read_string(mail, NAMESIZE);
                printf(" Password : ");
                read_string(name, NAMESIZE);
                cleanscr();
                switch(crea_user(&u, username, forename, name, mail, grade, pwd)){
                    case 1 ://Blacklisted
                        printf(" ----------------------------------------------------------------------\n");
                        printf("|                      Sorry your are blaklisted      press any : back |\n");
                        printf(" ----------------------------------------------------------------------\n");
                    break;

                    case 2://mail taken
                        printf(" ----------------------------------------------------------------------\n");
                        printf("|                   Sorry your mail is taken          press any : back |\n");
                        printf(" ----------------------------------------------------------------------\n");
                    break;

                    case 3://id taken
                        printf(" ----------------------------------------------------------------------\n");
                        printf("|                   Sorry your username is taken      press any : back |\n");
                        printf(" ----------------------------------------------------------------------\n");
                    break;
                    
                    case 0://sucessfull
                            printf(" ----------------------------------------------------------------------\n");
                            printf("|                      Gongratulation !               press any : back |\n");
                            printf("|                 Account sucessfully created                          |\n");
                            printf(" ----------------------------------------------------------------------\n");
                    break;

                    default:
                    break; 
                }
                free(username);
                free(name);
                free(pwd);
                free(mail);
                free(forename);
                cleanbuff();
                pos = -1;
            break;
            
            case 0 ://quit prgrm
                printf("                             Goodbye\n");
                pos = 0;
            break;

            default :
            break;


        }
    }
    



}



int main()
{
    printf("rose are red\nviolets are blue\nthis main is on the edge\nof a new and wonderfull youth\n");
    Menu();

    //User us;
    //printf("%d", login(&us, "Fryghost", "adminsdf"));
    //crea_user(&us,"Fryghost", "Valentin", "Frydrychowski", "frydrychowskiv@gmail.com", 10, "admin123");
    return 0;
}