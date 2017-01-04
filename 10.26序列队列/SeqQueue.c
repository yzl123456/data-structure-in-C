/* SeqQueue.c*/
/*˳����У�����ʵ��*/
/*ע�⣺����û�и���ȫ��������ʵ��*/

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
/* �ڶ�β����Ԫ��x */
void  enQueue_seq(PSeqQueue paqu, DataType x) {
	if (paqu == NULL)
		printf("����û�д������޷�����Ԫ��!");
	else if ((paqu->r + 1) % paqu->MAXNUM == paqu->f){
		printf("Full queue.\n");
	}
	else {
		paqu->q[paqu->r] = x;
		paqu->r = (paqu->r + 1) % paqu->MAXNUM;
	}
}

/* ɾ������ͷ��Ԫ�� */
void  deQueue_seq(PSeqQueue paqu){
	if (paqu == NULL)
		printf("����û�д���!");
	else if (paqu->f == paqu->r)
		printf("Empty Queue.\n");
	else {
		paqu->f = (paqu->f + 1) % paqu->MAXNUM;
	}
}

DataType  frontQueue_seq(PSeqQueue paqu)
{
	if (paqu == NULL) {
		printf("����û�д���!\n");
		return '\0';
	}
	else if (paqu->f == paqu->r) {
		printf("������û��Ԫ��!\n");
		return '\0';
	}
	else
		return (paqu->q[paqu->f]);
}

void printElement(PSeqQueue paqu) {
	int i,tmp;//tmp��ʾ��Ҫѭ���Ĵ�������Ԫ�صĸ���
	if (paqu == NULL)
		printf("����û�д���!");
	else if (paqu->f == paqu->r)
		printf("������û��Ԫ��!");
	else{
		if(paqu->r<paqu->f)//���β�ڵ���ͷ���֮ǰ����Ҫ����һ������maxnum
			tmp=(paqu->r+paqu->MAXNUM)-paqu->f;
		else tmp=paqu->r-paqu->f;//����ֱ�������ȡԪ�ظ���

		for (i = 0; i<tmp; i++) {
			if(i+ paqu->f >= paqu->MAXNUM)//�����ǰ��������Ԫ���±�����maxnum���������ǰ�±��ȥmaxnum��ֵ
				printf("%c ",paqu->q[i + paqu->f - paqu->MAXNUM]);
			else printf("%c ", paqu->q[i + paqu->f]);//�����������
			//������һ�ָ�Ϊ�򵥵ķ�ʽ
			//printf("%c ", paqu->q[(i + paqu->f)%paqu->MAXNUM]);
		}
	}
	printf("\n");
}


void printScreen() {
	printf("\n*************************\n");
	printf("1. �����ն���!\n");
	printf("2. �Ӷ���β������һ��Ԫ��!\n");
	printf("3. �Ӷ���ͷ��ɾ��һ��Ԫ��!\n");
	printf("4. ��ȡ����ͷ��Ԫ��!\n");
	printf("5. ��ӡ����������Ԫ��!\n");
	printf("0. �˳�\n");
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