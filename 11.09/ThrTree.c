#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define M 20
/*ThrTree.c*/
/*����������*/

typedef char DataType;

struct ThrTreeNode;	/* �����������еĽ�� */
typedef struct ThrTreeNode * PThrTreeNode;	/* ָ����������������ָ������ */
struct ThrTreeNode {	/* �����������н��Ķ��� */
	DataType      info;
	PThrTreeNode  llink, rlink;
	int           ltag, rtag;
};
typedef struct ThrTreeNode * ThrTree;	/* �������������͵Ķ��� */
typedef ThrTree * PThrTree;	    /* �������������͵�ָ������ */

struct  SeqStack { 	/* ˳��ջ���Ͷ��� */
	int  MAXNUM;      /* ջ�����Ԫ�ظ��� */
	int  t; 	/* t<MAXNUM��ָʾջ��λ�ã�������Ԫ�ظ��� */
	struct ThrTreeNode **s;
};
typedef  struct SeqStack  *PSeqStack;	/* ˳��ջ���͵�ָ������ */

int  isEmptyStack_seq(PSeqStack pastack) {
	//return pastack->t;
	if(pastack->t==0) return 1;//ע��յ�ʱ��ŷ���1
	else return 0;
}

PSeqStack createEmptyStack_seq(int m) {
	PSeqStack pastack=(PSeqStack )(malloc(sizeof(struct SeqStack)));//��̬����
	pastack->MAXNUM=m;
	pastack->t=0;//ջ����ʼλ��Ϊ0,��ջ�д��Ԫ�ص��±��0��ʼ
	pastack->s=(struct ThrTreeNode **)(malloc(sizeof(struct ThrTreeNode *)*m));//��̬����
	return pastack;
}

/* ��ջ��ѹ��һԪ��x */
void  push_seq(PSeqStack pastack, PThrTreeNode x) {
	pastack->s[pastack->t]=x;//��ջ
	pastack->t++;//ջ������
}

/* ɾ��ջ��Ԫ�� */
void  pop_seq(PSeqStack pastack) {
	pastack->t--;//ջ��λ������һ��
}

/* ��pastack��ָ��ջ��Ϊ��ջʱ����ջ��Ԫ�ص�ֵ */
PThrTreeNode  top_seq(PSeqStack pastack) {
	return pastack->s[pastack->t-1];//ע�ⷵ�ص�ʱ���±�Ҫ��1����Ϊ��0��ʼ
}

/*���Գ���������������*/
void thread(ThrTree  t) {
	PSeqStack  st = createEmptyStack_seq(M);
	/*ջԪ�ص�������ThrTree, Mһ��ȡt�ĸ߶� */
	ThrTree  p, pr;
	if (t == NULL)
		return;
	p = t;
	pr = NULL;
	do {
		/*�����������ջ��,Ȼ�������������*/
		while (p != NULL) {
			push_seq(st, p); p = p->llink;
		}
		p = top_seq(st);
		pop_seq(st);

		if (pr != NULL) {
			if (pr->rlink == NULL) { pr->rlink = p; pr->rtag = 1; }
			/*�޸�ǰ��������ָ��*/
			if (p->llink == NULL) { p->llink = pr; p->ltag = 1; }
			/*�޸ĸý�����ָ��*/
		}
		pr = p;
		p = p->rlink; 	 /* ���������� */
	} while (!isEmptyStack_seq(st) || p != NULL);
}

void visit(PThrTreeNode  p) {
	printf("%c ", p->info);
	//return t->info;
}

/*���Գ������ζԳ�������������*/
void nInOrder(ThrTree  t) {
	ThrTree  p = t;
	if (t == NULL) return;
	while (p->llink != NULL && p->ltag == 0)
		p = p->llink;	/*˳������һֱ���� */
	while (p != NULL) {
		visit(p);
		if (p->rlink != NULL && p->rtag == 0) {
			/* ��������������ʱ */
			p = p->rlink;
			while (p->llink != NULL&&p->ltag == 0)
				p = p->llink;                              /*˳��������������һֱ����*/
		}
		else
			p = p->rlink;    	   /* ˳�������� */
	}
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
PThrTreeNode leftChild_link(PThrTreeNode p) {
	if (p == NULL) 
		return NULL;
	return p->llink;
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
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


/*�������ȸ��������εĵݹ��㷨*/
void preOrder(ThrTree  t) {
	if (t == NULL) return;
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*�������Գ������εĵݹ��㷨*/
void inOrder(ThrTree  t) {
	if (t == NULL) return;
	inOrder(leftChild_link(t));
	visit(t);
	inOrder(rightChild_link(t));
}

/*����������������εĵݹ��㷨*/
void postOrder(ThrTree  t) {
	if (t == NULL) return;
	postOrder(leftChild_link(t));
	postOrder(rightChild_link(t));
	visit(t);
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. ����ֵ���������\n");
	printf("2. �ȸ��������\n");
	printf("3. �Գƴ������\n");
	printf("4. ����������\n");
	printf("5. ������������\n");
	printf("6. �Գƴ������ζԳ�������������\n");
	printf("0. �˳�\n");
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
	printf("��������ڵ�:");
	scanf("%c", &thrTree->info);
	getchar();
	while (1) {
		printScreen();
		printf("����˵�: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("�����븸����ֵ:");
			scanf("%c", &parent);
			getchar();
			printf("Ҫ����Ľ���ֵ:");
			scanf("%c", &x);
			getchar();
			p = (PThrTreeNode)malloc(sizeof(struct ThrTreeNode));
			p->info = x;
			p->llink = NULL;
			p->rlink = NULL;
			p->ltag = 0;
			p->rtag = 0;

			printf("Ҫ����λ��:");
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
			printf("���������������!");
			break;
		case 6:
			nInOrder(thrTree);
			break;
		case 0:
			exit(0);
		}
	}


}