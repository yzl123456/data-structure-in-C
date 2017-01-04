/* SeqQueue.c*/
/*顺序队列：函数实现*/
/*注意：这里没有给出全部函数的实现*/

#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

PSeqQueue createEmptyQueue_seq(int m){
	PSeqQueue tmp=(PSeqQueue )malloc(sizeof(struct SeqQueue)); 
	tmp->MAXNUM=m;
	tmp->f=0;tmp->r=0;
	tmp->q=malloc(sizeof(char)*m);
	return tmp;
}
/* 在队尾插入元素x */
void  enQueue_seq(PSeqQueue paqu, DataType x) {
	if (paqu == NULL)
		printf("队列没有创建，无法插入元素!");
	else if ((paqu->r + 1) % paqu->MAXNUM == paqu->f){
		printf("Full queue.\n");
	}
	else {
		paqu->q[paqu->r] = x;
		paqu->r = (paqu->r + 1) % paqu->MAXNUM;
	}
}

/* 删除队列头部元素 */
void  deQueue_seq(PSeqQueue paqu){
	if (paqu == NULL)
		printf("队列没有创建!");
	else if (paqu->f == paqu->r)
		printf("Empty Queue.\n");
	else {
		paqu->f = (paqu->f + 1) % paqu->MAXNUM;
	}
}

DataType  frontQueue_seq(PSeqQueue paqu)
{
	if (paqu == NULL) {
		printf("队列没有创建!\n");
		return '\0';
	}
	else if (paqu->f == paqu->r) {
		printf("队列中没有元素!\n");
		return '\0';
	}
	else
		return (paqu->q[paqu->f]);
}

void printElement(PSeqQueue paqu) {
	int i,tmp;//tmp表示需要循环的次数，即元素的个数
	if (paqu == NULL)
		printf("队列没有创建!");
	else if (paqu->f == paqu->r)
		printf("队列中没有元素!");
	else{
		if(paqu->r<paqu->f)//如果尾节点在头结点之前，需要加上一个周期maxnum
			tmp=(paqu->r+paqu->MAXNUM)-paqu->f;
		else tmp=paqu->r-paqu->f;//否则直接相减获取元素个数

		for (i = 0; i<tmp; i++) {
			if(i+ paqu->f >= paqu->MAXNUM)//如果当前遍历到的元素下表超过了maxnum，则输出当前下标减去maxnum的值
				printf("%c ",paqu->q[i + paqu->f - paqu->MAXNUM]);
			else printf("%c ", paqu->q[i + paqu->f]);//否则正常输出
			//下面是一种更为简单的方式
			//printf("%c ", paqu->q[(i + paqu->f)%paqu->MAXNUM]);
		}
	}
	printf("\n");
}


void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空队列!\n");
	printf("2. 从队列尾部插入一个元素!\n");
	printf("3. 从队列头部删除一个元素!\n");
	printf("4. 获取队列头部元素!\n");
	printf("5. 打印队列中所有元素!\n");
	printf("0. 退出\n");
	printf("*************************\n");
}


void main() {
	int way;char ch;
	PSeqQueue myQueue;
	
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			myQueue=createEmptyQueue_seq(5);
		}
		else if(way==2){
			getchar();
			scanf("%c",&ch);
			enQueue_seq(myQueue,ch);
		}
		else if(way==3){
			deQueue_seq(myQueue);
		}
		else if(way==4){
			printf("%c\n",frontQueue_seq(myQueue));
		}
		else if(way==5){
			printElement(myQueue);
		}
	}
}