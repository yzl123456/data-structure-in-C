#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//#include "PriorityQueue.c"
#define TRUE 1;
#define FALSE 0;

typedef int KeyType;
typedef int DataType;
//�Ұ�include��.c�ļ��ﶫ��ֱ����������
struct PriorityQueue {
	int MAXNUM;  /*���е�Ԫ�ظ��������� */
	int n;	      /*���е�ʵ��Ԫ�ظ���*/
	DataType *pq;   /*����Ԫ�ص�˳���ʾ*/
};	/*���ȶ�������*/
typedef struct PriorityQueue * PPriorityQueue;	/*ָ�����ȶ��е�ָ������*/

typedef struct
{
	KeyType key;		/* �������ֶ� */
	DataType info;	/* ��¼�������ֶ� */
}RecordNode;

typedef struct
{
	int n;			/* nΪ�ļ��еļ�¼����*/
	RecordNode  *record;
}SortObject;

/*ֱ�Ӳ�������*/
void  insertSort(SortObject * pvector) {
	/* �����������ֱ�Ӳ������� */
	int i, j;
	RecordNode temp;
	for (i = 1; i < pvector->n; i++) {
		/* ���β����¼R1, R2��Rn-1 */
		temp = pvector->record[i];
		j = i - 1;
		while ((temp.key < pvector->record[j].key) && (j >= 0)) {  /* �ɺ���ǰ�Ҳ���λ�� */
			pvector->record[j + 1] = pvector->record[j];	j--;
		}
		/* �����������ki�ļ�¼���� */
		if (j != (i - 1)) pvector->record[j + 1] = temp;
	}
}


/*���ַ���������*/
void  binSort(SortObject * pvector) {
	/* ����������ж��ַ��������� */
	int i, j, left, mid, right;
	RecordNode temp;
	for (i = 1; i < pvector->n; i++) {
		temp = pvector->record[i]; left = 0; right = i - 1;
		/* ��������������¡��Ͻ��ֵ */
		while (left <= right) {
			mid = (left + right) / 2;				/* midָ��������������м�λ�� */
			if (temp.key<pvector->record[mid].key)
				right = mid - 1;	 /* ����Ԫ��Ӧ���������� */
			else	 
				left = mid + 1;				/* ����Ԫ��Ӧ���������� */
		}
		for (j = i - 1; j >= left; j--) 
			pvector->record[j + 1] = pvector->record[j];
		/* ���������ļ�¼���� */
		if (left != i) pvector->record[left] = temp;
	}
}

/****************************************************************************/


struct Node;				/* ������������ */
typedef struct Node ListNode;
struct Node
{
	KeyType key;			    /* �������ֶ� */
	DataType info;			/* ��¼�������ֶ� */
	ListNode *next;			/* ��¼��ָ���ֶ� */
};
typedef ListNode * LinkList;

/* ��������������б�������������е�һ�����Ϊ��ͷ��㡣 */
void listSort(LinkList  plist) {
	ListNode *now, *pre, *p, *q, *head;
	head = plist;
	pre = head->next;
	if (pre == NULL) return;
	now = pre->next;
	if (now == NULL) return;			/* Ϊ�������������ֻ��һ����� */
	while (now != NULL) {
		q = head;	p = head->next;
		while (p != now && p->key <= now->key) { 
			q = p; 
			p = p->next;
		} /* ѭ�������ҵ�����λ�� */
		if (p == now) { pre = pre->next; now = pre->next; continue; }		/* nowӦ����ԭλ�� */
		pre->next = now->next;					/* ʹnow��¼���� */
		q->next = now;	now->next = p;				/* ��now��¼���������� */
		now = pre->next;
	}
}

