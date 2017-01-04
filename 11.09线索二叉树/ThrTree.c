#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define M 20
/*ThrTree.c*/
/*线索二叉树*/

typedef char DataType;

struct ThrTreeNode;	/* 线索二叉树中的结点 */
typedef struct ThrTreeNode * PThrTreeNode;	/* 指向线索二叉树结点的指针类型 */
struct ThrTreeNode {	/* 线索二叉树中结点的定义 */
	DataType      info;
	PThrTreeNode  llink, rlink;
	int           ltag, rtag;
};
typedef struct ThrTreeNode * ThrTree;	/* 线索二叉树类型的定义 */
typedef ThrTree * PThrTree;	    /* 线索二叉树类型的指针类型 */

struct  SeqStack { 	/* 顺序栈类型定义 */
	int  MAXNUM;      /* 栈中最大元素个数 */
	int  t; 	/* t<MAXNUM，指示栈顶位置，而不是元素个数 */
	struct ThrTreeNode **s;
};
typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */

int  isEmptyStack_seq(PSeqStack pastack) {
	//return pastack->t;
	if(pastack->t==0) return 1;//注意空的时候才返回1
	else return 0;
}

PSeqStack createEmptyStack_seq(int m) {
	PSeqStack pastack=(PSeqStack )(malloc(sizeof(struct SeqStack)));//动态分配
	pastack->MAXNUM=m;
	pastack->t=0;//栈顶初始位置为0,即栈中存放元素的下标从0开始
	pastack->s=(struct ThrTreeNode **)(malloc(sizeof(struct ThrTreeNode *)*m));//动态分配
	return pastack;
}

/* 在栈中压入一元素x */
void  push_seq(PSeqStack pastack, PThrTreeNode x) {
	pastack->s[pastack->t]=x;//入栈
	pastack->t++;//栈顶上移
}

/* 删除栈顶元素 */
void  pop_seq(PSeqStack pastack) {
	pastack->t--;//栈顶位置下移一个
}

/* 当pastack所指的栈不为空栈时，求栈顶元素的值 */
PThrTreeNode  top_seq(PSeqStack pastack) {
	return pastack->s[pastack->t-1];//注意返回的时候下标要减1，因为从0开始
}

/*按对称序线索化二叉树*/
void thread(ThrTree  t) {
	PSeqStack  st = createEmptyStack_seq(M);
	/*栈元素的类型是ThrTree, M一般取t的高度 */
	ThrTree  p, pr;
	if (t == NULL)
		return;
	p = t;
	pr = NULL;
	do {
		/*遇到结点推入栈中,然后进入其左子树*/
		while (p != NULL) {
			push_seq(st, p); p = p->llink;
		}
		p = top_seq(st);
		pop_seq(st);

		if (pr != NULL) {
			if (pr->rlink == NULL) { pr->rlink = p; pr->rtag = 1; }
			/*修改前驱结点的右指针*/
			if (p->llink == NULL) { p->llink = pr; p->ltag = 1; }
			/*修改该结点的左指针*/
		}
		pr = p;
		p = p->rlink; 	 /* 进入右子树 */
	} while (!isEmptyStack_seq(st) || p != NULL);
}

void visit(PThrTreeNode  p) {
	printf("%c ", p->info);
	//return t->info;
}

/*按对称序周游对称序线索二叉树*/
void nInOrder(ThrTree  t) {
	ThrTree  p = t;
	if (t == NULL) return;
	while (p->llink != NULL && p->ltag == 0)
		p = p->llink;	/*顺左子树一直向下 */
	while (p != NULL) {
		visit(p);
		if (p->rlink != NULL && p->rtag == 0) {
			/* 右子树不是线索时 */
			p = p->rlink;
			while (p->llink != NULL&&p->ltag == 0)
				p = p->llink;                              /*顺右子树的左子树一直向下*/
		}
		else
			p = p->rlink;    	   /* 顺线索向下 */
	}
}

/*返回结点p的左子结点的地址*/
PThrTreeNode leftChild_link(PThrTreeNode p) {
	if (p == NULL) 
		return NULL;
	return p->llink;
}

/*返回结点p的右子结点的地址*/
PThrTreeNode rightChild_link(PThrTreeNode p) {
	if (p == NULL) 
		return NULL;
	return p->rlink;
}

void insertNode(ThrTree  t, DataType parent, PThrTreeNode p, char pos) {
	if (t == NULL)
		return;
	if (t->info == parent&&pos == 'l') {
		t->llink = p;
		return;
	}
	else if (t->info == parent&&pos == 'r') {
		t->rlink = p;
		return;
	}
	else {
		insertNode(leftChild_link(t), parent, p, pos);
		insertNode(rightChild_link(t), parent, p, pos);
	}
}


/*二叉树先根次序周游的递归算法*/
void preOrder(ThrTree  t) {
	if (t == NULL) return;
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*二叉树对称序周游的递归算法*/
void inOrder(ThrTree  t) {
	if (t == NULL) return;
	inOrder(leftChild_link(t));
	visit(t);
	inOrder(rightChild_link(t));
}

/*二叉树后根次序周游的递归算法*/
void postOrder(ThrTree  t) {
	if (t == NULL) return;
	postOrder(leftChild_link(t));
	postOrder(rightChild_link(t));
	visit(t);
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. 插入值进入二叉树\n");
	printf("2. 先根次序遍历\n");
	printf("3. 对称次序遍历\n");
	printf("4. 后根次序遍历\n");
	printf("5. 线索化二叉树\n");
	printf("6. 对称次序周游对称序线索二叉树\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void main() {
	int input;
	DataType parent;
	DataType x;
	char pos;
	PThrTreeNode p;
	ThrTree thrTree = (ThrTree)malloc(sizeof(struct ThrTreeNode));
	thrTree->llink = NULL;
	thrTree->rlink = NULL;
	thrTree->ltag = 0;
	thrTree->rtag = 0;
	printf("请输入根节点:");
	scanf("%c", &thrTree->info);
	getchar();
	while (1) {
		printScreen();
		printf("输入菜单: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("请输入父结点的值:");
			scanf("%c", &parent);
			getchar();
			printf("要插入的结点的值:");
			scanf("%c", &x);
			getchar();
			p = (PThrTreeNode)malloc(sizeof(struct ThrTreeNode));
			p->info = x;
			p->llink = NULL;
			p->rlink = NULL;
			p->ltag = 0;
			p->rtag = 0;

			printf("要插入位置:");
			scanf("%c", &pos);
			getchar();
			insertNode(thrTree, parent, p, pos);
			break;
		case 2:
			preOrder(thrTree);
			break;
		case 3:
			inOrder(thrTree);
			break;
		case 4:
			postOrder(thrTree);
			break;
		case 5:
			thread(thrTree);
			printf("线索化二叉树完成!");
			break;
		case 6:
			nInOrder(thrTree);
			break;
		case 0:
			exit(0);
		}
	}


}