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

typedef struct{
    int group_id;
    double process;
}program_process;

int pps_cnt;
program_process pps[MAXN];

void read_file(){
    FILE *fp;
    fp=fopen(process_file,"r");
    while(true){
        fscanf(fp,"%d",&pps[++pps_cnt].group_id);
        fscanf(fp,"%lf",&pps[pps_cnt].process);
        if(feof(fp))
            break;
    }
    fclose(fp);
    return;
}

int serch_pps_num(int group_id){
    for(rg int i=1;i<=pps_cnt;++i)
        if(pps[i].group_id==group_id)
            return i;
    ++pps_cnt;
    pps[pps_cnt].group_id=group_id;
    return pps_cnt;
}

void push_file(){
    system("cls");
    printf("你的小组项目名称是:");
    char *program_name;
    program_name=(char*)malloc(1000*sizeof(char));
    scanf("%s",program_name);
    int T;
    printf("你要上传的文件数量:");
    scanf("%d",&T);
    int cnt=0;
    while(cnt<T){
        printf("请输入第%d文件的路径:",cnt+1);
        char *address;
        address=(char*)malloc(1000*sizeof(char));
        scanf("%s",address);
        char *file_name;
        file_name=(char*)malloc(1000*sizeof(char));
        printf("请输入文件名:");
        scanf("%s",file_name);
        strcat(address,"\\");
        strcat(address,file_name);
        FILE *fp1;
        if(!(fp1=fopen(address,"r"))){
            printf("请正确输入文件路径和名称!\n");
            continue;
        }
        char *write_file_name;
        write_file_name=(char*)malloc(1000*sizeof(char));
        strcpy(write_file_name,program_name);
        strcat(write_file_name,"-");
        strcat(write_file_name,file_name);
        FILE *fp2;
        if(!(fp2=fopen(write_file_name,"w"))){
            printf("提交文件失败!请再试一次!(Ctrl+C强制退出)\n");
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
    printf("提交完成\n");
    system("pause");
    return;
}

void push_process(){
    system("cls");
    printf("你的小组编号是:");
    int group_num;
    scanf("%d",&group_num);
    int pps_num=serch_pps_num(group_num);
    double process;
    while(true){
        printf("你的小组完成进度是（请输入0~1之间的小数）:");
        scanf("%lf",&process);
        if(0.0<=process&&process<=1.0)
            break;
        printf("请正确输入进度!\n");
    }
    pps[pps_num].process=process;
    printf("提交完成\n");
    system("pause");
    return;
}

void save_file(){
    FILE *fp;
    fp=fopen(process_file,"w");
    for(rg int i=1;i<=pps_cnt;++i){
        fprintf(fp,"%d\t",pps[i].group_id);
        fprintf(fp,"%.2lf\n",pps[i].process);
    }
    fclose(fp);
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
            printf("1-上传进度\n");
            printf("2-上传文件\n");
            printf("0-返回上级菜单\n");
            printf("++++++++++++++++++++++++\n");

            printf("\n选择你所需的功能编号:");
            scanf("%s",fuct);
            if(fuct[0]>='0'&&fuct[0]<='2')
                break;
            printf("请正确输入类型数字:\n");
        }
        switch(fuct[0]){
            case '1': push_process(),save_file();
                break;
            case '2': push_file();
                break;
            case '0': return;
        }
    }
    free(fuct);
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
        while(pps[i].process<mid)
            i++;
        while(pps[j].process>mid)
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

void welcome_tec(){
    read_file();
    printf("学生完成进度:\n");
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
    printf("学生提交文件已显示在程序文件夹中!\n");
    system("pause");
    return;
}

int main(){
    welcome_tec();
    return 0;
}

#endif