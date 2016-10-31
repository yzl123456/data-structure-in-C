/* LinkQueue.c*/
/*���Ӷ��У�����ʵ��*/

#include <stdio.h>
#include <stdlib.h>
#include "LinkQueue.h"

PLinkQueue  createEmptyQueue_link(void) {
	PLinkQueue plqu;
	plqu = (PLinkQueue)malloc(sizeof(struct LinkQueue));
	if (plqu != NULL) {
		plqu->f = NULL;
		plqu->r = NULL;
	}
	else
		printf("Out of space!! \n");
	return (plqu);
}


int  isEmptyQueue_link(PLinkQueue plqu) {
	return (plqu->f == NULL);
}

void  enQueue_link(PLinkQueue plqu, DataType x) {
	PNode  p;
	p = (PNode)malloc(sizeof(struct Node));  /*�����½��ռ�*/
	if (p == NULL)	
		printf("Out of space!");            /*�����½��ʧ��*/
	else {
		p->info = x;
		p->link = NULL;                     /*��д�½����Ϣ*/
		if (plqu->f == NULL)
			plqu->f = p;                    /*����ǰ�ǿն���*/
		else 
			plqu->r->link = p;             /*���½�����*/
		plqu->r = p;                       /*�޸Ķ�βָ��*/
	}
}

void  deQueue_link(PLinkQueue plqu) {
	PNode   p;
	if (plqu->f == NULL) 
		printf("Empty queue.\n "); /*�����ѿ�*/
	else {
		p = plqu->f;
		plqu->f = p->link;                          /*�޸Ķ�ͷָ��*/
		free(p);                              /*�ͷ��Ѿ�ɾ�����ռ�*/
	}
}


DataType  frontQueue_link(PLinkQueue plqu) {
	if (plqu == NULL) {
		printf("����û�д���!\n ");
		return '\0';
	}
	else if (plqu->f == NULL) {
		printf("������û��Ԫ��!\n "); /*�����ѿ�*/
		return '\0';
	}
	else
		return (plqu->f->info);
}

void printElement(PLinkQueue plqu) {
    PNode f=plqu->f;//��ȡ���е�ͷ��� 
	while(f!=NULL){//����ǰ�ڵ㲻Ϊ��ʱ
		printf("%c ",f->info);//����ڵ���Ϣ
		f=f->link;//�ѽڵ����һ���ڵ㸳����ǰ�ڵ�
	}
}

//��ӡ�����еĵ�i��Ԫ��
void printElementA(PLinkQueue plqu,int pos) {
	PNode f=plqu->f;//��ȡ���е�ͷ��� 
	int cnt=1;//����ѭ������
	while(f!=NULL){//����ǰ�ڵ㲻Ϊ��ʱ
		if(cnt==pos){//��ѭ�������ﵽposʱ
			printf("%c ",f->info);//����ڵ���Ϣ
			return ;//ֱ��return�� ����break����
		}
		f=f->link;//�ѽڵ����һ���ڵ㸳����ǰ�ڵ�
		cnt++;//ѭ������+1
	}
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. ���������Ӷ���!\n");
	printf("2. �����Ӷ���β������һ��Ԫ��!\n");
	printf("3. �����Ӷ���ͷ��ɾ��һ��Ԫ��!\n");
	printf("4. ��ȡ����ͷ��Ԫ��!\n");
	printf("5. ��ӡ����������Ԫ��!\n");
	printf("6. ��ӡ�����е�iλԪ��!\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	int way,pos;
	PLinkQueue plqu;
	char x;
	while (1) {
	    printScreen();
		scanf("%d",&way);
		if(way==1){
			plqu=createEmptyQueue_link();
		}
		else if(way==2){
			getchar();
			scanf("%c",&x);
			enQueue_link(plqu,x);
		}
		else if(way==3){
			deQueue_link(plqu);
		}
		else if(way==4){
			printf("%c\n",frontQueue_link(plqu));
		}
		else if(way==5){
			printElement(plqu);
		}
		else if(way==6){
			scanf("%d",&pos);
			printElementA(plqu,pos);
		}
	}
}