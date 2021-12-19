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
void welcome_stu_tsact();
void welcome_tec_tsact();
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
        printf("Failed to read the file! The system will create a new one!\n");
        fp=fopen(TS_FILE,"w+");
        system("pause");
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
        printf("Failed to submit question!\n");
        return;
    }

    List *pre=head;
    List *now_pointer=head->nxt;
    while(now_pointer)
        pre=now_pointer,now_pointer=now_pointer->nxt;
    now_pointer=(List*)malloc(sizeof(List));
    if(!now_pointer){
        printf("Failed to submit question!\n");
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
    printf("Please put your question:");
    scanf("%s",temp.question);
    strcpy(temp.answer,"NULL");
    add_to_list(temp);
    printf("Submit question successfully!\n");
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

void welcome_stu_tsact(){
    read_file();
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("**********************************************\n");
            printf("1-Show the questions and answers\n");
            printf("2-Show your question to the teacher\n");
            printf("0-Back to the last menu\n");
            printf("**********************************************\n");

            printf("\nChoose your function number:");
            if(!scanf("%d",&fuct)){
                printf("Please put in a interger number correctly!\n");
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
            printf("Please put in a interger number correctly!\n");
            system("pause");
        }
        switch(fuct){
            case 1: print_list();
                break;
            case 2: submit_Q();
                break;
            case 0: destroy_list();
            return;
        }
    }
    return;
}

void answer_question();
void give_answer();
bool save_file();

bool save_file(){
    FILE *fp;
    if(!(fp=fopen(TS_FILE,"w"))){
        printf("Successfully update but not put in a file!\n");
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
        printf("Wrong question id\n");
        return;
    }
    strcpy(now_pointer->data.answer,ans);
    if(save_file())
    printf("Submit successfully!\n");
    return;
}

void answer_question(){
    system("cls");
    print_list();
    putchar('\n');
    printf("Please put in the id of the question that you want to answer:");
    int id;
    while(!scanf("%d",&id)){
        printf("Wrong id number!\n");
        char s[10000];
        gets(s);
        system("pause");
    }
    char ch;
    ch=getchar();
    while(ch!='\n')
        ch=getchar();
    char ans[1000];
    printf("Your answer is:");
    scanf("%s",ans);
    give_answer(id,ans);
    system("pause");
    return;
}

void welcome_tec_tsact(){  
    read_file();
    int fuct;
    while(true){
        while(true){
            system("cls");
            print_list();
            printf("********************************************\n");
            printf("1-Choose a question to anwser\n");
            printf("0-Back to last menu\n");
            printf("********************************************\n");

            printf("\nChoose the function number:");
            if(!scanf("%d",&fuct)){
                printf("Correcrt number needed!\n");
                char s[10000];
                gets(s);
                system("pause");
                continue;
            }
            if(fuct>=0&&fuct<=1){
                char ch;
                ch=getchar();
                while(ch!='\n')
                    ch=getchar();
                break;
            }
            printf("Correct number needed!\n");
            system("pause");
        }
        switch(fuct){
            case 1: answer_question();
                break;
            case 0: destroy_list();
            return;
        }
    }
    return;
}

#endif