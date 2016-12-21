#pragma warning(disable:4996)
/*平衡的二叉排序树*/
#include<stdio.h>
#include <stdlib.h>
struct AVLNode;
typedef struct AVLNode * PAVLNode;
typedef int KeyType;

//新增学生结构
typedef struct {
	char info[10],name[10];
}stu;
typedef stu* DataType;

struct AVLNode
{
	KeyType key;						/* 结点的关键码 */
	int bf;							/* 结点的平衡因子 */
	PAVLNode llink, rlink;				/* 分别指向结点的左、右子女 */
	DataType stud;//树中节点新增一个指向字典结构的指针域
};
typedef struct AVLNode *AVLTree;
typedef AVLTree * PAVLTree;

/*创建以key为关键码的AVL树结点*/
PAVLNode creatNode(KeyType key,DataType stu) {//同时传递学生结构体
	PAVLNode node = (PAVLNode)malloc(sizeof(struct AVLNode));
	node->key = key;  
	node->bf = 0;  
	node->stud=stu;//赋值给对应指针
	node->llink = node->rlink = NULL;
	return (node);
}

/* LL型调整 */
PAVLNode  lL(PAVLNode  a, PAVLNode  b) {
	a->bf = 0;  
	a->llink = b->rlink;	 
	b->bf = 0;  
	b->rlink = a;	/* b指向调整后的子树的根结点 */
	return(b);
}

/* RR型调整 */
PAVLNode  rR(PAVLNode a, PAVLNode b) {
	a->bf = 0;  
	a->rlink = b->llink;  
	b->bf = 0;  
	b->llink = a;
	return(b);
}

/* LR型调整 */
PAVLNode  lR(PAVLNode a, PAVLNode b) {
	PAVLNode c = b->rlink;;
	a->llink = c->rlink; b->rlink = c->llink; c->llink = b; c->rlink = a;
	switch (c->bf) {
	case 0:	
		a->bf = 0;  b->bf = 0;  /* LR(0)型调整 */
		break;		
	case 1:	
		a->bf = 1;  b->bf = 0;  /* 新结点插在*c的左子树中，LR(L)型调整 */
		break;	
	case -1:
		a->bf = 0;  b->bf = -1; /* 新结点插在*c的右子树中，LR(R)型调整 */
		break; 
	}
	c->bf = 0;		return(c);
}


/* RL型调整 */
PAVLNode  rL(PAVLNode a, PAVLNode b) {
	PAVLNode c = b->llink;
	a->rlink = c->llink;  
	b->llink = c->rlink;	
	c->llink = a;  
	c->rlink = b;
	switch (c->bf) {
	case 0:	
		a->bf = 0;  b->bf = 0;  /* *c本身就是插入结点，RL(0)型调整 */
		break;	
	case 1:	
		a->bf = 0;  b->bf = 1;  /* 插在*c的左子树中，RL(L)型调整 */
		break;	
	case -1:
		a->bf = -1;  b->bf = 0;  /* 插在*c的右子树中，RL(R)型调整 */
		break;	
	}
	c->bf = 0;   
	return(c);
}

