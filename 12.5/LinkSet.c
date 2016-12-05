#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*LinkSet.h*/
/*���ϵ����ӱ�ʾ��ʽ�����ͺͽ��涨��*/
/*ע�⣺����û�и���ȫ���ĺ�����ֻ�ǽ̲��и�����ʵ�ֵĺ���������*/

struct  Node;
typedef char DataType;
typedef  struct Node  *PNode;
struct  Node {
	DataType  info;
	PNode     link;
};
typedef  struct Node  *LinkSet;

/*�������ʾ���ϵĽ���*/
int intersectionLink(LinkSet s0, LinkSet s1, LinkSet s2);

/*���ϵĸ�ֵ*/
int assignLink(LinkSet s0, LinkSet s1);

/*���������ʾ�ļ����еĲ������*/
int insertLink(LinkSet s0, DataType x);
LinkSet create(){
	PNode tmp=(PNode )malloc(sizeof(struct Node));
	LinkSet s;
	tmp->link=NULL;
	s=(LinkSet)malloc(sizeof(struct Node));
	s->link=tmp;
	return s;
}

int intersectionLink(LinkSet s0, LinkSet s1, LinkSet s2) {
	PNode x;
	/*�жϼ����Ƿ����*/
	if (s0 == NULL || s1 == NULL || s2 == NULL) {
		printf("No head node error");
		return 0;
	} 
	s2->link = NULL;    /*��s2�óɿռ���*/
	s0 = s0->link;  s1 = s1->link;
	while (s0 != NULL&&s1 != NULL)
		if (s0->info>s1->info)
			s1 = s1->link;
		else if (s0->info<s1->info)
			s0 = s0->link;
		else if (s0->info == s1->info) {   /*�ҵ���ͬԪ��*/
			x = (PNode)malloc(sizeof(struct Node)); /*������ռ�*/
			if (x == NULL) {
				printf("out of space"); 
				return 0;
			}
			x->info = s0->info; 
			x->link = NULL; 
			s2->link = x;   /*��s2�в���*/
			s0 = s0->link;  /*ָ�����*/
			s1 = s1->link; 
			s2 = s2->link; 
		}
		return 1;
}

int assignLink(LinkSet s0, LinkSet s1) {
	PNode  x;
	/*�жϼ����Ƿ����*/
	if (s0 == NULL || s1 == NULL) { 
		printf("No head node error"); 
		return 0; 
	} 
	s0->link = NULL;    /*��s0�óɿռ���*/
	s1 = s1->link;
	while (s1 != NULL) {
		x = (PNode)malloc(sizeof(struct Node)); /*������ռ�*/
		if (x == NULL) {
			printf("out of space");
			return 0;
		}
		x->info = s1->info;
		x->link = NULL;
		s0->link = x; /*��s0�в���*/
		s1 = s1->link; s0 = s0->link; /*ָ�����*/
	}
	return 1;
}

int insertLink(LinkSet s0, DataType x) {
	PNode  temp;
	/*�жϼ����Ƿ����*/
	if (s0 == NULL) {
		printf("No head node error");
		return 0;
	}
	temp = (PNode)malloc(sizeof(struct Node)); /*������ռ�*/
	if (temp == NULL) {
		printf("out of space");
		return 0;
	}
	while (s0->link != NULL) {
		if (s0->link->info == x) {
			//printf("Data already exist");
			return 1;
		}
		else if (s0->link->info<x){
			s0 = s0->link;
		}
		else if (s0->link->info>x) {/*�ҵ�����λ��*/
			temp->info = x;
			temp->link = s0->link;
			s0->link = temp;
			return 1; /*����*/
		}
	}
	if (s0->link == NULL) { /*�嵽���*/
		temp->info = x;  
		temp->link = s0->link;
		s0->link = temp;  
		return 1;
	}
}

void unitLink(LinkSet s0, LinkSet s1, LinkSet s2) {
	assignLink(s2, s0);
	while (s1->link != NULL) {
		s1 = s1->link;
		insertLink(s2, s1->info);
	}
}

void difference(LinkSet s0, LinkSet s1, LinkSet s2) {
	int hash[305]={0};
	LinkSet s0Head=s0->link->link;
	LinkSet s1Head=s1->link->link;
	while(s1Head!=NULL){
		hash[s1Head->info]=1;
		s1Head=s1Head->link;
	}
	while(s0Head!=NULL){
		if(hash[s0Head->info]==0){
			insertLink(s2,s0Head->info);
		}
		s0Head=s0Head->link;
	}
}

void printNode(LinkSet  s) {
	LinkSet head=s->link->link;
	while(head!=NULL){
		printf("%c ",head->info);
		head=head->link;
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. ���ַ����뼯��S0��\n");
	printf("2. ���ַ����뼯��S1��\n");
	printf("3. ��ӡ����S0��Ԫ��\n");
	printf("4. ��ӡ����S1��Ԫ��\n");
	printf("5. ����S0�뼯��S1�Ľ�\n");
	printf("6. ����S0�뼯��S1�Ĳ�\n");
	printf("7. ����S0�뼯��S1�Ĳ�\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
	int way;
	char x[3];
	LinkSet s0=create();
	LinkSet s1=create();
	LinkSet s2=create();
	LinkSet tmp=create();
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			scanf("%s",x);
			insertLink(s0,x[0]);
		}
		else if(way==2){
			scanf("%s",x);
			insertLink(s1,x[0]);
		}
		else if(way==3){
			printNode(s0);
		}
		else if(way==4){
			printNode(s1);
		}
		else if(way==5){
			intersectionLink(s0,s1,s2);
			printNode(s2);
		}
		else if(way==6){
			unitLink(s0,s1,s2);
			printNode(s2);
		}
		else if(way==7){
			difference(s0,s1,tmp);
			printNode(tmp);
		}
	}
}
