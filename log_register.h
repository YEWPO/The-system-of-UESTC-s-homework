#ifndef LOG_REGISTER_H
#define LOG_REGISTER_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>

int wherex();
int wherey();
void gotoxy(int,int);
void hide_pwd(char*);
//获取光标的位置x
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.X+1);
}
//获取光标的位置y
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return (pBuffer.dwCursorPosition.Y+1);
}
//设置光标的位置
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x-1;
    c.Y=y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void hide_pwd(char* s){
    int i=-1,x,y;
	do{
		i++;
		s[i]=getch();
		while(s[i]==8&&i>=0){
		    i--;
		    if(i>=0){
                x=wherex();
                y=wherey();
                gotoxy(x-1,y);
                printf(" ");
                x=wherex();
                y=wherey();
                gotoxy(x-1,y);
		    }
		    s[i]=getch();
		}
		if(i>=0&&s[i]!=13&&s[i]!=8){
		    x=wherex();
	        y=wherey();
		    gotoxy(x,y);
		    printf("*");
		}
	}while(s[i]!=13);
	s[i]='\0';
    return;
}

#define USER_FILE "users.txt"

void uread_file();
void regis();
void login();
void Mainland();

typedef struct{
    char id[10000];
    int group_id;
    char pwd[10000];
}user;

typedef struct vp{
    user data;
    struct vp *next;
}Ulist;

Ulist *uhead;

void uread_file(){
    FILE *p;
    if(!(p=fopen(USER_FILE,"r")))
        p=fopen(USER_FILE,"w"),fprintf(p,"0 teacher 123\n"),fclose(p);
    p=fopen(USER_FILE,"r");
    uhead=(Ulist*)malloc(sizeof(Ulist));
    Ulist *now_pointer,*temp;
    now_pointer=uhead;
    user data;
    while(true){
        fscanf(p,"%d",&data.group_id);
        fscanf(p,"%s",data.id);
        fscanf(p,"%s",data.pwd);
        if(feof(p))
            break;
        temp=(Ulist*)malloc(sizeof(Ulist));
        temp->data=data;
        now_pointer->next=temp;
        now_pointer=temp;
    }
    now_pointer->next=NULL;
    fclose(p);
    return;
}

#include<string.h>

bool search_id(const char *id){
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        if(!strcmp(now_pointer->data.id,id))
            return true;
        now_pointer=now_pointer->next;
    }
    return false;
}

void add_user_to_list(user data){
    FILE *fp;
    if(!(fp=fopen(USER_FILE,"a"))){
        printf("文件读取错误!\n");
        return;
    }

    Ulist *pre=uhead;
    Ulist *now_pointer=uhead->next;
    while(now_pointer)
        pre=now_pointer,now_pointer=now_pointer->next;
    now_pointer=(Ulist*)malloc(sizeof(Ulist));
    if(!now_pointer){
        printf("注册失败!\n");
        return;
    }
    pre->next=now_pointer;
    now_pointer->data=data;
    now_pointer->next=NULL;

    fprintf(fp,"%d ",data.group_id);
    fprintf(fp,"%s ",data.id);
    fprintf(fp,"%s\n",data.pwd);
    fclose(fp);
    printf("注册成功!\n");
    system("pause");
    return;
}

void regis(){
    user new_user;
    printf("请输入你要创建的用户名:");
    scanf("%s",new_user.id);
    while(search_id(new_user.id)){
        printf("用户名已存在!\n");
        printf("请再输入你要创建的用户名:");
        scanf("%s",new_user.id);
    }
    printf("请输入密码:");
    char pwwd[10000];
    hide_pwd(pwwd);
    putchar('\n');
    printf("请再次确认你的密码:");
    hide_pwd(new_user.pwd);
    putchar('\n');
    printf("你的小组编号是:");
    while(!scanf("%d",&new_user.group_id)){
        printf("请输入一个正确的数字!\n");
        char s[10000];
        gets(s);
        system("pause");
    }
    char ch=getchar();
    while(ch!='\n')
        ch=getchar();
    if(!strcmp(pwwd,new_user.pwd))
        add_user_to_list(new_user);
    else{
        printf("两次密码不同，注册失败!\n");
        system("pause");
        regis();
    }
    return;
}

bool check_pwd(const char*,const char*);

bool check_pwd(const char *id,const char *pwd){
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        if(!strcmp(now_pointer->data.id,id))
            if(!strcmp(now_pointer->data.pwd,pwd)){
                group_num=now_pointer->data.group_id;
                return true;
            }
        now_pointer=now_pointer->next;
    }
    return false;
}

void login(){
    user new_user;
    printf("请输入用户名:");
    scanf("%s",new_user.id);
    printf("请输入密码:");
    hide_pwd(new_user.pwd);
    putchar('\n');
    if(check_pwd(new_user.id,new_user.pwd)){
        if(!strcmp(new_user.id,"teacher"))
            teacher_client();
        else
            student_client();
    }
    else{
        printf("账户或密码错误!\n");
        system("pause");
    }
    return;
}

void welcome_tecmanager();
void print_usr();
void destroy_usr();
void usave_file();

void usave_file(){
    FILE *fp;
    fp=fopen(USER_FILE,"w");
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        user date=now_pointer->data;
        fprintf(fp,"%d\t",date.group_id);
        fprintf(fp,"%s\t",date.id);
        fprintf(fp,"%s\n",date.pwd);
        now_pointer=now_pointer->next;
    }
    fclose(fp);
    return;
}

void print_usr(){
    system("cls");
    printf("----------------------------------------\n");
    printf("小组编号\t用户名\t密码\n");
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        user temp=now_pointer->data;
        printf("%d\t",temp.group_id);
        printf("%s\t",temp.id);
        printf("%s\n",temp.pwd);
        now_pointer=now_pointer->next;
    }
    printf("----------------------------------------\n");
    system("pause");
    return;
}

void destroy_usr(){
    Ulist *pre=uhead;
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        free(pre);
        pre=now_pointer;
        now_pointer=now_pointer->next;
    }
    free(pre);
    return;
}

bool delete_usr(char*);

bool delete_usr(char *id){
    Ulist *pre=uhead,*p=uhead->next;
    while(p!=NULL){
        char *s=p->data.id;
        if(!strcmp(s,id))
        break;
        pre=p;
        p=p->next;
    }
    if(p==NULL)
    return false;
    pre->next=p->next;
    free(p);
    return true;
}

void welcome_tecmanager(){
    uread_file();
    print_usr();
    printf("是否进行删除学生操作?(y for yes):");
    char s[10];
    scanf("%s",s);
    if(s[0]=='y'){
        printf("要删除的学生的账户名:");
        char id[10000];
        scanf("%s",id);
        if(delete_usr(id)){
            usave_file();
            printf("删除成功!\n");
            system("pause");
        }
        else{
            printf("删除失败!\n");
            system("pause");
        }
    }
    printf("即将返回上级目录!\n");
    system("pause");
    return;
}

void Mainland(){
    uread_file();
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("++++++++++++++++++++++++\n");
            printf("1-登录\n");
            printf("2-注册\n");
            printf("0-退出\n");
            printf("++++++++++++++++++++++++\n");

            printf("\n选择功能编号:");
            if(!scanf("%d",&fuct)){
                printf("请正确输入一个功能编号:\n");
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
            printf("请正确输入一个功能编号:\n");
            system("pause");
        }
        switch(fuct){
            case 1: login();
                break;
            case 2: regis();
                break;
            case 0: exit(EXIT_SUCCESS),destroy_usr();
        }
    }
    return;
}

#endif