/*AVL树的插入*/
int avlInsert(PAVLTree ptree, KeyType key,DataType stu) {//传参stu
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
	/* 寻找插入位置及可能的最小不平衡子树*node_a */
	while (p != NULL) {
		if (key == p->key)	  
			return 1;	  		/* AVL树中已经有关键码为key的结点 */
		r = q;  q = p;
		if (key<p->key)	
			p = p->llink;				/* 进入*p的左子树 */
		else	 
			p = p->rlink;						/* 进入*p的右子树 */
		if (q->bf != 0) { 
			parent_a = r;  
			node_a = q; 
		}/* 寻找最小不平衡子树*node_a */
	}
	node = creatNode(key,stu);
	if (node == NULL) return 0;
	/* 将新结点插入到AVL树中，node_a指向可能的最小不平衡子树。 */
	/* *node_b为*node_a的子女中可能增高的子树*/
	if (key<q->key) 
		q->llink = node;	
	else		
		q->rlink = node;
	if (key<node_a->key) { 
		node_b = p = node_a->llink; 
		d = -1; 
	}/*插在*node_a的左子树中 */
	else { 
		node_b = p = node_a->rlink; d = 1; 
	}		/*插在*node_a的右子树中 */
	/* 修改*node_b到新结点路径上的各结点的平衡因子。 */
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
	/* *node_a原来为根结点并且平衡因子为0，插入结点后只可能为1或－1，没有破坏树的平衡性 */
	if (node_a->bf == -d) { 
		node_a->bf = 0;  
		return 1; 
	}/* 新结点插在原来高度较小的子树中*/
	/* 下面是新结点插在原来高度较大的子树中，破坏了平衡性，要对子树进行调整 */
	if (d == -1)								/* 新结点插在*node_a的左子树中*/
		if (node_b->bf == -1)  
			node_b = lL(node_a, node_b);		/* LL型调整*/
		else  
			node_b = lR(node_a, node_b);		/* LR型调整*/
	else									    /* 新结点插在*node_a的右子树中*/
		if (node_b->bf == 1)  
			node_b = rR(node_a, node_b);		/* RR型调整 */
		else  
			node_b = rL(node_a, node_b);		/* RL 型调整 */
		/*将node_b 作为调整后的根*/
	if (parent_a == NULL) 
		*ptree = node_b;	/* node_a原来指向树的根结点 */
	else {
		if (parent_a->llink == node_a)  
			parent_a->llink = node_b;
		else  
			parent_a->rlink = node_b;
	}
	return 1;
}

void visit(PAVLNode  p) {
	printf("关键字Key=%d, 平衡因子=%d\n", p->key, p->bf);
}

/*返回结点p的左子结点的地址*/
PAVLNode leftChild_link(PAVLNode p) {
	if (p == NULL)
		return NULL;
	return p->llink;
}

/*返回结点p的右子结点的地址*/
PAVLNode rightChild_link(PAVLNode p) {
	if (p == NULL)
		return NULL;
	return p->rlink;
}

/*二叉树先根次序周游的递归算法*/
void preOrder(AVLTree t) {
	if (t == NULL) return;
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*二叉树对称序周游的递归算法*/
void inOrder(AVLTree t) {
	if (t == NULL) return;
	inOrder(leftChild_link(t));
	visit(t);
	inOrder(rightChild_link(t));
}

/*二叉树后根次序周游的递归算法*/
void postOrder(AVLTree t) {
	if (t == NULL) return;
	postOrder(leftChild_link(t));
	postOrder(rightChild_link(t));
	visit(t);
}
void find(AVLTree t,KeyType key){//递归求解，小了往左，大了往右
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
	printf("1. 插入Key进入平衡二叉树\n");
	printf("2. 先根次序遍历平衡二叉树\n");
	printf("3. 中根次序遍历平衡二叉树\n");
	printf("4. 后根次序遍历平衡二叉树\n");
	printf("5.find\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void main() {
	/*
		请独立思考后实在不会写再看此题解，否则后果自负！！！
	*/
	KeyType key=-1;
	int input;
	PAVLTree ptree;
	DataType stud;//学生类型变量
	ptree = (AVLTree*)malloc(sizeof(struct AVLNode));	
	(*ptree) = NULL;

	while (1) {
		printScreen();
		printf("输入菜单: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
		case 1:
			while (key!=0) {
				printf("请输入Key:");
				scanf("%d", &key);
				if(key==0) break;
				stud=(DataType )malloc(sizeof(stu));//申请空间
				printf("please input classinfo:");
				scanf("%s",stud->info);
				printf("please input name:");
				scanf("%s",stud->name);//赋值
				avlInsert(ptree, key,stud);//插入
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
			scanf("%d",&key);//输入
			find(*ptree,key);//递归
			break;
		case 0:
			exit(0);
		}
	}
}