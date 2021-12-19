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
        p=fopen(USER_FILE,"w+");
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
        printf("Something wrong with the file!\n");
        return;
    }

    Ulist *pre=uhead;
    Ulist *now_pointer=uhead->next;
    while(now_pointer)
        pre=now_pointer,now_pointer=now_pointer->next;
    now_pointer=(Ulist*)malloc(sizeof(Ulist));
    if(!now_pointer){
        printf("Failed to add!\n");
        return;
    }
    pre->next=now_pointer;
    now_pointer->data=data;
    now_pointer->next=NULL;

    fprintf(fp,"%d ",data.group_id);
    fprintf(fp,"%s ",data.id);
    fprintf(fp,"%s\n",data.pwd);
    fclose(fp);
    printf("Add successfully!\n");
    system("pause");
    return;
}

void regis(){
    user new_user;
    printf("Please key your accout:");
    scanf("%s",new_user.id);
    while(search_id(new_user.id)){
        printf("The account has already existed!\n");
        printf("Please put another account:");
        scanf("%s",new_user.id);
    }
    printf("Please key your password:");
    hide_pwd(new_user.pwd);
    putchar('\n');
    printf("Your group_id is:");
    while(!scanf("%d",&new_user.group_id)){
        printf("Please put in a correct number!\n");
        char s[10000];
        gets(s);
        system("pause");
    }
    char ch=getchar();
    while(ch!='\n')
        ch=getchar();
    add_user_to_list(new_user);
    return;
}

bool check_pwd(char*,char*);

bool check_pwd(char *id,char *pwd){
    Ulist *now_pointer=uhead->next;
    while(now_pointer){
        if(!strcmp(now_pointer->data.id,id))
            if(!strcmp(now_pointer->data.pwd,pwd))
                return true;
        now_pointer=now_pointer->next;
    }
    return false;
}

void login(){
    user new_user;
    printf("Please key your accout:");
    scanf("%s",new_user.id);
    printf("Please key your password:");
    hide_pwd(new_user.pwd);
    putchar('\n');
    if(check_pwd(new_user.id,new_user.pwd)){
        if(!strcmp(new_user.id,"teacher"))
            teacher_client();
        else
            student_client();
    }
    else{
        printf("The account or password not right!\n");
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
    printf("group_id\tid\tpassword\n");
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
    printf("Whether you want to delete a student or not?(y for yes):");
    char s[10];
    scanf("%s",s);
    if(s[0]=='y'){
        printf("The student id you want to delete:");
        char id[10000];
        scanf("%s",id);
        if(delete_usr(id)){
            usave_file();
            printf("Delete successfully!\n");
            system("pause");
        }
        else{
            printf("Failed to delete!\n");
            system("pause");
        }
    }
    printf("The system will back to last menu!\n");
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
            printf("1-log\n");
            printf("2-register\n");
            printf("0-exit\n");
            printf("++++++++++++++++++++++++\n");

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
            case 1: login(),destroy_usr();
                break;
            case 2: regis(),destroy_usr();
                break;
            case 0: exit(EXIT_SUCCESS);
        }
    }
    return;
}

#endif