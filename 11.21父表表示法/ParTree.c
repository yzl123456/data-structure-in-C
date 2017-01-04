#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

/*ParTree.c*/
/*树的父指针表示法*/
typedef char DataType;

struct ParTreeNode {
	DataType  info;		/* 结点中的元素 */
	int       parent;	/* 结点的父结点位置 */
};

struct  ParTree {
	int       MAXNUM;                 /* 树中最大结点个数 */
	int       n;              	      /* 树中已有结点的个数 */
	struct ParTreeNode * nodelist;    /* 存放树中结点的数组 */
};
typedef  struct  ParTree  * PParTree; /* 树类型的指针类型 * /


/* 创建新的顺序表 */
PParTree createEmptyParTree_seq(int m) {
	PParTree pParTree = (PParTree)malloc(sizeof(struct ParTree));
	if (pParTree != NULL) {
		pParTree->nodelist = (struct ParTreeNode*)malloc(sizeof(struct ParTreeNode)*m);
		if (pParTree->nodelist!=NULL) {
			pParTree->MAXNUM = m;
			pParTree->n = 0;					/* 空表长度为0 */
			return (pParTree);
		}
		else free(pParTree);
	}
	printf("Out of space!!\n");    	/* 存储分配失败 */
	return NULL;
}

int isParTreeNull(PParTree pParTree) {
	if (pParTree->n == 0)
		return 1;
	else
		return 0;
}

void insertparTree_root(PParTree pParTree, char root) {
	if (pParTree->n == 0) {
		// 插入根节点
		pParTree->nodelist[0].info = root;
		pParTree->nodelist[0].parent = -1;
		pParTree->n = 1;
	}
	else {
		printf("根节点已经存在！");
	}
}

int insertTree_parTree(PParTree pParTree, char node, char parentnode) {
	//i用来循环，number表示nodelist中的个数，par_pos记录父节点对应值在数组中的下标
	int i,number=pParTree->n,par_pos=-1;
	//循环找到父节点对应在数组的下标
	for(i=0;i<number;i++){
		if(pParTree->nodelist[i].info==parentnode){
			par_pos=i;break;
		}
	}

	//构建新节点，新节点的下标为number
	pParTree->nodelist[number].info=node;
	pParTree->nodelist[number].parent=par_pos;

	//树中节点个数+1
	pParTree->n++;
}

/*在父指针表示的树中求右兄弟结点的位置*/
int rightSibling_partree(PParTree t, int p) {
	int i;
	if (p >= 0 && p<t->n)
		for (i = p + 1; i<t->n; i++)
			if (t->nodelist[i].parent == t->nodelist[p].parent)  
				return(i);
	return(-1);
}

/*在父指针表示的树中求最左子结点的位置*/
int leftChild_partree(PParTree t, int p) {
    if (t->nodelist[p + 1].parent == p)  
		return(p + 1);
    else  
        return(-1);
}

/*在父指针表示的树中求最左子结点的位置*/
int leftChild_partree_improve(PParTree pParTree, int p) {
	int  i;
	for (i = p+1; i<pParTree->n; i++) {
		if (pParTree->nodelist[i].parent == p)
		    return i;
	}
	return(-1);
}

void print_partree(PParTree pParTree) {
	int  i;
	for (i = 0; i < pParTree->n; i++) {
		printf("位置%d %c %d\n", i, pParTree->nodelist[i].info, pParTree->nodelist[i].parent);
	}
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空的父指针表示树\n");
	printf("2. 插入根结点\n");
	printf("3. 插入子结点\n");
	printf("4. 返回树中右兄弟结点和位置\n");
	printf("5. 返回树中最左子结点和位置\n");
	printf("6. 打印所有结点\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void main() {
	PParTree root;
	int way,pos,ans;
	char s[5],par[5];//利用数组不读空格，避免getchar
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			//创建树的根节点
			root=createEmptyParTree_seq(20);
		}
		else if(way==2){
			//输入根节点
			printf("please input root value:");
			scanf("%s",s);
			//插入
			insertparTree_root(root,s[0]);
		}
		else if(way==3){
			//输入父节点和子节点
			printf("please input parent node:");
			scanf("%s",par);
			printf("please input son node:");
			scanf("%s",s);
			//插入节点
			insertTree_parTree(root,s[0],par[0]);
		}

		else if(way==4){
			//输入节点的位置（下标）
			printf("please input the node index:");
			scanf("%d",&pos);
			//得到最右兄弟的下标ans
			ans=rightSibling_partree(root,pos);
			if(ans==-1){//若返回-1则表示不存在，直接continue掉
				printf("not exist!");continue;
			}
			printf("index-->%d  node value-->%c",ans,root->nodelist[ans]);
		}
		else if(way==5){
			//输入节点的位置（下标）
			printf("please input the node index:");
			scanf("%d",&pos);
			//得到最右兄弟的下标ans
			//注意此处的第二个参数为root->nodelist[pos].parent
			//因为在leftChild_partree中是判断(t->nodelist[p + 1].parent == p) ，所以传进去的参数应该是当前下标节点的父节点
			ans=leftChild_partree(root,root->nodelist[pos].parent);
			if(ans==-1){//若返回-1则表示不存在，直接continue掉
				printf("not exist!");continue;
			}
			printf("index-->%d  node value-->%c",ans,root->nodelist[ans]);
		}
		else if(way==6){
			//输出
			print_partree(root);
		}
		else if(way==0){
			return ;
		}
	}
}