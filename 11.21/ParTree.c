#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

/*ParTree.c*/
/*���ĸ�ָ���ʾ��*/
typedef char DataType;

struct ParTreeNode {
	DataType  info;		/* ����е�Ԫ�� */
	int       parent;	/* ���ĸ����λ�� */
};

struct  ParTree {
	int       MAXNUM;                 /* ������������ */
	int       n;              	      /* �������н��ĸ��� */
	struct ParTreeNode * nodelist;    /* ������н������� */
};
typedef  struct  ParTree  * PParTree; /* �����͵�ָ������ * /


/* �����µ�˳��� */
PParTree createEmptyParTree_seq(int m) {
	PParTree pParTree = (PParTree)malloc(sizeof(struct ParTree));
	if (pParTree != NULL) {
		pParTree->nodelist = (struct ParTreeNode*)malloc(sizeof(struct ParTreeNode)*m);
		if (pParTree->nodelist!=NULL) {
			pParTree->MAXNUM = m;
			pParTree->n = 0;					/* �ձ���Ϊ0 */
			return (pParTree);
		}
		else free(pParTree);
	}
	printf("Out of space!!\n");    	/* �洢����ʧ�� */
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
		// ������ڵ�
		pParTree->nodelist[0].info = root;
		pParTree->nodelist[0].parent = -1;
		pParTree->n = 1;
	}
	else {
		printf("���ڵ��Ѿ����ڣ�");
	}
}

int insertTree_parTree(PParTree pParTree, char node, char parentnode) {
	//i����ѭ����number��ʾnodelist�еĸ�����par_pos��¼���ڵ��Ӧֵ�������е��±�
	int i,number=pParTree->n,par_pos=-1;
	//ѭ���ҵ����ڵ��Ӧ��������±�
	for(i=0;i<number;i++){
		if(pParTree->nodelist[i].info==parentnode){
			par_pos=i;break;
		}
	}

	//�����½ڵ㣬�½ڵ���±�Ϊnumber
	pParTree->nodelist[number].info=node;
	pParTree->nodelist[number].parent=par_pos;

	//���нڵ����+1
	pParTree->n++;
}

/*�ڸ�ָ���ʾ�����������ֵܽ���λ��*/
int rightSibling_partree(PParTree t, int p) {
	int i;
	if (p >= 0 && p<t->n)
		for (i = p + 1; i<t->n; i++)
			if (t->nodelist[i].parent == t->nodelist[p].parent)  
				return(i);
	return(-1);
}

/*�ڸ�ָ���ʾ�������������ӽ���λ��*/
int leftChild_partree(PParTree t, int p) {
    if (t->nodelist[p + 1].parent == p)  
		return(p + 1);
    else  
        return(-1);
}

/*�ڸ�ָ���ʾ�������������ӽ���λ��*/
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
		printf("λ��%d %c %d\n", i, pParTree->nodelist[i].info, pParTree->nodelist[i].parent);
	}
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. �����յĸ�ָ���ʾ��\n");
	printf("2. ��������\n");
	printf("3. �����ӽ��\n");
	printf("4. �����������ֵܽ���λ��\n");
	printf("5. �������������ӽ���λ��\n");
	printf("6. ��ӡ���н��\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	PParTree root;
	int way,pos,ans;
	char s[5],par[5];//�������鲻���ո񣬱���getchar
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			//�������ĸ��ڵ�
			root=createEmptyParTree_seq(20);
		}
		else if(way==2){
			//������ڵ�
			printf("please input root value:");
			scanf("%s",s);
			//����
			insertparTree_root(root,s[0]);
		}
		else if(way==3){
			//���븸�ڵ���ӽڵ�
			printf("please input parent node:");
			scanf("%s",par);
			printf("please input son node:");
			scanf("%s",s);
			//����ڵ�
			insertTree_parTree(root,s[0],par[0]);
		}

		else if(way==4){
			//����ڵ��λ�ã��±꣩
			printf("please input the node index:");
			scanf("%d",&pos);
			//�õ������ֵܵ��±�ans
			ans=rightSibling_partree(root,pos);
			if(ans==-1){//������-1���ʾ�����ڣ�ֱ��continue��
				printf("not exist!");continue;
			}
			printf("index-->%d  node value-->%c",ans,root->nodelist[ans]);
		}
		else if(way==5){
			//����ڵ��λ�ã��±꣩
			printf("please input the node index:");
			scanf("%d",&pos);
			//�õ������ֵܵ��±�ans
			//ע��˴��ĵڶ�������Ϊroot->nodelist[pos].parent
			//��Ϊ��leftChild_partree�����ж�(t->nodelist[p + 1].parent == p) �����Դ���ȥ�Ĳ���Ӧ���ǵ�ǰ�±�ڵ�ĸ��ڵ�
			ans=leftChild_partree(root,root->nodelist[pos].parent);
			if(ans==-1){//������-1���ʾ�����ڣ�ֱ��continue��
				printf("not exist!");continue;
			}
			printf("index-->%d  node value-->%c",ans,root->nodelist[ans]);
		}
		else if(way==6){
			//���
			print_partree(root);
		}
		else if(way==0){
			return ;
		}
	}
}