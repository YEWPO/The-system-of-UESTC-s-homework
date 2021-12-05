#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define process_file "prcfile.txt"
#define user_file "usr.txt"
#define tc_stu_file "tsfile.txt"
#define stu_stu_file "ssfile.txt"

typedef struct{
    int member_id;
    char *member_name;
}Member;

typedef struct{
    int group_id;
    Member *head;
    int total;
}Group;

typedef struct{
    int question_id;
    char *question;
    char *ans;
}TSqus;

typedef struct{
    double process;
    FILE *file;
}Program;

void clearscreen(){
    system("cls");
    return;
}

void teacher_client(){
    //password function written by wujun;
    clearscreen();
    do{
        printf("\n++++++++++++++++++++++++\n");
        printf("1-�鿴ѧ����Ŀ��ɽ���\n");
        printf("2-����ѧ����Ϣ\n");
        printf("3-ѧ������\n");
        printf("0-�˳�ϵͳ\n");
        printf("++++++++++++++++++++++++\n\n");
        char *funcnum;
        funcnum=(char *)malloc(100*sizeof(char));
        printf("�����빦����� > ");
        do{
            scanf("%s",funcnum);
            if(funcnum[0]>='0'&&funcnum[0]<='3')
                break; 
            printf("����ȷ���빦�����ͣ�\n");
            printf("�����빦����� > ");
        }while(true);
        switch(funcnum[0]){
            case '1': ;//function written by hexuanyu;
                break;
            case '2': ;//function written by ganlinjun;
                break;
            case '3': ;//function written by yeqirui;
                break;
            case '0':return;
        }
    }while(true);
    return;
}

void student_client(){
    //student password function written by wujun;
    clearscreen();
    typedef struct{
        int question_id;
        char *question;
        char *ans;
    }SSqus;

    do{
        printf("\n+++++++++++++++++++\n");
        printf("1-�ϴ��ļ��ͽ���\n");
        printf("2-��������&�ش�\n");
        printf("3-����ʦ����\n");
        printf("0-�˳�ϵͳ\n");
        printf("+++++++++++++++++++\n\n");
        char *funcnum;
        funcnum=(char *)malloc(100*sizeof(char));
        printf("�����빦����� > ");
        do{
            scanf("%s",funcnum);
            if(funcnum[0]>='0'&&funcnum[0]<='3')
                break;
            printf("����ȷ���빦�����ͣ�\n");
            printf("�����빦����� > ");
        }while(true);
        switch(funcnum[0]){
            case '1': ;//function written by wushuting;
                break;
            case '2': ;//function written by wangzirui;
                break;
            case '3': ;//function written by huangxin;
                break;
            case '0':return;
        }
    }while(true);
    return;
}

void who_is(){
    char *whousr;
    whousr=(char *)malloc(100*sizeof(char));
    printf("ѡ���û����ͣ� 1 - ��ʦ 2 - ѧ�� 0 - �˳� ��> ");
    do{
        scanf("%s",whousr);
        if(whousr[0]>='0'&&whousr[0]<='2')
            break;
        printf("����ȷ�����û����ͣ�\n");
        printf("\nѡ���û����ͣ� 1 - ��ʦ 2 - ѧ�� 0 - �˳� ��> ");
    }while(true);
    switch(whousr[0]){
        case '1':teacher_client();
            break;
        case '2':student_client();
            break;
        case '0':return;
    }
    return;
}

int main(){
    who_is();
    system("pause");
    return 0;
}