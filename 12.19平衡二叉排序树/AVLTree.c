#pragma warning(disable:4996)
/*ƽ��Ķ���������*/
#include<stdio.h>
#include <stdlib.h>
struct AVLNode;
typedef struct AVLNode * PAVLNode;
typedef int KeyType;

//����ѧ���ṹ
typedef struct {
	char info[10],name[10];
}stu;
typedef stu* DataType;

struct AVLNode
{
	KeyType key;						/* ���Ĺؼ��� */
	int bf;							/* ����ƽ������ */
	PAVLNode llink, rlink;				/* �ֱ�ָ�����������Ů */
	DataType stud;//���нڵ�����һ��ָ���ֵ�ṹ��ָ����
};
typedef struct AVLNode *AVLTree;
typedef AVLTree * PAVLTree;

/*������keyΪ�ؼ����AVL�����*/
PAVLNode creatNode(KeyType key,DataType stu) {//ͬʱ����ѧ���ṹ��
	PAVLNode node = (PAVLNode)malloc(sizeof(struct AVLNode));
	node->key = key;  
	node->bf = 0;  
	node->stud=stu;//��ֵ����Ӧָ��
	node->llink = node->rlink = NULL;
	return (node);
}

/* LL�͵��� */
PAVLNode  lL(PAVLNode  a, PAVLNode  b) {
	a->bf = 0;  
	a->llink = b->rlink;	 
	b->bf = 0;  
	b->rlink = a;	/* bָ�������������ĸ���� */
	return(b);
}

/* RR�͵��� */
PAVLNode  rR(PAVLNode a, PAVLNode b) {
	a->bf = 0;  
	a->rlink = b->llink;  
	b->bf = 0;  
	b->llink = a;
	return(b);
}

/* LR�͵��� */
PAVLNode  lR(PAVLNode a, PAVLNode b) {
	PAVLNode c = b->rlink;;
	a->llink = c->rlink; b->rlink = c->llink; c->llink = b; c->rlink = a;
	switch (c->bf) {
	case 0:	
		a->bf = 0;  b->bf = 0;  /* LR(0)�͵��� */
		break;		
	case 1:	
		a->bf = 1;  b->bf = 0;  /* �½�����*c���������У�LR(L)�͵��� */
		break;	
	case -1:
		a->bf = 0;  b->bf = -1; /* �½�����*c���������У�LR(R)�͵��� */
		break; 
	}
	c->bf = 0;		return(c);
}


/* RL�͵��� */
PAVLNode  rL(PAVLNode a, PAVLNode b) {
	PAVLNode c = b->llink;
	a->rlink = c->llink;  
	b->llink = c->rlink;	
	c->llink = a;  
	c->rlink = b;
	switch (c->bf) {
	case 0:	
		a->bf = 0;  b->bf = 0;  /* *c������ǲ����㣬RL(0)�͵��� */
		break;	
	case 1:	
		a->bf = 0;  b->bf = 1;  /* ����*c���������У�RL(L)�͵��� */
		break;	
	case -1:
		a->bf = -1;  b->bf = 0;  /* ����*c���������У�RL(R)�͵��� */
		break;	
	}
	c->bf = 0;   
	return(c);
}

