#include <stdio.h>
#include <stdlib.h>

/*LinkBinTree.c*/
/*�����������ӱ�ʾ����-��ָ���ʾ��*/


typedef char DataType;

//struct BinTreeNode;	/* �������н�� */
typedef  struct BinTreeNode	 * PBinTreeNode;	/* ����ָ������ */
struct BinTreeNode {
	DataType  info;	/* ������ */
	PBinTreeNode  llink;	/* ָ�����ӽ�� */
	PBinTreeNode  rlink;	/* ָ�����ӽ�� */
};
typedef  struct BinTreeNode  *BinTree;
typedef  BinTree  *PBinTree;
PBinTreeNode root;//ȫ�ֱ�����ʾ���ڵ�
PBinTreeNode pos;//ȫ�ֱ�����¼��Ӧֵ�Ƿ���ڶ�Ӧ�ĸ��ڵ�
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


/*���ؽ��p�����ӽ��ĵ�ַ*/
PBinTreeNode leftChild_link(PBinTreeNode p) {

	if (p == NULL) 
		return NULL;
	return p->llink;
}

/*���ؽ��p�����ӽ��ĵ�ַ*/
PBinTreeNode rightChild_link(PBinTreeNode p) {
	if (p == NULL) 
		return NULL;
	return p->rlink;
}



/*������������*/

/*�������ȸ��������εĵݹ��㷨*/
void preOrder(BinTree  t) {
	if (t == NULL) 
		return;
	//visit(root(t));
	visit(t);
	preOrder(leftChild_link(t));
	preOrder(rightChild_link(t));
}

/*�������Գ������εĵݹ��㷨*/
void inOrder(BinTree  t) {
	if (t == NULL) 
		return;

	inOrder(leftChild_link(t));
	//visit(root(t));
	visit(t);

	inOrder(rightChild_link(t));
}

/*����������������εĵݹ��㷨*/
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
	printf("1. ����ֵ������\n");
	printf("2. �ȸ��������\n");
	printf("3. �Գƴ������\n");
	printf("4. ����������\n");
	printf("0. �˳�\n");
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
	tmp->llink=NULL;tmp->rlink=NULL;tmp->info=c;//����ڵ�

	if(dir=='l')//ѡ����
		t->llink=tmp;
	else if(dir=='r')
		t->rlink=tmp;
	else printf("Input Error!");
}

void prepareInsert(){//����ǰ
	char dir[3],insert_value[3],root_value[3];
	printf("Input the root:");//���ڵ��ֵ
	scanf("%s",root_value);
	find(root,root_value[0]);//���ҵ�ǰֵ����Ӧ�ĸ��ڵ�
	if(pos==NULL){//���Ҳ���
		printf("input error!");
	}
	else{
		printf("input the inserted value:");
		scanf("%s",insert_value);//Ҫ����Ľڵ��ֵ
		printf("input the direction('l' means 'left' , 'r' means 'right'):");
		scanf("%s",dir);//����
		insert(pos,insert_value[0],dir[0]);//����
	}

}


void main() {
	int way;char tmp[3];
	root=(PBinTreeNode )malloc(sizeof(struct BinTreeNode));
	root->llink=NULL;root->rlink=NULL;//����յĸ��ڵ�

	printf("please input the root:");
	scanf("%s",tmp);//%s������ո� ����
	root->info=tmp[0];//���ڵ㸳ֵ
	
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			pos=NULL;//posΪȫ�ֱ�����ÿ�β���ǰ�ҵ�Ҫ����ĸ��ڵ㣬���Ҳ�������Ϊ��
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