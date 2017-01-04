/* LinkQueue.c*/
/*链接队列：函数实现*/

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
	p = (PNode)malloc(sizeof(struct Node));  /*申请新结点空间*/
	if (p == NULL)	
		printf("Out of space!");            /*申请新结点失败*/
	else {
		p->info = x;
		p->link = NULL;                     /*填写新结点信息*/
		if (plqu->f == NULL)
			plqu->f = p;                    /*插入前是空队列*/
		else 
			plqu->r->link = p;             /*将新结点插入*/
		plqu->r = p;                       /*修改对尾指针*/
	}
}

void  deQueue_link(PLinkQueue plqu) {
	PNode   p;
	if (plqu->f == NULL) 
		printf("Empty queue.\n "); /*队列已空*/
	else {
		p = plqu->f;
		plqu->f = p->link;                          /*修改队头指针*/
		free(p);                              /*释放已经删除结点空间*/
	}
}


DataType  frontQueue_link(PLinkQueue plqu) {
	if (plqu == NULL) {
		printf("队列没有创建!\n ");
		return '\0';
	}
	else if (plqu->f == NULL) {
		printf("队列中没有元素!\n "); /*队列已空*/
		return '\0';
	}
	else
		return (plqu->f->info);
}

void printElement(PLinkQueue plqu) {
    PNode f=plqu->f;//获取队列的头结点 
	while(f!=NULL){//当当前节点不为空时
		printf("%c ",f->info);//输出节点信息
		f=f->link;//把节点的下一个节点赋给当前节点
	}
}

//打印队列中的第i个元素
void printElementA(PLinkQueue plqu,int pos) {
	PNode f=plqu->f;//获取队列的头结点 
	int cnt=1;//控制循环次数
	while(f!=NULL){//当当前节点不为空时
		if(cnt==pos){//当循环次数达到pos时
			printf("%c ",f->info);//输出节点信息
			return ;//直接return掉 或者break都行
		}
		f=f->link;//把节点的下一个节点赋给当前节点
		cnt++;//循环次数+1
	}
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空链接队列!\n");
	printf("2. 从链接队列尾部插入一个元素!\n");
	printf("3. 从链接队列头部删除一个元素!\n");
	printf("4. 获取队列头部元素!\n");
	printf("5. 打印队列中所有元素!\n");
	printf("6. 打印队列中第i位元素!\n");
	printf("0. 退出\n");
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