/*Shell����*/
void  shellSort(SortObject * pvector, int d) {	/* �����������Shell���� */
	int i, j, increment;
	RecordNode temp;
	for (increment = d; increment > 0; increment /= 2) {/* incrementΪ����shell�������� */
		for (i = increment; i<pvector->n; i++) {
			temp = pvector->record[i];					/* ����������¼Ri*/
			j = i - increment;
			while (j >= 0 && temp.key<pvector->record[j].key) {/* ���Ҳ���λ�� */
				pvector->record[j + increment] = pvector->record[j];	/* ��¼���� */
				j -= increment;
			}
			pvector->record[j + increment] = temp;				/* �����¼Ri */
		}
	}
}



/*ֱ��ѡ������*/
void  selectSort(SortObject * pvector) {  /* �����������ֱ��ѡ������ */
	int i, j, k;
	RecordNode temp;
	for (i = 0; i < pvector->n - 1; i++) {		/* ��n-1��ѡ������ */ k = i; for (j = i + 1; j<pvector->n; j++)		/* �����������ҳ���������С�ļ�¼Rk*/
		if (pvector->record[j].key<pvector->record[k].key)  k = j;
	if (k != i) {									/* ��¼Rk��Ri���� */
		temp = pvector->record[i];
		pvector->record[i] = pvector->record[k];
		pvector->record[k] = temp;
	}
	}
}

/*������*/
/*����Ѻ���*/
void  sift(SortObject * pvector, int size, int p) {
	RecordNode temp = pvector->record[p];
	int child = 2 * p + 1;
	while (child<size) {
		if ((child<size - 1) && (pvector->record[child].key>pvector->record[child + 1].key))
			child++;	/*ѡ��Ƚ�С���ӽ�� */
		if (temp.key>pvector->record[child].key) {
			pvector->record[p] = pvector->record[child]; /*��С���ӽ������ */
			p = child;
			child = 2 * p + 1;
		}
		else  break;			/* �������� */
	}
	pvector->record[p] = temp;	/* ��temp������ȷλ�� */
}

void heapSort(SortObject * pvector) {
	int i, n;
	RecordNode temp;
	n = pvector->n;
	for (i = n / 2 - 1; i >= 0; i--)
		sift(pvector, n, i);   /*���ȹ����һ����*/
	for (i = n - 1; i > 0; i--) {   /*����СԪ�������һ��Ԫ�ؽ��н���*/
		temp = pvector->record[0];
		pvector->record[0] = pvector->record[i];
		pvector->record[i] = temp;
		sift(pvector, i, 0);  /*���µ������ѡ�ע��i�ڿ��Ƶ�����Χ�е�����*/
	}
}


/*��������*/
void  bubbleSort(SortObject * pvector) {
	int i, j, noswap;
	RecordNode temp;
	for (i = 0; i<pvector->n - 1; i++) {							/* ��n-1������ */
		noswap = TRUE; 		/* �ý�����־��̬ */
		for (j = 0; j<pvector->n - i - 1; j++)
			if (pvector->record[j + 1].key<pvector->record[j].key) {		/* ��ǰ���ɨ�� */
				temp = pvector->record[j];						/* ������¼ */
				pvector->record[j] = pvector->record[j + 1];
				pvector->record[j + 1] = temp;
				noswap = FALSE;  		/* �޸Ľ�����־ */
			}
		if (noswap)  break;				/* ��������δ������¼�������㷨���� */
	}
}

/*��������*/
void  quickSort(SortObject * pvector, int l, int r) {
	int i, j;
	RecordNode temp;
	if (l >= r)  return;						/* ֻ��һ����¼���޼�¼������������ */
	i = l;  j = r;  temp = pvector->record[i];
	while (i != j) {							/* Ѱ��Rl������λ�� */
		while ((pvector->record[j].key >= temp.key) && (j>i))  j--;
		/* ��������ɨ�裬���ҵ�1��������С��temp.key�ļ�¼ */
		if (i<j) pvector->record[i++] = pvector->record[j];
		while ((pvector->record[i].key <= temp.key) && (j>i))  i++;
		/* ��������ɨ�裬���ҵ�1�����������temp.key�ļ�¼ */
		if (i<j)  pvector->record[j--] = pvector->record[i];
	}
	pvector->record[i] = temp;			/* �ҵ�Rl������λ�� */
	quickSort(pvector, l, i - 1);  			/* �ݹ鴦�������� */
	quickSort(pvector, i + 1, r);			/* �ݹ鴦�������� */
}

