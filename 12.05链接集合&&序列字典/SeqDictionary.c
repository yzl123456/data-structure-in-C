#pragma warning(disable: 4996)
/* SeqDictionary.c*/
/*�ֵ��˳���ʾ��ʽ*/

#include<stdio.h>
#include<stdlib.h>

typedef  int		KeyType;
typedef  int		DataType;
typedef struct {
	KeyType key;				/* �ֵ�Ԫ�صĹؼ����ֶ�	*/
	DataType value;			    /* �ֵ�Ԫ�ص������ֶ�	*/
}DicElement;

typedef struct {
	int MAXNUM; 		/*�ֵ���Ԫ�صĸ����Ͻ�*/
	int n;					/*Ϊ�ֵ���ʵ��Ԫ�صĸ��� */
	DicElement *element; 		 /*����ֵ��е�Ԫ��*/
} SeqDictionary;
SeqDictionary* create(int m){
	//�����ֵ伯��
	SeqDictionary* node=(SeqDictionary *)malloc(sizeof(SeqDictionary));
	node->MAXNUM=m;
	node->n=0;
	node->element=(DicElement *)malloc(sizeof(DicElement)*m);
	return node;
}
/*˳������㷨*/
int seqSearch(SeqDictionary * pdic, KeyType key, int * position) {
	/*���ֵ���˳������ؼ���Ϊkey��Ԫ��*/
	int i;
	for (i = 0; i<pdic->n; i++)			/* ��ͷ��ʼ���ɨ��	*/
		if (pdic->element[i].key == key)
		{
			*position = i;
			return(1);
		}	/* �����ɹ� */

	*position = pdic->n;
	return(0);				/* ����ʧ�� */
}

/* ���ֵ����ö��ַ����ҹؼ���Ϊkey��Ԫ�� */
int binarySearch(SeqDictionary * pdic, KeyType key, int *position) {
	int low, mid, high;
	low = 0;  high = pdic->n - 1;
	while (low <= high) {
		mid = (low + high) / 2;							/* ��ǰ�������м�λ�� */
		if (pdic->element[mid].key == key) {
			*position = mid;  
			return(1);
		}	/* �����ɹ� */
		else if (pdic->element[mid].key>key)
			high = mid - 1;	        /* Ҫ������Ԫ��������� */
		else  low = mid + 1;		 /* Ҫ������Ԫ�����Ұ��� */
	}
	*position = low;  
	return(0);				/* ����ʧ�� */
}
//��д��δ����Ĳ���
void noSortInsertDictionary(SeqDictionary * pdic, KeyType key, DataType value){
	int number=pdic->n;
	//�����ֵ�Ԫ��
	pdic->element[number].key=key;
	pdic->element[number].value=value;
	pdic->n++;
}
int insertDictionary(SeqDictionary * pdic, KeyType key, DataType value) {
	int pos,i;
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
	for (pos = 0; pos < pdic->n; pos++) {
		if (key < pdic->element[pos].key)
			break;
	}

	for (i = pdic->n-1; i >= pos; i--) {         /* ����λ�ü�֮���Ԫ�ؾ�����һ��λ�� */
		pdic->element[i + 1] = pdic->element[i];
	}
	pdic->element[pos].key = key;        /* ����Key */
	pdic->element[pos].value = value;    /* ����value */
	pdic->n = pdic->n + 1;                /* Ԫ�ظ�����1 */
	return (1);
}

void printDictionary(SeqDictionary * pdic) {
	int i;
	//����
	for(i=0;i<pdic->n;i++){
		printf("key: %d  value:%d\n",pdic->element[i].key,pdic->element[i].value);
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. �����ֵ�\n");
	printf("2. ˳�򷨼����ֵ�\n");
	printf("3. Ϊ���ַ����������ֵ�\n");
	printf("4. ���ַ������ֵ�\n");
	printf("5. ��ӡ�ֵ�\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
	int way,key,val,res,flag;//way�������룬flag���������������ֵ�1�����ֵ�2
	int *pos=(int *)malloc(sizeof(int));
	SeqDictionary* dic1;//�ֵ�ָ��
	SeqDictionary* dic2;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			flag=1;
			dic1=create(20);//�����ֵ�
			while(1){
				//����
				printf("input key(����0��ֹ):");
				scanf("%d",&key);
				if(key==0) break;
				printf("input value:");
				scanf("%d",&val);
				//��ͨ�ֵ䲻����
				noSortInsertDictionary(dic1,key,val);
			}
		}
		else if(way==2){
			printf("input the key what you want:");
			scanf("%d",&key);
			//��ͨ������λ�ý�����浽int *pos��,*posΪһ�����ͣ����ҵ���λ�ã�������elementʱҲһ��
			res=seqSearch(dic1,key,pos);
			if(res==0){
				printf("not found");
			}
			else printf("key-->%d   value-->%d    pos-->%d\n",dic1->element[*pos].key,dic1->element[*pos].value,*pos);
		}
		else if(way==3){
			flag=2;
			dic2=create(20);//����
			while(1){
				//����
				printf("input key(����0��ֹ):");
				scanf("%d",&key);
				if(key==0) break;
				printf("input value:");
				scanf("%d",&val);
				insertDictionary(dic2,key,val);
			}
		}
		else if(way==4){
			printf("input the key what you want:");
			scanf("%d",&key);
			//����
			res=binarySearch(dic2,key,pos);
			if(res==0){
				printf("not found");
			}
			else printf("key-->%d   value-->%d    pos-->%d\n",dic1->element[*pos].key,dic1->element[*pos].value,*pos);
		}
		else if(way==5){
			//����
			if(flag==1)
				printDictionary(dic1);
			else printDictionary(dic2);
		}
	}
}
    