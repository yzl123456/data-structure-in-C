#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*LinkSet.h*/
/*集合的链接表示方式：类型和界面定义*/
/*注意：这里没有给出全部的函数，只是教材中给出了实现的函数的声明*/

struct  Node;
typedef char DataType;
typedef  struct Node  *PNode;
struct  Node {
	DataType  info;
	PNode     link;
};
typedef  struct Node  *LinkSet;

/*求单链表表示集合的交集*/
int intersectionLink(LinkSet s0, LinkSet s1, LinkSet s2);

/*集合的赋值*/
int assignLink(LinkSet s0, LinkSet s1);

/*有序链表表示的集合中的插入操作*/
int insertLink(LinkSet s0, DataType x);
LinkSet create(){
	//创建头结点
	PNode tmp=(PNode )malloc(sizeof(struct Node));
	tmp->link=NULL;
	return tmp;
}

int intersectionLink(LinkSet s0, LinkSet s1, LinkSet s2) {
	PNode x;
	/*判断集合是否存在*/
	if (s0 == NULL || s1 == NULL || s2 == NULL) {
		printf("No head node error");
		return 0;
	} 
	s2->link = NULL;    /*将s2置成空集合*/
	s0 = s0->link;  s1 = s1->link;
	while (s0 != NULL&&s1 != NULL)
		if (s0->info>s1->info)
			s1 = s1->link;
		else if (s0->info<s1->info)
			s0 = s0->link;
		else if (s0->info == s1->info) {   /*找到相同元素*/
			x = (PNode)malloc(sizeof(struct Node)); /*分配结点空间*/
			if (x == NULL) {
				printf("out of space"); 
				return 0;
			}
			x->info = s0->info; 
			x->link = NULL; 
			s2->link = x;   /*在s2中插入*/
			s0 = s0->link;  /*指针后推*/
			s1 = s1->link; 
			s2 = s2->link; 
		}
		return 1;
}

int assignLink(LinkSet s0, LinkSet s1) {
	PNode  x;
	/*判断集合是否存在*/
	if (s0 == NULL || s1 == NULL) { 
		printf("No head node error"); 
		return 0; 
	} 
	s0->link = NULL;    /*将s0置成空集合*/
	s1 = s1->link;
	while (s1 != NULL) {
		x = (PNode)malloc(sizeof(struct Node)); /*分配结点空间*/
		if (x == NULL) {
			printf("out of space");
			return 0;
		}
		x->info = s1->info;
		x->link = NULL;
		s0->link = x; /*在s0中插入*/
		s1 = s1->link; s0 = s0->link; /*指针后推*/
	}
	return 1;
}

int insertLink(LinkSet s0, DataType x) {
	PNode  temp;
	/*判断集合是否存在*/
	if (s0 == NULL) {
		printf("No head node error");
		return 0;
	}
	temp = (PNode)malloc(sizeof(struct Node)); /*分配结点空间*/
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
		else if (s0->link->info>x) {/*找到插入位置*/
			temp->info = x;
			temp->link = s0->link;
			s0->link = temp;
			return 1; /*插入*/
		}
	}
	if (s0->link == NULL) { /*插到最后*/
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
	LinkSet h1=s0->link;//带头结点的
	LinkSet h2=s1->link;
	while(h1!=NULL){
		while(h2!=NULL&&h2->info<h1->info){//此层while始终保持h2>=h1
			h2=h2->link;//一直找到h2满足条件
		}
		if(h2==NULL){
			insertLink(s2,h1->info);
		}
		else if(h2->info==h1->info){//2个集合中元素大小一样,不插入
			;//啥也不干。。。
		}
		else if(h2->info>h1->info){
			insertLink(s2,h1->info);//符合要求插入
		}
		h1=h1->link;//往下找
	}
}

void printNode(LinkSet  s) {
	LinkSet head=s->link;//带头结点的指针，所以赋值的时候赋值s->link
	//遍历
	while(head!=NULL){
		printf("%c ",head->info);
		head=head->link;
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 将字符插入集合S0中\n");
	printf("2. 将字符插入集合S1中\n");
	printf("3. 打印集合S0中元素\n");
	printf("4. 打印集合S1中元素\n");
	printf("5. 集合S0与集合S1的交\n");
	printf("6. 集合S0与集合S1的并\n");
	printf("7. 集合S0与集合S1的差\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
	int way;
	char x[3];//字符数组避免读换行空格
	LinkSet s0=create();//创建集合
	LinkSet s1=create();
	LinkSet s2;
	
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			//输入并插入
			printf("input the inserted value:");
			scanf("%s",x);
			insertLink(s0,x[0]);
		}
		else if(way==2){
			//输入并插入
			printf("input the inserted value:");
			scanf("%s",x);
			insertLink(s1,x[0]);
		}
		else if(way==3){
			//打印
			printNode(s0);
		}
		else if(way==4){
			//打印
			printNode(s1);
		}
		else if(way==5){
			//交
			s2=create();
			intersectionLink(s0,s1,s2);
			printNode(s2);
		}
		else if(way==6){
			//并
			s2=create();
			unitLink(s0,s1,s2);
			printNode(s2);
		}
		else if(way==7){
			//差
			s2=create();
			difference(s0,s1,s2);
			printNode(s2);
		}
	}
}