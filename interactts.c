#ifndef INTERACTTS_H
#define INTERACTTS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define TS_FILE "teacher&student-interact.txt"
#define LEN 1000

void read_file();
void print_list();
void welcome_stu();
void add_to_list();
void submit_Q();
void destroy_list();

typedef struct{
    int id;
    char question[LEN];
    char answer[LEN];
}Q;

int questioncnt;

typedef struct Node{
    Q data;
    struct Node *nxt;
}List;

List *head;

void read_file(){
    FILE *fp;
    if(!(fp=fopen(TS_FILE,"r"))){
        printf("读取问题和回答失败!\n");
        return;
    }
    head=(List*)malloc(sizeof(List));
    List *now_pointer,*temp;
    now_pointer=head;
    Q data;
    while(true){
        fscanf(fp,"%d",&data.id);
        fscanf(fp,"%s",data.question);
        fscanf(fp,"%s",data.answer);
        if(feof(fp))
            break;
        temp=(List*)malloc(sizeof(List));
        temp->data=data;
        now_pointer->nxt=temp;
        now_pointer=temp;
        questioncnt++;
    }
    now_pointer->nxt=NULL;
    fclose(fp);
    return;
}

void add_to_list(Q data){
    FILE *fp;
    if(!(fp=fopen(TS_FILE,"a"))){
        printf("提交问题失败!\n");
        return;
    }

    List *pre=head;
    List *now_pointer=head->nxt;
    while(now_pointer)
        pre=now_pointer,now_pointer=now_pointer->nxt;
    now_pointer=(List*)malloc(sizeof(List));
    if(!now_pointer){
        printf("提交问题失败!\n");
        return;
    }
    data.id=++questioncnt;
    pre->nxt=now_pointer;
    now_pointer->data=data;
    now_pointer->nxt=NULL;

    fprintf(fp,"%d\t",data.id);
    fprintf(fp,"%s\t",data.question);
    fprintf(fp,"%s\n",data.answer);
    fclose(fp);
    return;
}

void submit_Q(){
    system("cls");
    Q temp;
    printf("请输入你的问题:");
    scanf("%s",temp.question);
    strcpy(temp.answer,"NULL");
    add_to_list(temp);
    printf("提交问题成功!\n");
    system("pause");
    return;
}

void print_list(){
    system("cls");
    printf("----------------------------------------\n");
    printf("id\tquestion\tanswer\n");
    List *now_pointer=head->nxt;
    while(now_pointer){
        Q temp=now_pointer->data;
        printf("%d\t",temp.id);
        printf("%s\t",temp.question);
        printf("%s\n",temp.answer);
        now_pointer=now_pointer->nxt;
    }
    printf("----------------------------------------\n");
    system("pause");
    return;
}

void destroy_list(){
    List *pre=head;
    List *now_pointer=head->nxt;
    while(now_pointer){
        free(pre);
        pre=now_pointer;
        now_pointer=now_pointer->nxt;
    }
    free(pre);
    return;
}

void welcome_stu(){
    read_file();
    char *fuct;
    fuct=(char*)malloc(50*sizeof(char));
    while(true){
        while(true){
            system("cls");
            printf("++++++++++++++++++++++++\n");
            printf("1-查看所有问题及回答\n");
            printf("2-提出问题\n");
            printf("0-返回上级菜单\n");
            printf("++++++++++++++++++++++++\n");

            printf("\n选择你所需的功能编号:");
            scanf("%s",fuct);
            if(fuct[0]>='0'&&fuct[0]<='2')
                break;
            printf("请正确输入类型数字:\n");
        }
        switch(fuct[0]){
            case '1': print_list();
                break;
            case '2': submit_Q();
                break;
            case '0': destroy_list(),free(fuct);
            return;
        }
    }
    return;
}

void welcome_tec();
void answer_question();
void give_answer();
bool save_file();

bool save_file(){
    FILE *fp;
    if(!(fp=fopen(TS_FILE,"w"))){
        printf("成功修改但未写入文件!\n");
        return false;
    }
    List *now_pointer=head->nxt;
    while(now_pointer){
        fprintf(fp,"%d\t",now_pointer->data.id);
        fprintf(fp,"%s\t",now_pointer->data.question);
        fprintf(fp,"%s\n",now_pointer->data.answer);
        now_pointer=now_pointer->nxt;
    }
    fclose(fp);
    return true;
}

void give_answer(int id,const char *ans){
    List *pre=head;
    List *now_pointer=head->nxt;

    while(now_pointer){
        Q temp;
        temp=now_pointer->data;
        if(temp.id==id)
            break;
        pre=now_pointer;
        now_pointer=now_pointer->nxt;
    }
    if(!now_pointer){
        printf("问题编号错误，请重新输入!\n");
        return;
    }
    strcpy(now_pointer->data.answer,ans);
    if(save_file())
    printf("成功上传回答!\n");
    return;
}

void answer_question(){
    system("cls");
    print_list();
    putchar('\n');
    printf("请输入问题编号:");
    int id;
    scanf("%d",&id);
    char ans[1000];
    printf("你的回答是:");
    scanf("%s",ans);
    give_answer(id,ans);
    system("pause");
    return;
}

void welcome_tec(){  
    read_file();
    char *fuct;
    fuct=(char*)malloc(50*sizeof(char));
    while(true){
        while(true){
            system("cls");
            print_list();
            printf("++++++++++++++++++++++++\n");
            printf("1-选择问题回答\n");
            printf("0-返回上级菜单\n");
            printf("++++++++++++++++++++++++\n");

            printf("\n选择你所需的功能编号:");
            scanf("%s",fuct);
            if(fuct[0]>='0'&&fuct[0]<='1')
                break;
            printf("请正确输入类型数字:\n");
        }
        switch(fuct[0]){
            case '1': answer_question();
                break;
            case '0': destroy_list(),free(fuct);
            return;
        }
    }
    return;
}

int main(){
    welcome_tec();
    return 0;
}

#endif