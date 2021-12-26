#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void teacher_client();
void student_client();

int group_num;

#include "log_register.h"
#include "task_process.h"
#include "interactts.h"

void teacher_client(){
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("1-显示学生完成进度\n");
            printf("2-管理学生信息\n");
            printf("3-师生互动\n");
            printf("0-退出\n");
            printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");

            printf("\n选择功能编号:");
            if(!scanf("%d",&fuct)){
                printf("请正确输入一个编号:\n");
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
            printf("请正确输入一个编号:\n");
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
            printf("1-上传进度或文件\n");
            printf("2-向老师提问\n");
            printf("0-退出\n");
            printf("++++++++++++++++++++++++++++++++++++++++++\n");

            printf("\n请输入功能编号:");
            if(!scanf("%d",&fuct)){
                printf("请正确输入一个编号:\n");
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
            printf("请正确输入一个编号:\n");
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
    system("color 94");
    Mainland();
    system("pause");
    return 0;
}