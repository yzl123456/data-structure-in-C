#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*LChildBrotherTree.c*/
/*���ĳ���-�ֵܱ�ʾ��*/

typedef char DataType;
struct  CSNode;   			 /* ���н��ṹ */
typedef  struct  CSNode  * PCSNode;  /* ����ָ������ */
struct  CSNode { 			 /* ���ṹ���� */
	DataType   info;		 /* ����е�Ԫ�� */
	PCSNode  lchild;		 /* ���������ӽ���ָ�� */
	PCSNode  rsibling;		 /* �������ֵܵ�ָ�� */
};
typedef  struct CSNode * CSTree;	/* �����Ͷ��� */

/* ����ջ */
typedef  struct Node  *PNode;	/* ָ�����ָ������ */
struct  Node {				    /* �������㶨�� */
	CSTree		info;
	PNode		link;
};

struct LinkStack {			   /* ����ջ���Ͷ��� */
	PNode  top;		           /* ָ��ջ����� */
};
typedef  struct LinkStack  *Stack;	 /* ����ջ���͵�ָ������ */

/* ������� */
struct  LinkQueue { 		/* ���Ӷ������Ͷ��� */
	PNode  f;  		/* ͷָ�� */
	PNode  r;  		/* βָ�� */
};
typedef  struct LinkQueue  *Queue;		/*���Ӷ������͵�ָ������*/

/****��ջ��غ�����ʼ****/
Stack  createEmptyStack(void) {
	Stack plstack;
	plstack = (Stack)malloc(sizeof(struct LinkStack));
	if (plstack != NULL)
		plstack->top = NULL;
	else
		printf("Out of space! \n");  /*����ʧ��*/
	return (plstack);
}

void push(Stack plstack, CSTree x) {
	PNode  p;
	p = (PNode)malloc(sizeof(struct Node));
	if (p == NULL)
		printf("Out of space!\n");
	else {
		p->info = x;
		p->link = plstack->top;
		plstack->top = p;
	}
}

int  isEmptyStack(Stack plstack) {
	return (plstack->top == NULL);
}

void  pop(Stack plstack) {
	PNode p;
	if (isEmptyStack(plstack))
		printf("Empty stack pop.\n");
	else {
		//printf("�����ַ�Ϊ: %c", plstack->top->info);
		p = plstack->top;
		plstack->top = plstack->top->link;
		free(p);
	}
}

CSTree top(Stack plstack) {
	if (plstack->top == NULL) {
		return '\0';
	}
	else
		return (plstack->top->info);
}
/****��ջ��غ�������****/

/****�������غ�����ʼ****/
Queue  createEmptyQueue(void) {
	Queue plqu;
	plqu = (Queue)malloc(sizeof(struct LinkQueue));
	if (plqu != NULL) {
		plqu->f = NULL;
		plqu->r = NULL;
	}
	else
		printf("Out of space!! \n");
	return (plqu);
}

int  isEmptyQueue(Queue plqu) {
	return (plqu->f == NULL);
}

void  enQueue(Queue plqu, CSTree x) {
	PNode  p;
	p = (PNode)malloc(sizeof(struct Node));  /*�����½��ռ�*/
	if (p == NULL)
		printf("Out of space!");            /*�����½��ʧ��*/
	else {
		p->info = x;
		p->link = NULL;                     /*��д�½����Ϣ*/
		if (plqu->f == NULL)
			plqu->f = p;                    /*����ǰ�ǿն���*/
		else
			plqu->r->link = p;             /*���½�����*/
		plqu->r = p;                       /*�޸Ķ�βָ��*/
	}
}

void  deQueue(Queue plqu) {
	PNode   p;
	if (plqu->f == NULL)
		printf("Empty queue.\n ");           /*�����ѿ�*/
	else {
		p = plqu->f;
		plqu->f = p->link;                   /*�޸Ķ�ͷָ��*/
		free(p);                             /*�ͷ��Ѿ�ɾ�����ռ�*/
	}
}

CSTree  frontQueue(Queue plqu) {
	if (plqu == NULL) {
		printf("����û�д���!\n ");
		return '\0';
	}
	else if (plqu->f == NULL) {
		printf("������û��Ԫ��!\n ");         /*�����ѿ�*/
		return '\0';
	}
	else
		return (plqu->f->info);
}
/****�������غ�������****/

