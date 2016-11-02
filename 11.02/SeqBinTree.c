#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*SeqBinTree.c*/
/*��������˳���ʾ*/

typedef char DataType;

struct SeqBinTree {				/* ˳����������Ͷ��� */
	int   MAXNUM;               /* ��ȫ��������������������� */
	int       n;                /* �������ȫ�������󣬽���ʵ�ʸ��� */
	DataType  *nodelist; 		/* ��Ž������� */
};
typedef  struct SeqBinTree  *PSeqBinTree; /*˳����������͵�ָ������*/


PSeqBinTree createEmptyBinTree_seq(int m) {
	/* �����µ�˳��� */
	PSeqBinTree pSeqBinTree = (PSeqBinTree)malloc(sizeof(struct SeqBinTree));
	if (pSeqBinTree != NULL) {
		pSeqBinTree->nodelist = (DataType*)malloc(sizeof(DataType)*m);
		if (pSeqBinTree->nodelist) {
			pSeqBinTree->MAXNUM = m;
			pSeqBinTree->n = 0;					/* �ձ���Ϊ0 */
			return (pSeqBinTree);
		}
		else free(pSeqBinTree);
	}
	printf("Out of space!!\n");    	/* �洢����ʧ�� */
	return NULL;
}

int isNull(PSeqBinTree pSeqBinTree) {
	if (pSeqBinTree->n == 0)
		return 1;
	else
		return 0;
}


/*�����±�Ϊp�Ľ��ĸ������±�*/
int parent_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return (p - 1) / 2;
}

/*�����±�Ϊp�Ľ������ӽ����±�*/
int leftChild_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return 2 * p + 1;
}

/*�����±�Ϊp�Ľ������ӽ����±�*/
int rightChild_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return 2 * (p + 1);
}


void printScreen() {
	printf("\n*************************\n");
	printf("1. ��������\n");
	printf("2. ����ֵ�������\n");
	printf("3. ����pλ�õĸ����\n");
	printf("4. ����pλ�õ�����\n");
	printf("5. ����Pλ�õ��ҽ��\n");
	printf("6. ��ӡ���н��\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}


void main() {
	PSeqBinTree root;
	int way,number,i,pos,tmp;
	char x;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			root=createEmptyBinTree_seq(100);//������ͷ�ڵ㸳��root
		}
		else if(way==2){
			printf("please input the number of tree");
			scanf("%d",&number);getchar();//getchar��������number��Ļ���
			for(i=root->n;i<root->n+number;i++){
				printf("number %d:",i);
				scanf("%c",&x);getchar();//getchar��������һ���ַ�����Ļ���
				root->nodelist[i]=x;//��������ַ���ֵ��root->nodelist
			}
			root->n+=number;//root��n�ĸ�������number
		}
		else if(way==3){
			printf("input the index of P:");
			scanf("%d",&pos);
			tmp=parent_seq(root,pos);//��parent���±�
			printf("index->%d  value->%c\n",tmp,root->nodelist[tmp]);//���
		}
		else if(way==4){
			printf("input the index of P:");
			scanf("%d",&pos);
			tmp=leftChild_seq(root,pos);
			printf("index->%d  value->%c\n",tmp,root->nodelist[tmp]);
		}
		else if(way==5){
			printf("input the index of P:");
			scanf("%d",&pos);
			tmp=rightChild_seq(root,pos);
			printf("index->%d  value->%c\n",tmp,root->nodelist[tmp]);
		}
		else if(way==6){
			for(i=0;i<root->n;i++){//��ͷ��β����һ��
				printf("%c ",root->nodelist[i]);
			}
			printf("\n");
		}

	}
	



	printf("1");


}