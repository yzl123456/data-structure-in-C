#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*SeqBinTree.c*/
/*二叉树的顺序表示*/

typedef char DataType;

struct SeqBinTree {				/* 顺序二叉树类型定义 */
	int   MAXNUM;               /* 完全二叉树中允许结点的最大个数 */
	int       n;                /* 改造成完全二叉树后，结点的实际个数 */
	DataType  *nodelist; 		/* 存放结点的数组 */
};
typedef  struct SeqBinTree  *PSeqBinTree; /*顺序二叉树类型的指针类型*/


PSeqBinTree createEmptyBinTree_seq(int m) {
	/* 创建新的顺序表 */
	PSeqBinTree pSeqBinTree = (PSeqBinTree)malloc(sizeof(struct SeqBinTree));
	if (pSeqBinTree != NULL) {
		pSeqBinTree->nodelist = (DataType*)malloc(sizeof(DataType)*m);
		if (pSeqBinTree->nodelist) {
			pSeqBinTree->MAXNUM = m;
			pSeqBinTree->n = 0;					/* 空表长度为0 */
			return (pSeqBinTree);
		}
		else free(pSeqBinTree);
	}
	printf("Out of space!!\n");    	/* 存储分配失败 */
	return NULL;
}

int isNull(PSeqBinTree pSeqBinTree) {
	if (pSeqBinTree->n == 0)
		return 1;
	else
		return 0;
}


/*返回下标为p的结点的父结点的下标*/
int parent_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return (p - 1) / 2;
}

/*返回下标为p的结点的左子结点的下标*/
int leftChild_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return 2 * p + 1;
}

/*返回下标为p的结点的右子结点的下标*/
int rightChild_seq(PSeqBinTree t, int p) {
	if (p < 0 || p >= t->n) 
		return -1;
	return 2 * (p + 1);
}


void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空树\n");
	printf("2. 插入值进入空树\n");
	printf("3. 返回p位置的父结点\n");
	printf("4. 返回p位置的左结点\n");
	printf("5. 返回P位置的右结点\n");
	printf("6. 打印所有结点\n");
	printf("0. 退出\n");
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
			root=createEmptyBinTree_seq(100);//建树后将头节点赋给root
		}
		else if(way==2){
			printf("please input the number of tree");
			scanf("%d",&number);getchar();//getchar读掉输入number后的换行
			for(i=root->n;i<root->n+number;i++){
				printf("number %d:",i);
				scanf("%c",&x);getchar();//getchar读掉输入一个字符后面的换行
				root->nodelist[i]=x;//将输入的字符赋值给root->nodelist
			}
			root->n+=number;//root的n的个数加上number
		}
		else if(way==3){
			printf("input the index of P:");
			scanf("%d",&pos);
			tmp=parent_seq(root,pos);//求parent的下标
			printf("index->%d  value->%c\n",tmp,root->nodelist[tmp]);//输出
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
			for(i=0;i<root->n;i++){//从头到尾遍历一遍
				printf("%c ",root->nodelist[i]);
			}
			printf("\n");
		}

	}
	



	printf("1");


}