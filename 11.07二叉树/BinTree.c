#include <stdio.h>
#include <stdlib.h>

/*LinkBinTree.c*/
/*二叉树的链接表示：左-右指针表示法*/


typedef char DataType;

//struct BinTreeNode;	/* 二叉树中结点 */
typedef  struct BinTreeNode	 * PBinTreeNode;	/* 结点的指针类型 */
struct BinTreeNode {
	DataType  info;	/* 数据域 */
	PBinTreeNode  llink;	/* 指向左子结点 */
	PBinTreeNode  rlink;	/* 指向右子结点 */
};
typedef  struct BinTreeNode  *BinTree;
typedef  BinTree  *PBinTree;
PBinTreeNode root;//全局变量表示根节点
PBinTreeNode pos;//全局变量记录对应值是否存在对应的根节点
void visit(BinTree t){
	printf("%c ",t->info);
}
/*
void create(PBinTreeNode *root){
	int data,x=0;
	scanf("%d",&data);
	if(data==0)
		*root=NULL;
	else{ 
		*root=(PBinTreeNode)malloc(sizeof(struct BinTreeNode));
		(*root)->info=data;

		create(&(*root)->llink);
		create(&(*root)->rlink);
	}
	return ;
}*/


/*返回结点p的左子结点的地址*/
PBinTreeNode leftChild_link(PBinTreeNode p) {

	if (p == NULL) 
		return NULL;
	return p->llink;
}

/*返回结点p的右子结点的地址*/
PBinTreeNode rightChild_link(PBinTreeNode p) {
	if (p == NULL) 
		return NULL;
	return p->rlink;
}



/*二叉树的周游*/

/*二叉树先根次序周游的递归算法*/
void preOrder(BinTree  t) {
	if (t == NULL) 
		return;
	//visit(root(t));
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*二叉树对称序周游的递归算法*/
void inOrder(BinTree  t) {
	if (t == NULL) 
		return;

	inOrder(leftChild_link(t));
	//visit(root(t));
	visit(t);

	inOrder(rightChild_link(t));
}

/*二叉树后根次序周游的递归算法*/
void postOrder(BinTree  t) {
	if (t == NULL) 
		return;
	postOrder(leftChild_link(t));
	postOrder(rightChild_link(t));
	//visit(root(t));
	visit(t);
}



void printScreen() {
	printf("\n*************************\n");
	printf("1. 插入值进入树\n");
	printf("2. 先根次序遍历\n");
	printf("3. 对称次序遍历\n");
	printf("4. 后根次序遍历\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void find(BinTree t,char c){
	if(t==NULL)
		return ;
	if(t->info==c){
		pos=t;return ;
	}
	find(t->llink,c);
	find(t->rlink,c);
	return ;
}

void insert(BinTree t,char c,char dir){
	PBinTreeNode tmp=(PBinTreeNode )malloc(sizeof(struct BinTreeNode));
	tmp->llink=NULL;tmp->rlink=NULL;tmp->info=c;//构造节点

	if(dir=='l')//选择方向
		t->llink=tmp;
	else if(dir=='r')
		t->rlink=tmp;
	else printf("Input Error!");
}

void prepareInsert(){//插入前
	char dir[3],insert_value[3],root_value[3];
	printf("Input the root:");//根节点的值
	scanf("%s",root_value);
	find(root,root_value[0]);//查找当前值所对应的根节点
	if(pos==NULL){//若找不到
		printf("input error!");
	}
	else{
		printf("input the inserted value:");
		scanf("%s",insert_value);//要插入的节点的值
		printf("input the direction('l' means 'left' , 'r' means 'right'):");
		scanf("%s",dir);//方向
		insert(pos,insert_value[0],dir[0]);//插入
	}

}


void main() {
	int way;char tmp[3];
	root=(PBinTreeNode )malloc(sizeof(struct BinTreeNode));
	root->llink=NULL;root->rlink=NULL;//构造空的根节点

	printf("please input the root:");
	scanf("%s",tmp);//%s避免读空格 换行
	root->info=tmp[0];//根节点赋值
	
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			pos=NULL;//pos为全局变量，每次插入前找到要插入的根节点，若找不到，则为空
			prepareInsert();//insert
		}
		else if(way==2){
			preOrder(root);
		}
		else if(way==3){
			inOrder(root);
		}
		else if(way==4){
			postOrder(root);
		}
		else if(way==0){
			break ;
		}
	}
	
	
}