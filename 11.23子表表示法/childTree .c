#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*ChiTree.c*/
/*树的子表表示法*/

typedef int DataType;
struct  EdgeNode {   	/* 子表中结点的结构 */
	int             nodeposition;  /* 子结点在结点表中的位置 */
	struct EdgeNode  *link;       /* 指向下一个子表中的结点 */
};

struct  ChiTreeNode {           /* 结点表中结点的结构 */
	DataType         info;      /* 结点本身的信息 */
	struct EdgeNode  *children; /* 本结点子表的头指针 */
};

struct  ChiTree { 		/* 树结构 */
	int    MAXNUM;      /* 树中最大结点个数 */
	int    root;	    /* 根结点的下标 */
	int    n; 		    /* 实际结点个数 */
	struct ChiTreeNode  * nodelist;    /*结点表 */
};
typedef  struct  ChiTree *  PChiTree;

/* 创建子表表示法树 */
PChiTree createEmptyChildTree_seq(int m) {
	PChiTree pChiTree = (PChiTree)malloc(sizeof(struct ChiTree));
	if (pChiTree != NULL) {
		pChiTree->nodelist = (struct ChiTreeNode*)malloc(sizeof(struct ChiTreeNode)*m);
		if (pChiTree->nodelist != NULL) {
			pChiTree->MAXNUM = m;
			pChiTree->n = 0;					/* 空表长度为0 */
			return (pChiTree);
		}
		else free(pChiTree);
	}
	printf("Out of space!!\n");    	/* 存储分配失败 */
	return NULL;
}

void insertchiTree_root(PChiTree pChiTree, char root) {
	if (pChiTree->n == 0) {
		// 插入根节点
		pChiTree->nodelist[0].info = root;
		pChiTree->nodelist[0].children = NULL;
		pChiTree->n = 1;
	}
	else {
		printf("根节点已经存在！");
	}
}

/*返回1表示插入成功,0表示插入失败*/
int insertTree_chiTree(PChiTree pChiTree, char node, char parentnode) {
	int i,pos=-1,number;//i循环，pos记录父节点的位置，number节点个数
	struct EdgeNode * head;//head存nodelist[i].children 子链表头地址
	struct EdgeNode * cur;
	struct EdgeNode *tmp;
	number=pChiTree->n;
	
	for(i=0;i<number;i++){
		if(pChiTree->nodelist[i].info==parentnode){//找到父节点的位置赋给pos
			pos=i;break;
		}
	}
	//若输入错误找不到父节点，返回0
	if(pos==-1){
		printf("input error!");
		return 0;
	}
	if(number>=pChiTree->MAXNUM){
		printf("over flow!");
		return 0;
	}

	head=pChiTree->nodelist[pos].children;//把当前父节点的children子链表头地址给head
	
	//先处理nodelist
	//在nodelist中赋值，并使节点个数++
	pChiTree->nodelist[number].info=node;
	pChiTree->nodelist[number].children=NULL;//新构造的nodelist中的children置为空
	pChiTree->n++;

	//构造父节点的children子链表
	if(head==NULL){//如果head为空，表示没有子链表头地址
		head=(struct EdgeNode *)malloc(sizeof(struct EdgeNode));//申请空间
		//构造子链表的第一个节点
		head->nodeposition=number;
		head->link=NULL;

		//把构造好的head赋给 当前父节点的children子链表
		pChiTree->nodelist[pos].children=head;
		return 1;
	}

	cur=head;//将head赋给cur（current）表示当前操作的节点，避免找不到最初的head
	//找到最后一个节点
	while(cur->link!=NULL)
		cur=cur->link;
	//构造新节点tmp
	tmp=(struct EdgeNode *)malloc(sizeof(struct EdgeNode));
	tmp->nodeposition=number;
	tmp->link=NULL;
	//在最后一个节点后加上新增的节点
	cur->link=tmp;
	
	//构造完子链表head把该链表赋给当前父节点的children子链表
	pChiTree->nodelist[pos].children=head;

	return 1;//插入成功 返回1
}