DataType visit(CSTree t) {
	printf("%c", t->info);
	return t->info;
}

PCSNode root(CSTree t) {
	return t;
}

DataType getInfo(CSTree t) {
	return t->info;
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
CSTree leftChild(CSTree p) {
	if (p == NULL)
		return NULL;
	return p->lchild;
}

/*���ؽ��p�����ֵܵĵ�ַ*/
CSTree rightSibling(CSTree p) {
	if (p->rsibling != NULL)
		return p->rsibling;
	else
		return NULL;
}




/*���ȸ�����ݹ������*/
void insertNode(CSTree t, DataType parent, PCSNode p) {
	CSTree  c;
	if (t == NULL) 
		return;
	if(t->info==parent){//�ݹ�ֱ��t->info==parentʱ��ʾ��ǰ��tΪ����Ҫ�ҵĸ��ڵ�
		c = leftChild(t);//���жϸø��ڵ����޳���
		if(c==NULL){//�޳���
			t->lchild=p;//��p����t�ĳ��ӣ�return
			return ;
		}
		while (c->rsibling != NULL) { //���Ѵ��ڳ��ӣ��ҵ������ֵܽڵ�
			c = rightSibling(c); 
		}
		c->rsibling=p;//��Ҫ����Ľڵ㸳�������ֵܵ��ҽڵ㣬return
		return ;
	}
	//visit(root(t));  
	c = leftChild(t);//��t->info��������parent�����ȴ�t�ĳ��ӿ�ʼ�ݹ���
	while (c != NULL) { 
		insertNode(c,parent,p);//�ݹ�ӵ�ǰc��ʼ��
		c = rightSibling(c); //�����ֵܲ�Ϊ�գ�ÿ�δ��������ֵܿ�ʼ��
	}
}

/*���ȸ������������ķǵݹ������*/
void insertNode2(CSTree t, DataType parent, PCSNode p) {
	CSTree c = t;PCSNode cur,par_node;//cur(current)��ǰ���ڱ����Ľڵ㣬par_node������Ҫ�ҵĸ��ڵ�
	Stack  s = createEmptyStack();	/* ջԪ�ص�������Tree  */
	do {
		while (c != NULL) { 
			//visit(root(c));
			par_node=root(c);//����ÿ�ε�ջ������c���ж�����info�Ƿ������Ҫ�ҵ�parent
			if(par_node->info==parent){//�ҵ�����Ҫ���
				cur=leftChild(par_node);//���жϸ��ڵ����޳���
				if(cur==NULL)//�޳���
					par_node->lchild=p;//��p�������ڵ�ĳ���
				else{//�г���
					while(cur->rsibling!=NULL)//�ҵ������ֵܽڵ�
						cur=cur->rsibling;
					cur->rsibling=p;//��p���������ֵܽڵ���ҽڵ�
				}
				return ;
			}
			push(s, c); 
			c = leftChild(c); 
		}
		while ((c == NULL) && (!isEmptyStack(s))) {
			c = rightSibling(top(s)); 
			pop(s); 
		}
	} while (c != NULL);


}


/*���ȸ������������ĵݹ��㷨*/
void preOrder(CSTree  t) {
	CSTree  c;
	if (t == NULL) 
		return;
	visit(root(t));  
	c = leftChild(t);
	while (c != NULL) { 
		preOrder(c);  
		c = rightSibling(c); 
	}
}

/*���ȸ������������ķǵݹ��㷨*/
void nPreOrder(CSTree t) {
	CSTree c = t;
	Stack  s = createEmptyStack();	/* ջԪ�ص�������Tree  */
	do {
		while (c != NULL) { 
			visit(root(c)); 
			push(s, c); 
			c = leftChild(c); 
		}
		while ((c == NULL) && (!isEmptyStack(s))) {
			c = rightSibling(top(s)); 
			pop(s); 
		}
	} while (c != NULL);
}

/*����������������ĵݹ��㷨*/
void postOrder(CSTree t) {
	CSTree  c;
	if (t == NULL) return;
	c = leftChild(t);
	while (c != NULL) { 
		postOrder(c); 
		c = rightSibling(c); 
	}
	visit(root(t));
}

/*����������������㷨*/
void levelOrder(CSTree  t) {
	CSTree  c;
	/*����Ԫ�ص�����ΪTree*/
	Queue q;	
	q = createEmptyQueue();  
	c = t;
	if (c == NULL)  
		return;
	enQueue(q, c);
	while (!isEmptyQueue(q)) {
		c = frontQueue(q); 
		deQueue(q); 
		visit(root(c));  
		c = leftChild(c);
		while (c != NULL) { 
			enQueue(q, c); 
			c = rightSibling(c); 
		}
	}
}

/*���ҽ�㣬�����ؽ��ָ��*/
PCSNode searchNode(CSTree t, DataType x) {
	//���ܵ������ֱ�����ʽ���ɣ��˴����ò�α���

	CSTree  c;
	/*����Ԫ�ص�����ΪTree*/
	Queue q;	
	q = createEmptyQueue();  
	c = t;
	if (c == NULL)  
		return;
	enQueue(q, c);
	while (!isEmptyQueue(q)) {
		c = frontQueue(q); 
		if(c->info==x){//�ڲ�α��������ҵ�����Ҫ��ĸ��ڵ㣬ֱ��return ����ڵ�ָ��
			return c;
		}
		deQueue(q); 
		//visit(root(c));  
		c = leftChild(c);
		while (c != NULL) { 
			enQueue(q, c); 
			c = rightSibling(c); 
		}
	}


}

/*��ĳ���ĸ��ڵ�*/
PCSNode parentCSTree(PCSNode p, CSTree t) {
	PCSNode q, r;
	if (p == NULL)
		return NULL;
	if (p == t || t == NULL)
		return NULL;
	q = t->lchild;
	while (q != NULL) {
		if (q == p)
			return t;
		r = parentCSTree(p, q);
		if (r != NULL)
			return r;
		q = q->rsibling;
	}
	return NULL;
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. �����������\n");
	printf("2. �ȸ�����ݹ�����(����)��\n");
	printf("3. �ȸ�����ǵݹ�����(����)��\n");
	printf("4. �������ݹ�����(����)��\n");
	printf("5. �����������(����)��\n");
	printf("6. �����ӽڵ�ĸ��ڵ�\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	int input;
	char par;
	char x;
	PCSNode child, parent;
	PCSNode p;
	CSTree csTree = (CSTree)malloc(sizeof(struct CSNode));
	csTree->lchild = NULL;
	csTree->rsibling = NULL;
	printf("��������ڵ�:");
	scanf("%c", &csTree->info);
	getchar();
	while (1) {
		printScreen();
		printf("����˵�: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("�����븸����ֵ:");
			scanf("%c", &par);
			getchar();
			printf("Ҫ����Ľ���ֵ:");
			scanf("%c", &x);
			getchar();
			p = (PCSNode)malloc(sizeof(struct CSNode));
			p->info = x;
			p->lchild = NULL;
			p->rsibling = NULL;
			//�˴����л�
			insertNode(csTree, par, p);
			//insertNode2(csTree, par, p);
			break;
		case 2:
			printf("�ȸ�����ݹ�����(����)����");
			preOrder(csTree);
			break;
		case 3:
			printf("�ȸ�����ǵݹ�����(����)����");
			nPreOrder(csTree);
			break;
		case 4:
			printf("�������ݹ�����(����)����");
			postOrder(csTree);
			break;
		case 5:
			printf("�����������(����)����");
			levelOrder(csTree);
			break;
		case 6:
			printf("����Ҫ���Ҹ��׵Ľ���ֵ:");
			scanf("%c", &x);
			getchar();
			child = searchNode(csTree, x);
			if(child == NULL){
				printf("�ý�㲻���ڣ�");
				break;
			}
			parent = parentCSTree(child, csTree);
			if (parent == NULL){
				printf("�ý��û�и��ף�");
				break;
			}
			else
				printf("��� %c �ĸ�����:%c",x, parent->info);
			break;
		case 0:
			exit(1);
			break;
		default:printf("error.");
		}
	}

}