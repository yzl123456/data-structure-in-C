#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
/*ChiTree.c*/
/*�����ӱ��ʾ��*/

typedef int DataType;
struct  EdgeNode {   	/* �ӱ��н��Ľṹ */
	int             nodeposition;  /* �ӽ���ڽ����е�λ�� */
	struct EdgeNode  *link;       /* ָ����һ���ӱ��еĽ�� */
};

struct  ChiTreeNode {           /* �����н��Ľṹ */
	DataType         info;      /* ��㱾�����Ϣ */
	struct EdgeNode  *children; /* ������ӱ��ͷָ�� */
};

struct  ChiTree { 		/* ���ṹ */
	int    MAXNUM;      /* ������������ */
	int    root;	    /* �������±� */
	int    n; 		    /* ʵ�ʽ����� */
	struct ChiTreeNode  * nodelist;    /*���� */
};
typedef  struct  ChiTree *  PChiTree;

/* �����ӱ��ʾ���� */
PChiTree createEmptyChildTree_seq(int m) {
	PChiTree pChiTree = (PChiTree)malloc(sizeof(struct ChiTree));
	if (pChiTree != NULL) {
		pChiTree->nodelist = (struct ChiTreeNode*)malloc(sizeof(struct ChiTreeNode)*m);
		if (pChiTree->nodelist != NULL) {
			pChiTree->MAXNUM = m;
			pChiTree->n = 0;					/* �ձ���Ϊ0 */
			return (pChiTree);
		}
		else free(pChiTree);
	}
	printf("Out of space!!\n");    	/* �洢����ʧ�� */
	return NULL;
}

void insertchiTree_root(PChiTree pChiTree, char root) {
	if (pChiTree->n == 0) {
		// ������ڵ�
		pChiTree->nodelist[0].info = root;
		pChiTree->nodelist[0].children = NULL;
		pChiTree->n = 1;
	}
	else {
		printf("���ڵ��Ѿ����ڣ�");
	}
}

/*����1��ʾ����ɹ�,0��ʾ����ʧ��*/
int insertTree_chiTree(PChiTree pChiTree, char node, char parentnode) {
	int i,pos=-1,number;//iѭ����pos��¼���ڵ��λ�ã�number�ڵ����
	struct EdgeNode * head;//head��nodelist[i].children ������ͷ��ַ
	struct EdgeNode * cur;
	struct EdgeNode *tmp;
	number=pChiTree->n;
	
	for(i=0;i<number;i++){
		if(pChiTree->nodelist[i].info==parentnode){//�ҵ����ڵ��λ�ø���pos
			pos=i;break;
		}
	}
	//����������Ҳ������ڵ㣬����0
	if(pos==-1){
		printf("input error!");
		return 0;
	}
	if(number>=pChiTree->MAXNUM){
		printf("over flow!");
		return 0;
	}

	head=pChiTree->nodelist[pos].children;//�ѵ�ǰ���ڵ��children������ͷ��ַ��head
	
	//�ȴ���nodelist
	//��nodelist�и�ֵ����ʹ�ڵ����++
	pChiTree->nodelist[number].info=node;
	pChiTree->nodelist[number].children=NULL;//�¹����nodelist�е�children��Ϊ��
	pChiTree->n++;

	//���츸�ڵ��children������
	if(head==NULL){//���headΪ�գ���ʾû��������ͷ��ַ
		head=(struct EdgeNode *)malloc(sizeof(struct EdgeNode));//����ռ�
		//����������ĵ�һ���ڵ�
		head->nodeposition=number;
		head->link=NULL;

		//�ѹ���õ�head���� ��ǰ���ڵ��children������
		pChiTree->nodelist[pos].children=head;
		return 1;
	}

	cur=head;//��head����cur��current����ʾ��ǰ�����Ľڵ㣬�����Ҳ��������head
	//�ҵ����һ���ڵ�
	while(cur->link!=NULL)
		cur=cur->link;
	//�����½ڵ�tmp
	tmp=(struct EdgeNode *)malloc(sizeof(struct EdgeNode));
	tmp->nodeposition=number;
	tmp->link=NULL;
	//�����һ���ڵ����������Ľڵ�
	cur->link=tmp;
	
	//������������head�Ѹ���������ǰ���ڵ��children������
	pChiTree->nodelist[pos].children=head;

	return 1;//����ɹ� ����1
}