/*在树的子表表示中求右兄弟结点的位置*/
int rightSibling_chitree(PChiTree t, int p) {
	int i;  struct EdgeNode *v;
	for (i = 0; i<t->n; i++) {
		v = t->nodelist[i].children;
		while (v != NULL)
			if (v->nodeposition == p)
				if (v->link == NULL)
					return(-1);
				else  
					return(v->link->nodeposition);
			else  
				v = v->link;
	}
	return(-1);
}

/*在树的子表表示上求父结点的位置*/
int parent_chitree(PChiTree t, int p) {
	int i;  struct EdgeNode  *v;
	for (i = 0; i<t->n; i++) { 	/* 逐个检查树的各个结点，是不是父结点 */
		v = t->nodelist[i].children;/* 若检查的结点子表中有p，则返回值是该结点的位置 */
		while (v != NULL)
			if (v->nodeposition == p) 
				return(i);
			else  
				v = v->link;
	}
	return(-1);  /* 无父结点，则返回值为-1 */
}

void print_chitree(PChiTree pChiTree) {
    int i,number;
	struct EdgeNode * head;//head保存每个nodelist[i]的children子链表的头地址
	number=pChiTree->n;//当前节点个数
	for(i=0;i<number;i++){
		//先输出当前节点位置和值
		printf("node %d -->value %c ",i,pChiTree->nodelist[i].info);
		head=pChiTree->nodelist[i].children;
		if(head!=NULL)//如果nodelist[i]的children子链表存在
			printf("childenLink-->");
		while(head!=NULL){//从head一步一步往下遍历到最后并输出
			printf("%d ",head->nodeposition);
			head=head->link;
		}
		printf("\n");
	}
	printf("\n");
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空的子表表示树\n");
	printf("2. 插入根结点\n");
	printf("3. 插入子结点\n");
	printf("4. 返回树的子表表示中右兄弟结点的位置\n");
	printf("5. 返回树的子表表示上父结点的位置\n");
	printf("6. 打印所有结点\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void main() {
	/**
	请在充分思考后再查看此题解，否则没有意义的，记得后果自负！！！
	*/

	//way表示操作，i循环，pos节点位置，ans记录返回的节点位置
	int way,i,pos,ans;
	char val[5],par_val[5];//用字符数组避免读空格、换行
	PChiTree root;//树的根节点
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			printf("create success!");
			root=createEmptyChildTree_seq(20);//将创建的根节点赋给root
		}
		else if(way==2){
			printf("please input the root value:");
			scanf("%s",val);//输入树根值
			insertchiTree_root(root,val[0]);
		}
		else if(way==3){
			printf("please input the parent value:");
			scanf("%s",par_val);//输入父节点的值
			printf("please input the son value:");
			scanf("%s",val);//子节点的值
			insertTree_chiTree(root,val[0],par_val[0]);//插入
		}
		else if(way==4){
			printf("please input the node index:");	
			scanf("%d",&pos);//输入要查的节点的位置（下标从0开始）
			ans=rightSibling_chitree(root,pos);//ans记录返回的右兄弟节点位置
			if(ans==-1){//如果不存在
				printf("NOT EXIST!");
				continue;//直接continue掉不会执行下面的语句
			}
			//找得到的话就输出
			printf("node %d value %c 's right----->node %d value %c ",pos,root->nodelist[pos].info,ans,root->nodelist[ans].info);
		}
		else if(way==5){
			printf("please input the node index:");	
			scanf("%d",&pos);//输入要查的节点的位置（下标从0开始）
			ans=parent_chitree(root,pos);//ans记录返回的右兄弟节点位置

			if(ans==-1){//如果不存在
				printf("NOT EXIST!");
				continue;//直接continue掉不会执行下面的语句
			}
			//找得到的话就输出
			printf("node %d value %c 's parent----->node %d value %c ",pos,root->nodelist[pos].info,ans,root->nodelist[ans].info);

		}
		else if(way==6){
			//输出
			print_chitree(root);
		}
		
	}
	
}