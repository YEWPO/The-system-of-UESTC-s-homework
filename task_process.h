#ifndef TASK_PROCESS_H
#define TASK_PROCESS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>

#define rg register
#define MAXN 150

#define process_file "processfile.txt"

void tread_file();
int search_pps_num(int);
void push_file();
void push_process();
void tsave_file();
void welcome_stu_task();
void welcome_tec_task();

typedef struct{
    int group_id;
    double process;
}program_process;

int pps_cnt;
program_process pps[MAXN];

void tread_file(){
    FILE *fp;
    if(!(fp=fopen(process_file,"r"))){
        printf("Can't get the process file, the system will create a new one!\n");
        fp=fopen(process_file,"w+");
        system("pause");
    }
    while(true){
        fscanf(fp,"%d",&pps[++pps_cnt].group_id);
        fscanf(fp,"%lf",&pps[pps_cnt].process);
        if(feof(fp))
            break;
    }
    fclose(fp);
    return;
}

int search_pps_num(int group_id){
    for(rg int i=1;i<=pps_cnt;++i)
        if(pps[i].group_id==group_id)
            return i;
    printf("Something error in your group id!\n");
    return 0;
}

void push_file(){
    system("cls");
    printf("Your group program's name:");
    char *program_name;
    program_name=(char*)malloc(1000*sizeof(char));
    scanf("%s",program_name);
    int T;
    printf("Put the amount of files that you want to submit:");
    while(!scanf("%d",&T)){
        printf("Please put in a correct number!\n");
        char s[10000];
        gets(s);
        system("pause");
    }
    char ch=getchar();
    while(ch!='\n')
        ch=getchar();
    int cnt=0;
    while(cnt<T){
        printf("Please put in the address of the %dth file:",cnt+1);
        char *address;
        address=(char*)malloc(1000*sizeof(char));
        scanf("%s",address);
        char *file_name;
        file_name=(char*)malloc(1000*sizeof(char));
        printf("Please put in your file's name:");
        scanf("%s",file_name);
        strcat(address,"\\");
        strcat(address,file_name);
        FILE *fp1;
        if(!(fp1=fopen(address,"r"))){
            printf("Please put in correct address or file's name!\n");
            continue;
        }
        char *write_file_name;
        write_file_name=(char*)malloc(1000*sizeof(char));
        strcpy(write_file_name,program_name);
        strcat(write_file_name,"-");
        strcat(write_file_name,file_name);
        FILE *fp2;
        if(!(fp2=fopen(write_file_name,"w"))){
            printf("Failed to submit your file! Please try again!(Ctrl+C to exit)\n");
            continue;
        }
        while(!feof(fp1)){
            char s[1000];
            fgets(s,1000,fp1);
            fputs(s,fp2);
        }
        cnt++;
        fclose(fp1);
        fclose(fp2);
        free(address);
        free(file_name);
        free(write_file_name);
    }
    free(program_name);
    printf("Submit successfully!\n");
    system("pause");
    return;
}

void push_process(){
    system("cls");
    printf("Your group number is:");
    int group_num,pps_num=0;
    while(true){
        while(!scanf("%d",&group_num)){
            printf("Please put in a correct number!\n");
            char s[10000];
            gets(s);
            system("pause");
        }
        char ch=getchar();
        while(ch!='\n')
            ch=getchar();
        pps_num=search_pps_num(group_num);
        if(pps_num)
            break;
    }
    
    double process;
    while(true){
        printf("Your group's process(a double number range from 0 - 1):");
        scanf("%lf",&process);
        if(0.0<=process&&process<=1.0)
            break;
        printf("Please put your process correctly!\n");
    }
    pps[pps_num].process=process;
    printf("Submit successfully!\n");
    system("pause");
    return;
}

void tsave_file(){
    FILE *fp;
    fp=fopen(process_file,"w");
    for(rg int i=1;i<=pps_cnt;++i){
        fprintf(fp,"%d\t",pps[i].group_id);
        fprintf(fp,"%.2lf\n",pps[i].process);
    }
    fclose(fp);
    return;
}

void welcome_stu_task(){
    tread_file();
    int fuct;
    while(true){
        while(true){
            system("cls");
            printf("---------------------------------\n");
            printf("1-Submit your process\n");
            printf("2-Submit your files\n");
            printf("0-Back to the last menu\n");
            printf("---------------------------------\n");

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
            case 1: push_process(),tsave_file();
                break;
            case 2: push_file();
                break;
            case 0: return;
        }
    }
    return;
}

void quick_sort_id(int l,int r){
    int i=l,j=r;
    int mid=pps[(l+r)>>1].group_id;
    do{
        while(pps[i].group_id<mid)
            i++;
        while(pps[j].group_id>mid)
            j--;
        if(i<=j)
        {
            program_process temp;
            temp=pps[i];
            pps[i]=pps[j];
            pps[j]=temp;
            i++,j--;
        }
    }while(i<=j);
    if(l<j)
        quick_sort_id(l,j);
    if(i<r)
        quick_sort_id(i,r);
    return;
}

void quick_sort_process(int l,int r){
    int i=l,j=r;
    double mid=pps[(l+r)>>1].process;
    do{
        while(pps[i].process>mid)
            i++;
        while(pps[j].process<mid)
            j--;
        if(i<=j)
        {
            program_process temp;
            temp=pps[i];
            pps[i]=pps[j];
            pps[j]=temp;
            i++,j--;
        }
    }while(i<=j);
    if(l<j)
        quick_sort_process(l,j);
    if(i<r)
        quick_sort_process(i,r);
    return;
}

void welcome_tec_task(){
    tread_file();
    printf("Students' processes:\n");
    quick_sort_id(1,pps_cnt);
    printf("++++++++++++++order by group's id+++++++++++++++++++++\n");
    printf("group_id\tgroup_process\n");
    for(rg int i=1;i<=pps_cnt;++i){
        printf("%d\t\t",pps[i].group_id);
        printf("%.2lf\n",pps[i].process);
    }
    printf("++++++++++++++order by processes++++++++++++++++++++\n");
    quick_sort_process(1,pps_cnt);
    printf("group_id\tgroup_process\n");
    for(rg int i=1;i<=pps_cnt;++i){
        printf("%d\t\t",pps[i].group_id);
        printf("%.2lf\n",pps[i].process);
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++\n");
    printf("The students's files have already in the exe address!\n");
    system("pause");
    return;
}

#endif