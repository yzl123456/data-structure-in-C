#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*LChildBrotherTree.c*/
/*树的长子-兄弟表示法*/

typedef char DataType;
struct  CSNode;   			 /* 树中结点结构 */
typedef  struct  CSNode  * PCSNode;  /* 结点的指针类型 */
struct  CSNode { 			 /* 结点结构定义 */
	DataType   info;		 /* 结点中的元素 */
	PCSNode  lchild;		 /* 结点的最左子结点的指针 */
	PCSNode  rsibling;		 /* 结点的右兄弟的指针 */
};
typedef  struct CSNode * CSTree;	/* 树类型定义 */

/* 定义栈 */
typedef  struct Node  *PNode;	/* 指向结点的指针类型 */
struct  Node {				    /* 单链表结点定义 */
	CSTree		info;
	PNode		link;
};

struct LinkStack {			   /* 链接栈类型定义 */
	PNode  top;		           /* 指向栈顶结点 */
};
typedef  struct LinkStack  *Stack;	 /* 链接栈类型的指针类型 */

/* 定义队列 */
struct  LinkQueue { 		/* 链接队列类型定义 */
	PNode  f;  		/* 头指针 */
	PNode  r;  		/* 尾指针 */
};
typedef  struct LinkQueue  *Queue;		/*链接队列类型的指针类型*/

/****与栈相关函数开始****/
Stack  createEmptyStack(void) {
	Stack plstack;
	plstack = (Stack)malloc(sizeof(struct LinkStack));
	if (plstack != NULL)
		plstack->top = NULL;
	else
		printf("Out of space! \n");  /*创建失败*/
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
		//printf("弹出字符为: %c", plstack->top->info);
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
/****与栈相关函数结束****/

/****与队列相关函数开始****/
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

void  deQueue(Queue plqu) {
	PNode   p;
	if (plqu->f == NULL)
		printf("Empty queue.\n ");           /*队列已空*/
	else {
		p = plqu->f;
		plqu->f = p->link;                   /*修改队头指针*/
		free(p);                             /*释放已经删除结点空间*/
	}
}

CSTree  frontQueue(Queue plqu) {
	if (plqu == NULL) {
		printf("队列没有创建!\n ");
		return '\0';
	}
	else if (plqu->f == NULL) {
		printf("队列中没有元素!\n ");         /*队列已空*/
		return '\0';
	}
	else
		return (plqu->f->info);
}
/****与队列相关函数结束****/

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

/*返回结点p的左子结点的地址*/
CSTree leftChild(CSTree p) {
	if (p == NULL)
		return NULL;
	return p->lchild;
}

/*返回结点p的右兄弟的地址*/
CSTree rightSibling(CSTree p) {
	if (p->rsibling != NULL)
		return p->rsibling;
	else
		return NULL;
}




/*按先根次序递归插入结点*/
void insertNode(CSTree t, DataType parent, PCSNode p) {
	CSTree  c;
	if (t == NULL) 
		return;
	if(t->info==parent){//递归直到t->info==parent时表示当前的t为所需要找的父节点
		c = leftChild(t);//先判断该父节点有无长子
		if(c==NULL){//无长子
			t->lchild=p;//把p赋给t的长子，return
			return ;
		}
		while (c->rsibling != NULL) { //若已存在长子，找到最右兄弟节点
			c = rightSibling(c); 
		}
		c->rsibling=p;//将要插入的节点赋给最右兄弟的右节点，return
		return ;
	}
	//visit(root(t));  
	c = leftChild(t);//若t->info并不等于parent，则先从t的长子开始递归找
	while (c != NULL) { 
		insertNode(c,parent,p);//递归从当前c开始找
		c = rightSibling(c); //若右兄弟不为空，每次从它的右兄弟开始找
	}
}

/*按先根次序周游树的非递归插入结点*/
void insertNode2(CSTree t, DataType parent, PCSNode p) {
	CSTree c = t;PCSNode cur,par_node;//cur(current)当前正在遍历的节点，par_node，所需要找的父节点
	Stack  s = createEmptyStack();	/* 栈元素的类型是Tree  */
	do {
		while (c != NULL) { 
			//visit(root(c));
			par_node=root(c);//对于每次弹栈出来的c，判断他的info是否符合需要找的parent
			if(par_node->info==parent){//找到符合要求的
				cur=leftChild(par_node);//先判断父节点有无长子
				if(cur==NULL)//无长子
					par_node->lchild=p;//将p赋给父节点的长子
				else{//有长子
					while(cur->rsibling!=NULL)//找到最右兄弟节点
						cur=cur->rsibling;
					cur->rsibling=p;//将p赋给最右兄弟节点的右节点
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


/*按先根次序周游树的递归算法*/
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

/*按先根次序周游树的非递归算法*/
void nPreOrder(CSTree t) {
	CSTree c = t;
	Stack  s = createEmptyStack();	/* 栈元素的类型是Tree  */
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

/*按后根次序周游树的递归算法*/
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

/*广度优先周游树的算法*/
void levelOrder(CSTree  t) {
	CSTree  c;
	/*队列元素的类型为Tree*/
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

/*查找结点，并返回结点指针*/
PCSNode searchNode(CSTree t, DataType x) {
	//不管调用哪种遍历方式均可，此处采用层次遍历

	CSTree  c;
	/*队列元素的类型为Tree*/
	Queue q;	
	q = createEmptyQueue();  
	c = t;
	if (c == NULL)  
		return;
	enQueue(q, c);
	while (!isEmptyQueue(q)) {
		c = frontQueue(q); 
		if(c->info==x){//在层次遍历中若找到符合要求的父节点，直接return 这个节点指针
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

/*求某结点的父节点*/
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
	printf("1. 插入结点进入树\n");
	printf("2. 先根次序递归周游(遍历)树\n");
	printf("3. 先根次序非递归周游(遍历)树\n");
	printf("4. 后根次序递归周游(遍历)树\n");
	printf("5. 广度优先周游(遍历)树\n");
	printf("6. 返回子节点的父节点\n");
	printf("0. 退出\n");
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
	printf("请输入根节点:");
	scanf("%c", &csTree->info);
	getchar();
	while (1) {
		printScreen();
		printf("输入菜单: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			printf("请输入父结点的值:");
			scanf("%c", &par);
			getchar();
			printf("要插入的结点的值:");
			scanf("%c", &x);
			getchar();
			p = (PCSNode)malloc(sizeof(struct CSNode));
			p->info = x;
			p->lchild = NULL;
			p->rsibling = NULL;
			//此处可切换
			insertNode(csTree, par, p);
			//insertNode2(csTree, par, p);
			break;
		case 2:
			printf("先根次序递归周游(遍历)树：");
			preOrder(csTree);
			break;
		case 3:
			printf("先根次序非递归周游(遍历)树：");
			nPreOrder(csTree);
			break;
		case 4:
			printf("后根次序递归周游(遍历)树：");
			postOrder(csTree);
			break;
		case 5:
			printf("广度优先周游(遍历)树：");
			levelOrder(csTree);
			break;
		case 6:
			printf("输入要查找父亲的结点的值:");
			scanf("%c", &x);
			getchar();
			child = searchNode(csTree, x);
			if(child == NULL){
				printf("该结点不存在！");
				break;
			}
			parent = parentCSTree(child, csTree);
			if (parent == NULL){
				printf("该结点没有父亲！");
				break;
			}
			else
				printf("结点 %c 的父亲是:%c",x, parent->info);
			break;
		case 0:
			exit(1);
			break;
		default:printf("error.");
		}
	}

}