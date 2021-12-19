#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void teacher_client();
void student_client();

#include "log_register.h"
#include "task_process.h"
#include "interactts.h"

void teacher_client(){
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("1-Display the students' process\n");
            printf("2-Manage the students' information\n");
            printf("3-Students' questions\n");
            printf("0-exit\n");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");

            printf("\nChoose your number that you want to do:");
            if(!scanf("%d",&fuct)){
                printf("Please put in a correct number:\n");
                char s[10000];
                gets(s);
                system("pause");
                continue;
            }
            if(fuct>=0&&fuct<=3){
                char ch;
                ch=getchar();
                while(ch!='\n')
                    ch=getchar();
                break;
            }   
            printf("Please put int a correct number:\n");
            system("pause");
        }
        switch(fuct){
            case 1: welcome_tec_task();
                break;
            case 2: welcome_tecmanager();
                break;
            case 3: welcome_tec_tsact();
                break;
            case 0: exit(EXIT_SUCCESS);
        }
    }
    return;
}

void student_client(){
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("++++++++++++++++++++++++++++++++++++++++++\n");
            printf("1-Submit your process or files\n");
            printf("2-Ask teacher questions\n");
            printf("0-exit\n");
            printf("++++++++++++++++++++++++++++++++++++++++++\n");

            printf("\nChoose your number that you want to do:");
            if(!scanf("%d",&fuct)){
                printf("Please put in a correct number:\n");
                char s[10000];
                gets(s);
                system("pause");
                continue;
            }
            if(fuct>=0&&fuct<=2){
                char ch;
                ch=getchar();
                while(ch!='\n')
                    ch=getchar();
                break;
            }   
            printf("Please put int a correct number:\n");
            system("pause");
        }
        switch(fuct){
            case 1: welcome_stu_task();
                break;
            case 2: welcome_stu_tsact();
                break;
            case 0: exit(EXIT_SUCCESS);
        }
    }
    return;
}

int main(){
    system("color B5");
    Mainland();
    system("pause");
    return 0;
}