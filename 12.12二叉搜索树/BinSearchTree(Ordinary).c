#pragma warning(disable:4996)
/*BinSearchTree.c*/
/*二叉排序树*/

#include <stdio.h>
#include <stdlib.h>
struct BinSearchNode;
typedef struct BinSearchNode * PBinSearchNode;
typedef int KeyType;
typedef int DataType;


typedef struct {
	KeyType key;				/* 字典元素的关键码字段	*/
	DataType value;			    /* 字典元素的属性字段	*/
}DicElement;

typedef struct {
	int MAXNUM; 		/*字典中元素的个数上界*/
	int n;					/*为字典中实际元素的个数 */
	DicElement *element; 		 /*存放字典中的元素*/
} SeqDictionary;

struct BinSearchNode {
	KeyType key;					/* 结点的关键码字段 */
	PBinSearchNode llink, rlink;		/* 二叉树的左、右指针 */
};
typedef struct BinSearchNode * BinSearchTree;	/*二叉排序树	*/
typedef BinSearchTree * PBinSearchTree;
SeqDictionary* create(int m){//创建序列字典
	SeqDictionary* node=(SeqDictionary *)malloc(sizeof(SeqDictionary));
	node->MAXNUM=m;
	node->n=0;
	node->element=(DicElement *)malloc(sizeof(DicElement)*m);
	return node;
}
int insertDictionary(SeqDictionary * pdic, KeyType key, DataType value) {
	int i,number=pdic->n;
	if (pdic->n >= pdic->MAXNUM) {   /* 溢出 */
		printf("Overflow!\n");
		return (0);
	}
	if (pdic->n == 0) {                    /*空顺序表插入 */
		pdic->element[0].key = key;        /* 插入Key */
		pdic->element[0].value = value;    /* 插入value */
		pdic->n = 1;                       /* 元素个数为1 */
		return (1);
	}

	pdic->element[number].key = key;        /* 插入Key */
	pdic->element[number].value = value;    /* 插入value */
	pdic->n = pdic->n + 1;                /* 元素个数加1 */
	return (1);
}

/*二叉排序树的检索算法*/
int search(PBinSearchTree ptree, KeyType key, PBinSearchNode *position) {
	PBinSearchNode p, q;
	p = *ptree;  q = p;
	while (p != NULL) {
		q = p; 		/* 用q记录父结点的位置 */
		if (p->key == key) { 
			*position = p;  
			return(1); 
		}		/* 检索成功 */
		else if (p->key>key)	  
			p = p->llink;			/* 进入左子树继续检索 */
		else	
			p = p->rlink;			/* 进入右子树继续检索 */
	}
	*position = q;  
	return(0);					/* 检索失败 */
}

/*二叉排序树中插入结点*/
int insert(PBinSearchTree ptree, KeyType key) {
	PBinSearchNode p, position;
	if (search(ptree, key, &position) == 1) 
		return 1;   /* 已存在关键码为key的结点 */
	p = (PBinSearchNode)malloc(sizeof(struct BinSearchNode));/* 申请新结点 */
	/* 申请空间出错 */
	if (p == NULL) { 
		printf("Error\n");  return 0; 
	}	
	/* 对新结点的赋值 */
	p->key = key;	
	p->llink = p->rlink = NULL;		
	/* 原树为空树 */
	if (position == NULL)	
		*ptree = p;					
	else if (key<position->key) 
		position->llink = p;	  /* 插入position的左子树 */
	else  
		position->rlink = p;				/* 插入position的右子树 */
	return 1;
}

/*二叉排序树的构造*/
int creatSearchTree(PBinSearchTree ptree, SeqDictionary *dic) {
	int i;
	*ptree = NULL; 			/* 将二叉排序树置空 */
	for (i = 0; i<dic->n; i++)
		if (!insert(ptree, dic->element[i].key)) 
			return 0;			/* 将新结点插入树中 */
	return 1;
}

/*二叉排序树的删除*/
int delete(PBinSearchTree ptree, KeyType key) {
	PBinSearchNode parentp, p, r;
	p = *ptree;  parentp = NULL;
	while (p != NULL) {
		if (p->key == key)  
			break;				/* 找到了关键码为key的结点 */
		parentp = p;
		if (p->key>key)  
			p = p->llink;			/* 进入左子树 */
		else  
			p = p->rlink;						/* 进入右子树 */
	}
	if (p == NULL)  
		return 0;					/* 二叉排序树中无关键码为key的结点 */
	if (p->llink == NULL) { 					/* 结点*p无左子树 */
		/* 被删除的结点是原二叉排序树的根结点*/
		if (parentp == NULL) 
			*ptree = p->rlink;		
		else if (parentp->llink == p)	
			parentp->llink = p->rlink;	/*将*p的右子树链到其父结点的左链*/
		else	
			parentp->rlink = p->rlink;	/* 将*p的右子树链到其父结点的右链上 */
	}
	else {								/* 结点*p有左子树 */
		r = p->llink;
		while (r->rlink != NULL)  
			r = r->rlink;		/* 在*p的左子树中找最右下结点*r */
		r->rlink = p->rlink;	/* 用*r的右指针指向*p的右子女 */
		if (parentp == NULL)  
			*ptree = p->llink;
		else if (parentp->llink == p)	
			parentp->llink = p->llink;	/* 用*p的左子女代替*p */
		else	 
			parentp->rlink = p->llink;
	}
	free(p);  
	return 1;									/* 释放被删除结点 */
}

void printDictionary(SeqDictionary * pdic) {
	int i;
	for(i=0;i<pdic->n;i++){//打印
		printf("key: %d  value:%d\n",pdic->element[i].key,pdic->element[i].value);
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 创建字典\n");
	printf("2. 二叉排序树中插入结点(创建索引)\n");
	printf("3. 二叉排序树中检索Key(关键码)\n");
	printf("4. 删除二叉排序树中的结点\n");
	printf("5. 打印字典\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
	int way,key,val,res,x;//res存检索的结果
	SeqDictionary* dic=NULL;
	PBinSearchTree root=(PBinSearchTree)malloc(sizeof(struct BinSearchNode));//根节点
	PBinSearchNode pos=(PBinSearchNode)malloc(sizeof(struct BinSearchNode));//pos存检索到的那个指针节点
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			dic=create(50);//创建
			while(1){
				printf("input the key:");
				scanf("%d",&key);//输入
				if(key==0) break;
				printf("input the value:");
				scanf("%d",&val);
				insertDictionary(dic,key,val);//插入字典
			}
		}
		else if(way==2){
			creatSearchTree(root,dic);//建树
		}
		else if(way==3){
			printf("input the key you want:");
			scanf("%d",&x);
			res=search(root,x,&pos);//查找，注意这里要用&pos作形参，虽然用pos也能运行。。。
			if(res!=0) printf("find is ok!");
			else printf("not find!");
		}
		else if(way==4){
			printf("input the key you want to delete:");
			scanf("%d",&x);
			res=delete(root,x);//删除
			if(res!=0) printf("delete is ok!");
			else printf("delete defeat!");
		}
		else if(way==5){
			printDictionary(dic);//打印
		}
	}
}