/*AVL���Ĳ���*/
int avlInsert(PAVLTree ptree, KeyType key,DataType stu) {//����stu
	PAVLNode node_a, node_b, parent_a, p, q, r, node;
	int d;
	if (*ptree == NULL) {
		*ptree = creatNode(key,stu);
		if (*ptree == NULL) 
			return 0; 
		else 
			return 1;
	}
	node_a = *ptree;  parent_a = NULL;  p = node_a;  q = NULL;
	/* Ѱ�Ҳ���λ�ü����ܵ���С��ƽ������*node_a */
	while (p != NULL) {
		if (key == p->key)	  
			return 1;	  		/* AVL�����Ѿ��йؼ���Ϊkey�Ľ�� */
		r = q;  q = p;
		if (key<p->key)	
			p = p->llink;				/* ����*p�������� */
		else	 
			p = p->rlink;						/* ����*p�������� */
		if (q->bf != 0) { 
			parent_a = r;  
			node_a = q; 
		}/* Ѱ����С��ƽ������*node_a */
	}
	node = creatNode(key,stu);
	if (node == NULL) return 0;
	/* ���½����뵽AVL���У�node_aָ����ܵ���С��ƽ�������� */
	/* *node_bΪ*node_a����Ů�п������ߵ�����*/
	if (key<q->key) 
		q->llink = node;	
	else		
		q->rlink = node;
	if (key<node_a->key) { 
		node_b = p = node_a->llink; 
		d = -1; 
	}/*����*node_a���������� */
	else { 
		node_b = p = node_a->rlink; d = 1; 
	}		/*����*node_a���������� */
	/* �޸�*node_b���½��·���ϵĸ�����ƽ�����ӡ� */
	while ((p != NULL) && (p != node)) {
		if (key<p->key) { 
			p->bf = -1;  
			p = p->llink; 
		}
		else { 
			p->bf = 1;  
			p = p->rlink; 
		}
	}
	if (node_a->bf == 0) { 
		node_a->bf = d;  
		return 1; 
	}
	/* *node_aԭ��Ϊ����㲢��ƽ������Ϊ0���������ֻ����Ϊ1��1��û���ƻ�����ƽ���� */
	if (node_a->bf == -d) { 
		node_a->bf = 0;  
		return 1; 
	}/* �½�����ԭ���߶Ƚ�С��������*/
	/* �������½�����ԭ���߶Ƚϴ�������У��ƻ���ƽ���ԣ�Ҫ���������е��� */
	if (d == -1)								/* �½�����*node_a����������*/
		if (node_b->bf == -1)  
			node_b = lL(node_a, node_b);		/* LL�͵���*/
		else  
			node_b = lR(node_a, node_b);		/* LR�͵���*/
	else									    /* �½�����*node_a����������*/
		if (node_b->bf == 1)  
			node_b = rR(node_a, node_b);		/* RR�͵��� */
		else  
			node_b = rL(node_a, node_b);		/* RL �͵��� */
		/*��node_b ��Ϊ������ĸ�*/
	if (parent_a == NULL) 
		*ptree = node_b;	/* node_aԭ��ָ�����ĸ���� */
	else {
		if (parent_a->llink == node_a)  
			parent_a->llink = node_b;
		else  
			parent_a->rlink = node_b;
	}
	return 1;
}

void visit(PAVLNode  p) {
	printf("�ؼ���Key=%d, ƽ������=%d\n", p->key, p->bf);
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
PAVLNode leftChild_link(PAVLNode p) {
	if (p == NULL)
		return NULL;
	return p->llink;
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
PAVLNode rightChild_link(PAVLNode p) {
	if (p == NULL)
		return NULL;
	return p->rlink;
}

/*�������ȸ��������εĵݹ��㷨*/
void preOrder(AVLTree t) {
	if (t == NULL) return;
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*�������Գ������εĵݹ��㷨*/
void inOrder(AVLTree t) {
	if (t == NULL) return;
	inOrder(leftChild_link(t));
	visit(t);
	inOrder(rightChild_link(t));
}

/*����������������εĵݹ��㷨*/
void postOrder(AVLTree t) {
	if (t == NULL) return;
	postOrder(leftChild_link(t));
	postOrder(rightChild_link(t));
	visit(t);
}
void find(AVLTree t,KeyType key){//�ݹ���⣬С�����󣬴�������
	if(key==t->key){
		printf("%s %s\n",t->stud->info,t->stud->name);return ;
	}
	else if(key>t->key){
		find(t->rlink,key);
	}
	else find(t->llink,key);
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. ����Key����ƽ�������\n");
	printf("2. �ȸ��������ƽ�������\n");
	printf("3. �и��������ƽ�������\n");
	printf("4. ����������ƽ�������\n");
	printf("5.find\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	/*
		�����˼����ʵ�ڲ���д�ٿ�����⣬�������Ը�������
	*/
	KeyType key=-1;
	int input;
	PAVLTree ptree;
	DataType stud;//ѧ�����ͱ���
	ptree = (AVLTree*)malloc(sizeof(struct AVLNode));	
	(*ptree) = NULL;

	while (1) {
		printScreen();
		printf("����˵�: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			while (key!=0) {
				printf("������Key:");
				scanf("%d", &key);
				if(key==0) break;
				stud=(DataType )malloc(sizeof(stu));//����ռ�
				printf("please input classinfo:");
				scanf("%s",stud->info);
				printf("please input name:");
				scanf("%s",stud->name);//��ֵ
				avlInsert(ptree, key,stud);//����
				//getchar();
			}
			break;
		case 2:
			preOrder(*ptree);
			break;
		case 3:
			inOrder(*ptree);
			break;
		case 4:
			postOrder(*ptree);
			break;
		case 5:
			printf("input the key:");
			scanf("%d",&key);//����
			find(*ptree,key);//�ݹ�
			break;
		case 0:
			exit(0);
		}
	}
}