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
        printf("文件读取失败，将创建一个新的文件!\n");
        fp=fopen(process_file,"w+");
        system("pause");
    }
    while(true){
        int gid;
        double gpr;
        fscanf(fp,"%d",&gid);
        fscanf(fp,"%lf",&gpr);
        if(feof(fp))
            break;
        pps[++pps_cnt].group_id=gid;
        pps[pps_cnt].process=gpr;
    }
    fclose(fp);
    return;
}

int search_pps_num(int gid){
    for(rg int i=1;i<=pps_cnt;++i)
        if(pps[i].group_id==gid)
            return i;
    pps_cnt++;
    pps[pps_cnt].group_id=gid;
    pps[pps_cnt].process=0.0;
    return pps_cnt;
}

void push_file(){
    system("cls");
    printf("小组项目名称是:");
    char *program_name;
    program_name=(char*)malloc(1000*sizeof(char));
    scanf("%s",program_name);
    int T;
    printf("要提交的文件数量:");
    while(!scanf("%d",&T)){
        printf("请正确输入一个数字!\n");
        printf("要提交的文件数量:");
        char s[10000];
        gets(s);
        system("pause");
    }
    char ch=getchar();
    while(ch!='\n')
        ch=getchar();
    int cnt=0;
    while(cnt<T){
        printf("请输入第%d个文件的地址:",cnt+1);
        char *address;
        address=(char*)malloc(1000*sizeof(char));
        scanf("%s",address);
        char *file_name;
        file_name=(char*)malloc(1000*sizeof(char));
        printf("请输入第%d个文件的名称:",cnt+1);
        scanf("%s",file_name);
        strcat(address,"\\");
        strcat(address,file_name);
        FILE *fp1;
        if(!(fp1=fopen(address,"r"))){
            printf("请正确输入文件的地址或名称!\n");
            continue;
        }
        char *write_file_name;
        write_file_name=(char*)malloc(1000*sizeof(char));
        strcpy(write_file_name,program_name);
        strcat(write_file_name,"-");
        strcat(write_file_name,file_name);
        FILE *fp2;
        if(!(fp2=fopen(write_file_name,"w"))){
            printf("上传失败!请再试一次!(Ctrl+C 以强制退出)\n");
            continue;
        }
        while(true){
            char s[1000];
            fgets(s,1000,fp1);
            if(feof(fp1))
                break;
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
    printf("上传成功!\n");
    system("pause");
    return;
}

void push_process(){
    system("cls");
    int pps_num=search_pps_num(group_num);

    double process;
    while(true){
        printf("请输入一个0到1的小数表示完成度:");
        scanf("%lf",&process);
        if(0.0<=process&&process<=1.0)
            break;
        printf("输入错误!\n");
    }
    pps[pps_num].process=process;
    printf("提交成功!\n");
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
            printf("1-上传进度\n");
            printf("2-上传文件\n");
            printf("0-回到上级目录\n");
            printf("---------------------------------\n");

            printf("\n请输入功能编号:");
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
    pps_cnt=0;
    tread_file();
    printf("学生项目完成进度:\n");
    quick_sort_id(1,pps_cnt);
    printf("++++++++++++++按组排序+++++++++++++++++++++\n");
    printf("group_id\tgroup_process\n");
    for(rg int i=1;i<=pps_cnt;++i){
        printf("%d\t\t",pps[i].group_id);
        printf("%.2lf\n",pps[i].process);
    }
    printf("++++++++++++++按进度排序++++++++++++++++++++\n");
    quick_sort_process(1,pps_cnt);
    printf("group_id\tgroup_process\n");
    for(rg int i=1;i<=pps_cnt;++i){
        printf("%d\t\t",pps[i].group_id);
        printf("%.2lf\n",pps[i].process);
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++\n");
    printf("学生上传文件已显示在该程序所在文件夹中!\n");
    system("pause");
    return;
}

#endif