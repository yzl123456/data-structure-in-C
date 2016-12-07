#pragma warning(disable:4996)

/* HashDictionary.c*/
/*�ֵ��ɢ�б�ʾ*/


#include <stdio.h>
#include <stdlib.h>
typedef  int		KeyType;
typedef  int		DataType;
typedef struct {
	KeyType key;				/* �ֵ�Ԫ�صĹؼ����ֶ�	*/
	DataType value;			/* �ֵ�Ԫ�ص������ֶ�	*/
}DicElement;

typedef struct
{
	int m;					/* mΪ�������򳤶� */
	DicElement *element;
} HashDictionary;

int m;

/*������ɢ�б�*/
HashDictionary* createEmptyDictionary(int m) {
	int i;
	HashDictionary* phd = (HashDictionary*)malloc(sizeof(HashDictionary));
	if (phd != NULL) {
		phd->element = (DicElement *)malloc(sizeof(DicElement)*m);
		if (phd->element) {
			phd->m = m;
			for (i = 0; i<m; i++)
				phd->element[i].key = 0;   /*��ʼ��*/
			return (phd);
		}
		else
			free(phd);
	}
	printf("Out of space!!\n");    	/* �洢����ʧ�� */
	return NULL;
}

int h(KeyType key) {
	return key%m;
}

/*ɢ�б�ļ����㷨��������̽�鷨�����ײ*/
int linearSearch(HashDictionary * phash, KeyType key, int *position) {
	int d, inc;
	d = h(key);				/* dΪɢ�е�ַ��ɢ�к���Ϊh(key) */
	for (inc = 0; inc<phash->m; inc++) {
		if (phash->element[d].key == key) {
			*position = d;					/* �����ɹ� */
			return(1);
		}
		else if (phash->element[d].key == 0) {
			*position = d;					/* ����ʧ�ܣ��ҵ�����λ�� */
			return(0);
		}
		d = (d + 1) % phash->m;
	}
	*position = -1;						/* ɢ�б���� */
	return(0);
}

/*ɢ�б�Ĳ����㷨��������̽�鷨�����ײ*/
int linearInsert(HashDictionary *phash, DicElement ele) {
	int position;
	/*ɢ�б������йؼ���Ϊkey�Ľ�� */
	if (linearSearch(phash, ele.key, &position) == 1)
		printf("Find\n");
	else if (position != -1)
		phash->element[position] = ele;		/* ������*/
	else  
		return(0);						/* ɢ�б���� */
	return(1);
}

void printHashDirectionary(HashDictionary *phash) {
	int i;
	for(i=0;i<phash->m;i++){//��ͷ��β���δ�ӡÿ��key
		printf("%d ",phash->element[i].key);
	}
	printf("\n");
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. ����ɢ�б�\n");
	printf("2. ɢ�б��в���ؼ��뼯��\n");
	printf("3. ��ӡɢ�б��еĹؼ���\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
    int way,x;
	HashDictionary* phash;//Hash��
	DicElement* tmp;//����½ڵ�
	while(1){
		scanf("%d",&way);
		if(way==1){
			scanf("%d",&m);
			phash=createEmptyDictionary(m);//����
		}
		else if(way==2){
			while(1){
				scanf("%d",&x);//����
				if(x==0) break;
				tmp=(DicElement* )malloc(sizeof( DicElement));//�����½ڵ�
				tmp->key=x;tmp->value=h(x);//��ֵ
				linearInsert(phash,*tmp);//����
			}
		}
		else if(way==3){
			printHashDirectionary(phash);//��ӡ
		}
	}

}