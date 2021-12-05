//author by UESTC
//rebuild by mengpei

#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int data;
    List *next;
}List;

bool insert(List *L,int data,int choice){
    List *temp;
    List *pre=L,*p=L->next;

    switch(choice){
        case 0:{// insert into head;
            while(p!=NULL)
            pre=p,p=p->next;
            temp=(List*)malloc(sizeof(List));
            pre->next=temp;
            temp->data=data;
            temp->next=NULL;
            return true;
        }
        case 1:{// insert into tail;
            temp=(List*)malloc(sizeof(List));
            temp->data=data;
            temp->next=p;
            pre->next=temp;
            return true;
        }
    }
}

bool delete(List *L, char* id) {
    List *pre=L, *p=L->next;
    while(p!=NULL){
        //search for the delete position;
        //here written by yourself;
        pre=p;
        p=p->next;
    }
    if(p==NULL)
    return false;
    (pre->next)=(p->next);
    free(p);
    return true;
}

List* search(List *L, char* id) {
    List *p=L->next;
    while(p!=NULL){
        //search;
        //here written by yourself;
        p=p->next;
    }
    return p;
}

bool update(List *L, char* id,int new_data){
    List *p=L->next;
    List *ptarget=search(L,id);
    if(ptarget==NULL)
    return false;
    ptarget->data=new_data;
    return true;
}

void output_one(List *p){
	printf("%d",p->data);
    return;
}

void output_all(List *L)
{
    List *p=L->next;
    while(p!=NULL){
        output_one(p);
        p=p->next;
    }
	return;
}

void destory_list(List **L) {
	if (L==NULL||*L==NULL)
		return;
	List *pre=*L,*p=(*L)->next;
	while(p!=NULL){
        free(pre);
        pre=p;
        p=p->next;
    }
    free(pre);
    (*L)=NULL;
    return;
}

void read_file(){
    FILE *fp;
    fp=fopen("filename","r");
    //fscanf;
    return;
}

void save_file(){
    FILE *fp;
    fp=fopen("filename","w");
    fprintf(fp,"");
    return;
}

int main(){
    return 0;
}