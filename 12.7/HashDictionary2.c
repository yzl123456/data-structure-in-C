#pragma warning(disable:4996)
/* HashDictionary.c*/
/*�ֵ��ɢ�б�ʾ*/


#include <stdio.h>
#include <stdlib.h>
typedef  int		KeyType;
typedef  int		DataType;

struct DicElement;

typedef struct DicElement *LinkElement;

struct DicElement {
	KeyType key;				/* �ֵ�Ԫ�صĹؼ����ֶ�	*/
	DataType value;			/* �ֵ�Ԫ�ص������ֶ�	*/
	LinkElement next;
};



typedef struct
{
	int m;					/* mΪ�������򳤶� */
	LinkElement *element;
} HashDictionary;

int m;

/*������ɢ�б�*/
HashDictionary* createEmptyDictionary(int m) {
	int i;

	HashDictionary* phd = (HashDictionary*)malloc(sizeof(HashDictionary));
	if (phd != NULL) {
		phd->element = (LinkElement*)malloc(sizeof(LinkElement)*m);
		if (phd->element) {
			phd->m = m;
			for (i = 0; i<m; i++) {
				phd->element[i] = NULL;

			}
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

/*ɢ�б�ļ���*/
int linearSearch(HashDictionary *phash, KeyType key){
    int d;
    LinkElement p;
    d = h(key);
	if(phash->element[d]==NULL)
		return(0);
	if(phash->element[d]->key==key){
        return (1);
    }
    else{
		p = phash->element[d]->next;
        while(p!=NULL){
            if(p->key == key)
                return (1);
            else
                p = p->next;
        }
    }
    return(0);
}

/*ɢ�б�Ĳ����㷨*/
int linearInsert(HashDictionary *phash, LinkElement ele) {
	int d;
	LinkElement p;
	d = h(ele->key);
	if (phash->element[d] == NULL) {
		phash->element[d] = ele;
		return (1);
	}
	else {
		p = phash->element[d];
		while (p != NULL) {
			if (p->next == NULL) {
				p->next = ele;
				break;
			}
			p = p->next;
		}
	}
	return(0);
}

void printHashDirectionary(HashDictionary *phash) {
    int i;
	LinkElement tmp;//���һ����ַ�ռ�ָ�������ͷ���
	for(i=0;i<phash->m;i++){
		printf("[%d]  ",i);
		tmp=phash->element[i];//�õ�ͷ���
		while(tmp!=NULL){
			printf("%d ",tmp->key);//����
			tmp=tmp->next;
		}
		printf("\n");
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. ����ɢ�б�\n");
	printf("2. ɢ�б��в���ؼ��뼯��\n");
	printf("3. ���ݹؼ������ɢ�б�\n");
	printf("4. ��ӡɢ�б��еĹؼ���\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
    int way,x,key,res;
	HashDictionary* phash;//hash��
	LinkElement tmp;//����½����Ľڵ�
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
				tmp=(LinkElement )malloc(sizeof(struct DicElement));//�����½ڵ�
				tmp->key=x;tmp->value=h(x);tmp->next=NULL;//��ֵ
				linearInsert(phash,tmp);//����
			}
		}
		else if(way==3){
			scanf("%d",&key);//����
			res=linearSearch(phash,key);//����
			if(res==0) printf("not found\n");
			else printf("find is ok!\n");

		}
		else if(way==4){
			printHashDirectionary(phash);//��ӡ
		}
	}
}