/*�������ӱ��ʾ�������ֵܽ���λ��*/
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

/*�������ӱ��ʾ���󸸽���λ��*/
int parent_chitree(PChiTree t, int p) {
	int i;  struct EdgeNode  *v;
	for (i = 0; i<t->n; i++) { 	/* ���������ĸ�����㣬�ǲ��Ǹ���� */
		v = t->nodelist[i].children;/* �����Ľ���ӱ�����p���򷵻�ֵ�Ǹý���λ�� */
		while (v != NULL)
			if (v->nodeposition == p) 
				return(i);
			else  
				v = v->link;
	}
	return(-1);  /* �޸���㣬�򷵻�ֵΪ-1 */
}

void print_chitree(PChiTree pChiTree) {
    int i,number;
	struct EdgeNode * head;//head����ÿ��nodelist[i]��children�������ͷ��ַ
	number=pChiTree->n;//��ǰ�ڵ����
	for(i=0;i<number;i++){
		//�������ǰ�ڵ�λ�ú�ֵ
		printf("node %d -->value %c ",i,pChiTree->nodelist[i].info);
		head=pChiTree->nodelist[i].children;
		if(head!=NULL)//���nodelist[i]��children���������
			printf("childenLink-->");
		while(head!=NULL){//��headһ��һ�����±�����������
			printf("%d ",head->nodeposition);
			head=head->link;
		}
		printf("\n");
	}
	printf("\n");
}

void printScreen() {
	printf("\n*************************\n");
	printf("1. �����յ��ӱ��ʾ��\n");
	printf("2. ��������\n");
	printf("3. �����ӽ��\n");
	printf("4. ���������ӱ��ʾ�����ֵܽ���λ��\n");
	printf("5. ���������ӱ��ʾ�ϸ�����λ��\n");
	printf("6. ��ӡ���н��\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	/**
	���ڳ��˼�����ٲ鿴����⣬����û������ģ��ǵú���Ը�������
	*/

	//way��ʾ������iѭ����pos�ڵ�λ�ã�ans��¼���صĽڵ�λ��
	int way,i,pos,ans;
	char val[5],par_val[5];//���ַ����������ո񡢻���
	PChiTree root;//���ĸ��ڵ�
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			printf("create success!");
			root=createEmptyChildTree_seq(20);//�������ĸ��ڵ㸳��root
		}
		else if(way==2){
			printf("please input the root value:");
			scanf("%s",val);//��������ֵ
			insertchiTree_root(root,val[0]);
		}
		else if(way==3){
			printf("please input the parent value:");
			scanf("%s",par_val);//���븸�ڵ��ֵ
			printf("please input the son value:");
			scanf("%s",val);//�ӽڵ��ֵ
			insertTree_chiTree(root,val[0],par_val[0]);//����
		}
		else if(way==4){
			printf("please input the node index:");	
			scanf("%d",&pos);//����Ҫ��Ľڵ��λ�ã��±��0��ʼ��
			ans=rightSibling_chitree(root,pos);//ans��¼���ص����ֵܽڵ�λ��
			if(ans==-1){//���������
				printf("NOT EXIST!");
				continue;//ֱ��continue������ִ����������
			}
			//�ҵõ��Ļ������
			printf("node %d value %c 's right----->node %d value %c ",pos,root->nodelist[pos].info,ans,root->nodelist[ans].info);
		}
		else if(way==5){
			printf("please input the node index:");	
			scanf("%d",&pos);//����Ҫ��Ľڵ��λ�ã��±��0��ʼ��
			ans=parent_chitree(root,pos);//ans��¼���ص����ֵܽڵ�λ��

			if(ans==-1){//���������
				printf("NOT EXIST!");
				continue;//ֱ��continue������ִ����������
			}
			//�ҵõ��Ļ������
			printf("node %d value %c 's parent----->node %d value %c ",pos,root->nodelist[pos].info,ans,root->nodelist[ans].info);

		}
		else if(way==6){
			//���
			print_chitree(root);
		}
		
	}
	
}