/****************************************************************************/

struct Node1;
typedef struct Node1 RadixNode;

struct Node1				/*������� */
{
	KeyType key[4];	        /*DΪ[0,r-1]�е�����*/
	DataType info;
	RadixNode *next;
};
typedef RadixNode * RadixList; 		/*�������ļ����� */
typedef struct
{
	RadixNode *f;					/*���е�ͷָ�� */
	RadixNode *e;					/*���е�βָ�� */
}Queue;
RadixList createRadix(){//�������������л���Ϊ10����λ���ȣ�key���鱣��������ĸ�λ���֣�����x�ĺϷ�����Ϊ3λ�������ڣ�key��2�������λ��key��1������ʮλ��key��0�������λ
	RadixList plist=(RadixList)malloc(sizeof(RadixNode));//������������
	RadixList cur=plist;
	RadixNode *tmp;//�����еĽڵ�
	int x;
	printf("please input the value(0 is the end):");
	while(1){
		scanf("%d",&x);//����
		if(x==0) break;
		tmp=(RadixNode *)malloc(sizeof(RadixNode));//����ռ�
		//����info�ֶδ���������ֶε���Ϣ������˵info���Դ�һ��ѧ���Ľṹ�壬�˴����õ�����Ļ���ȥ��д
		//tmp->info=x;
		//�ֽ����������
		tmp->key[2]=x%10;tmp->key[1]=x/10%10;tmp->key[0]=x/100%10;
		tmp->next=NULL;
		cur->next=tmp;//�����ν�����
		cur=tmp;
	}

	return plist;//����
}

/*��������,����ʱr������Ϊ����7*/
void radixSort(RadixList  plist, int d, int r) {
	int i, j, k;
	Queue queue[10];
	RadixNode *p, *head;
	head = plist->next;
	for (j = d - 1; j >= 0; j--) {					/* ����d�η�����ռ�*/
		p = head;
		for (i = 0; i<r; i++) { queue[i].f = NULL; queue[i].e = NULL; }	/* ����� */
		while (p != NULL) {
			k = p->key[j];							/* ��������ĵ�j���������з���*/
			if (queue[k].f == NULL) queue[k].f = p;	/* ����k����Ϊ�գ���ǰ��¼Ϊ��ͷ*/
			else (queue[k].e)->next = p;			/* ����ǰ��¼���ӵ���k�ӵĶ�β*/
			queue[k].e = p;  p = p->next;
		}
		i = 0;
		while (queue[i].f == NULL)  i++;			/* ��r���������ҳ���һ���ǿյĶ���*/
		p = queue[i].e;  head = queue[i].f;			/* headΪ�ռ������ͷָ��*/
		for (i++; i<r; i++)
			if (queue[i].f != NULL)
			{
				p->next = queue[i].f;  p = queue[i].e;
			}		/* �ռ��ǿն��� */
		p->next = NULL;
	}
	plist->next = head;
}

/*����鲢�㷨*/
void merge(RecordNode *r, RecordNode *r1, int low, int m, int high) {
	/* r[low]��r[m]��r[m+1]��r[high]�����������ļ� */
	int i, j, k;
	i = low;  j = m + 1;  k = low;
	while ((i <= m) && (j <= high)) {  /* �����������ļ��еĵ�һ����¼��ѡ��С�ļ�¼ */
		if (r[i].key <= r[j].key)	r1[k++] = r[i++];
		else  r1[k++] = r[j++];
	}
	while (i <= m)  r1[k++] = r[i++];		/* ���Ƶ�һ���ļ���ʣ���¼ */
	while (j <= high)  r1[k++] = r[j++];	/* ���Ƶڶ����ļ���ʣ���¼ */
}


