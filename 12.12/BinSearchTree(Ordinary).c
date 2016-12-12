#pragma warning(disable:4996)
/*BinSearchTree.c*/
/*����������*/

#include <stdio.h>
#include <stdlib.h>
struct BinSearchNode;
typedef struct BinSearchNode * PBinSearchNode;
typedef int KeyType;
typedef int DataType;


typedef struct {
	KeyType key;				/* �ֵ�Ԫ�صĹؼ����ֶ�	*/
	DataType value;			    /* �ֵ�Ԫ�ص������ֶ�	*/
}DicElement;

typedef struct {
	int MAXNUM; 		/*�ֵ���Ԫ�صĸ����Ͻ�*/
	int n;					/*Ϊ�ֵ���ʵ��Ԫ�صĸ��� */
	DicElement *element; 		 /*����ֵ��е�Ԫ��*/
} SeqDictionary;

struct BinSearchNode {
	KeyType key;					/* ���Ĺؼ����ֶ� */
	PBinSearchNode llink, rlink;		/* ������������ָ�� */
};
typedef struct BinSearchNode * BinSearchTree;	/*����������	*/
typedef BinSearchTree * PBinSearchTree;
SeqDictionary* create(int m){//���������ֵ�
	SeqDictionary* node=(SeqDictionary *)malloc(sizeof(SeqDictionary));
	node->MAXNUM=m;
	node->n=0;
	node->element=(DicElement *)malloc(sizeof(DicElement)*m);
	return node;
}
int insertDictionary(SeqDictionary * pdic, KeyType key, DataType value) {
	int i,number=pdic->n;
	if (pdic->n >= pdic->MAXNUM) {   /* ��� */
		printf("Overflow!\n");
		return (0);
	}
	if (pdic->n == 0) {                    /*��˳������ */
		pdic->element[0].key = key;        /* ����Key */
		pdic->element[0].value = value;    /* ����value */
		pdic->n = 1;                       /* Ԫ�ظ���Ϊ1 */
		return (1);
	}

	pdic->element[number].key = key;        /* ����Key */
	pdic->element[number].value = value;    /* ����value */
	pdic->n = pdic->n + 1;                /* Ԫ�ظ�����1 */
	return (1);
}

/*�����������ļ����㷨*/
int search(PBinSearchTree ptree, KeyType key, PBinSearchNode *position) {
	PBinSearchNode p, q;
	p = *ptree;  q = p;
	while (p != NULL) {
		q = p; 		/* ��q��¼������λ�� */
		if (p->key == key) { 
			*position = p;  
			return(1); 
		}		/* �����ɹ� */
		else if (p->key>key)	  
			p = p->llink;			/* ������������������ */
		else	
			p = p->rlink;			/* ������������������ */
	}
	*position = q;  
	return(0);					/* ����ʧ�� */
}

/*�����������в�����*/
int insert(PBinSearchTree ptree, KeyType key) {
	PBinSearchNode p, position;
	if (search(ptree, key, &position) == 1) 
		return 1;   /* �Ѵ��ڹؼ���Ϊkey�Ľ�� */
	p = (PBinSearchNode)malloc(sizeof(struct BinSearchNode));/* �����½�� */
	/* ����ռ���� */
	if (p == NULL) { 
		printf("Error\n");  return 0; 
	}	
	/* ���½��ĸ�ֵ */
	p->key = key;	
	p->llink = p->rlink = NULL;		
	/* ԭ��Ϊ���� */
	if (position == NULL)	
		*ptree = p;					
	else if (key<position->key) 
		position->llink = p;	  /* ����position�������� */
	else  
		position->rlink = p;				/* ����position�������� */
	return 1;
}

/*�����������Ĺ���*/
int creatSearchTree(PBinSearchTree ptree, SeqDictionary *dic) {
	int i;
	*ptree = NULL; 			/* �������������ÿ� */
	for (i = 0; i<dic->n; i++)
		if (!insert(ptree, dic->element[i].key)) 
			return 0;			/* ���½��������� */
	return 1;
}

/*������������ɾ��*/
int delete(PBinSearchTree ptree, KeyType key) {
	PBinSearchNode parentp, p, r;
	p = *ptree;  parentp = NULL;
	while (p != NULL) {
		if (p->key == key)  
			break;				/* �ҵ��˹ؼ���Ϊkey�Ľ�� */
		parentp = p;
		if (p->key>key)  
			p = p->llink;			/* ���������� */
		else  
			p = p->rlink;						/* ���������� */
	}
	if (p == NULL)  
		return 0;					/* �������������޹ؼ���Ϊkey�Ľ�� */
	if (p->llink == NULL) { 					/* ���*p�������� */
		/* ��ɾ���Ľ����ԭ�����������ĸ����*/
		if (parentp == NULL) 
			*ptree = p->rlink;		
		else if (parentp->llink == p)	
			parentp->llink = p->rlink;	/*��*p�������������丸��������*/
		else	
			parentp->rlink = p->rlink;	/* ��*p�������������丸���������� */
	}
	else {								/* ���*p�������� */
		r = p->llink;
		while (r->rlink != NULL)  
			r = r->rlink;		/* ��*p�����������������½��*r */
		r->rlink = p->rlink;	/* ��*r����ָ��ָ��*p������Ů */
		if (parentp == NULL)  
			*ptree = p->llink;
		else if (parentp->llink == p)	
			parentp->llink = p->llink;	/* ��*p������Ů����*p */
		else	 
			parentp->rlink = p->llink;
	}
	free(p);  
	return 1;									/* �ͷű�ɾ����� */
}

void printDictionary(SeqDictionary * pdic) {
	int i;
	for(i=0;i<pdic->n;i++){//��ӡ
		printf("key: %d  value:%d\n",pdic->element[i].key,pdic->element[i].value);
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. �����ֵ�\n");
	printf("2. �����������в�����(��������)\n");
	printf("3. �����������м���Key(�ؼ���)\n");
	printf("4. ɾ�������������еĽ��\n");
	printf("5. ��ӡ�ֵ�\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
	int way,key,val,res,x;//res������Ľ��
	SeqDictionary* dic=NULL;
	PBinSearchTree root=(PBinSearchTree)malloc(sizeof(struct BinSearchNode));//���ڵ�
	PBinSearchNode pos=(PBinSearchNode)malloc(sizeof(struct BinSearchNode));//pos����������Ǹ�ָ��ڵ�
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			dic=create(50);//����
			while(1){
				printf("input the key:");
				scanf("%d",&key);//����
				if(key==0) break;
				printf("input the value:");
				scanf("%d",&val);
				insertDictionary(dic,key,val);//�����ֵ�
			}
		}
		else if(way==2){
			creatSearchTree(root,dic);//����
		}
		else if(way==3){
			printf("input the key you want:");
			scanf("%d",&x);
			res=search(root,x,&pos);//���ң�ע������Ҫ��&pos���βΣ���Ȼ��posҲ�����С�����
			if(res!=0) printf("find is ok!");
			else printf("not find!");
		}
		else if(way==4){
			printf("input the key you want to delete:");
			scanf("%d",&x);
			res=delete(root,x);//ɾ��
			if(res!=0) printf("delete is ok!");
			else printf("delete defeat!");
		}
		else if(way==5){
			printDictionary(dic);//��ӡ
		}
	}
}