/* ��r��һ�˹鲢���������r1�� */
void mergePass(RecordNode *r, RecordNode *r1, int n, int length) {
	/* lengthΪ���˹鲢���������ļ��ĳ��� */
	int j, i = 0;
	while (i + 2 * length - 1<n) {
		merge(r, r1, i, i + length - 1, i + 2 * length - 1);	/* �鲢����Ϊlength���������ļ�*/
		i += 2 * length;
	}
	if (i + length - 1<n - 1)  /* ʣ���������ļ�������һ������С�� length */
		merge(r, r1, i, i + length - 1, n - 1);
	else
		for (j = i; j<n; j++) r1[j] = r[j];			/* �����һ�����ļ����Ƶ�����r1�� */
}

/*��·�鲢����*/
void mergeSort(SortObject * pvector) {
	RecordNode record[100]; /*�����ܱ���pvector->n*/
	int length = 1;
	while (length<pvector->n) {
		mergePass(pvector->record, record, pvector->n, length);
		/* һ�˹鲢���������r1��*/
		length *= 2;
		mergePass(record, pvector->record, pvector->n, length);
		/* һ�˹鲢���������r�� */
		length *= 2;
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1.  (��������)ֱ�Ӳ�������\n");
	printf("2.  (��������)���ַ�����\n");
	printf("3.  (��������)���������\n");
	printf("4.  (��������)Shell����\n");
	printf("5.  (ѡ������)ֱ��ѡ������\n");
	printf("6.  (ѡ������)������\n");
	printf("7.  (��������)��������\n");
	printf("8.  (��������)��������\n");
	printf("9.  (��������)��������\n");
	printf("10. (�鲢����)��·�鲢����\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void printSortedKeys(SortObject * pvector) {
	int i;
	for (i = 0; i<pvector->n; i++) {
		printf("%d ", pvector->record[i].key);
	}
	printf("\n");
}

void printSortedLinkedKeys(LinkList lList) {
	lList = lList->next;
	while (lList != NULL) {
		printf("%d ", lList->key);
		lList = lList->next;
	}
	printf("\n");
}

void printRadixSortKeys(RadixList lList) {
	int i;
	lList = lList->next;
	while (lList != NULL) {
		for (i = 0; i<3; i++)
			printf("%d", lList->key[i]);
		printf(" ");
		lList = lList->next;
	}
	printf("\n");
}

SortObject * createSortObject(SortObject *SO) {
	int key;
	SO = (SortObject*)malloc(sizeof(SortObject));
	SO->n = 0;
	SO->record = (RecordNode*)malloc(sizeof(RecordNode) * 100);
	printf("�������¼,0��ʾ����:");
	scanf("%d", &key);
	while (key != 0) {
		SO->record[SO->n].key = key;
		SO->n++;
		scanf("%d", &key);
	}
	return SO;
}

void add_heap(PPriorityQueue papq, DataType x) { /*�����ȶ����в���x,���ֶ�����*/
	int i;
	if (papq->n >= papq->MAXNUM) { printf("Full!\n");	return; }
	for (i = papq->n; i > 0 && papq->pq[(i - 1) / 2] > x; i = (i - 1) / 2)
		papq->pq[i] = papq->pq[(i - 1) / 2];  /*��λ����ƶ����Ҳ����λ��*/
	papq->pq[i] = x;   papq->n++;   /*��x����*/
}


int isEmpty_heap(PPriorityQueue papq) {
	if (papq->n == 0)
		return 1;
	else
		return 0;

}

void removeMin_heap(PPriorityQueue papq) {
	int s, temp, i, child;
	if (isEmpty_heap(papq)) { printf("Empty!\n"); return; }
	s = --papq->n; /*��ɾ����*/
	temp = papq->pq[s];  /*�����Ԫ���Ƶ�temp*/
						 /*�Ӹ�������papq��ָ����ȫ������Ϊ��*/
	i = 0;  	child = 1;
	while (child < s) {   /*�����Ԫ�ش�ŵ�λ��*/
		if (child < s - 1 && papq->pq[child] > papq->pq[child + 1])
			child++; /*ѡ��Ƚ�С���ӽ��*/
		if (temp > papq->pq[child]) /*��λ��Ҷ����ƶ�*/
		{
			papq->pq[i] = papq->pq[child]; 	i = child; child = 2 * i + 1;
		}
		else break;  /*�Ѿ��ҵ��ʵ�λ��*/
	}
	papq->pq[i] = temp;  /*�����Ԫ������*/
}
LinkList createList(){//����������ͷ��㣩
	int x;ListNode * tmp;
	LinkList head=(LinkList)malloc(sizeof( ListNode));
	LinkList cur=head;
	
	printf("please input the value(0 is end):");
	while(1){
		scanf("%d",&x);//����
		if(x==0) break;
		tmp=(ListNode *)malloc(sizeof( ListNode));//����ռ�
		tmp->key=x;tmp->next=NULL;//����ڵ�
		cur->next=tmp;//�ν�
		cur=tmp;
	}
	return head;//����ͷ���
}
PPriorityQueue createPriorityQueue(int max){//�������ȶ���ʵ��С����
	PPriorityQueue papq=(PPriorityQueue )malloc(sizeof(struct PriorityQueue));//�������ȶ���ָ��
	papq->MAXNUM=max;//��ֵ����
	papq->n=0;
	papq->pq=(int *)malloc(sizeof(int)*max);//�����ݵ�˳���ʾ
	return papq;//����
}
void main() {
	/*
		��ʵ�ڲ�����ٿ�����⣬�������Ը���
	*/
	int way,x;
	SortObject * object;//���������ָ��
	LinkList head;//��������ͷ���
	PPriorityQueue priorityQueue;//���ȶ���ָ��
	RadixList radixList;//��������ָ��
	while(1){
		scanf("%d",&way);
		if(way==1){//ֱ�Ӳ�������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);//��������������
			insertSort(object);//����
			printSortedKeys(object);//���
		}
		else if(way==2){//��������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			binSort(object);
			printSortedKeys(object);
		}
		else if(way==3){//�����������
			head=createList();//ͽ�ֽ�����
			listSort(head);
			printSortedLinkedKeys(head);
		}
		else if(way==4){//ϣ������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			shellSort(object,object->n/2);//ϣ�����򣬴˴���ȡ��d1=n/2
			printSortedKeys(object);
		}
		else if(way==5){//ֱ��ѡ������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			selectSort(object);
			printSortedKeys(object);
		}
		else if(way==6){//������ �˴�ʹ��С����
			priorityQueue=createPriorityQueue(100);
			while(1){
				scanf("%d",&x);//����
				if(x==0) break;
				add_heap(priorityQueue,x);//��x����С����
			}
			while(!isEmpty_heap(priorityQueue)){//�ѷǿ�
				printf("%d ",priorityQueue->pq[0]);//����Ѷ�Ԫ��
				removeMin_heap(priorityQueue);//pop���Ѷ�Ԫ��
			}
			printf("\n");
		}
		else if(way==7){//ð������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			bubbleSort(object);
			printSortedKeys(object);
		}
		else if(way==8){//��������
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			quickSort(object,0,object->n-1);//ָ�����ŵ�����Ϊ��0��n-1��
			printSortedKeys(object);
		}
		else if(way==9){//��������
			radixList=createRadix();//ͽ�ֽ���������

			radixSort(radixList,3,10);//���򣬴˴������������Ϊ3λ�������ڵ������£�������3������Ϊ10

			printRadixSortKeys(radixList);//�������ǰ��0��
		}
		else if(way==10){//��·�鲢
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			mergeSort(object);
			printSortedKeys(object);
		}
	}


	




	
}