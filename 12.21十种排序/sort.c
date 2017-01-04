#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
//#include "PriorityQueue.c"
#define TRUE 1;
#define FALSE 0;

typedef int KeyType;
typedef int DataType;
//我把include的.c文件里东西直接拉过来了
struct PriorityQueue {
	int MAXNUM;  /*堆中的元素个数的上限 */
	int n;	      /*堆中的实际元素个数*/
	DataType *pq;   /*堆中元素的顺序表示*/
};	/*优先队列类型*/
typedef struct PriorityQueue * PPriorityQueue;	/*指向优先队列的指针类型*/

typedef struct
{
	KeyType key;		/* 排序码字段 */
	DataType info;	/* 记录的其它字段 */
}RecordNode;

typedef struct
{
	int n;			/* n为文件中的记录个数*/
	RecordNode  *record;
}SortObject;

/*直接插入排序*/
void  insertSort(SortObject * pvector) {
	/* 按递增序进行直接插入排序 */
	int i, j;
	RecordNode temp;
	for (i = 1; i < pvector->n; i++) {
		/* 依次插入记录R1, R2…Rn-1 */
		temp = pvector->record[i];
		j = i - 1;
		while ((temp.key < pvector->record[j].key) && (j >= 0)) {  /* 由后向前找插入位置 */
			pvector->record[j + 1] = pvector->record[j];	j--;
		}
		/* 将排序码大于ki的记录后移 */
		if (j != (i - 1)) pvector->record[j + 1] = temp;
	}
}


/*二分法插入排序*/
void  binSort(SortObject * pvector) {
	/* 按递增序进行二分法插入排序 */
	int i, j, left, mid, right;
	RecordNode temp;
	for (i = 1; i < pvector->n; i++) {
		temp = pvector->record[i]; left = 0; right = i - 1;
		/* 置已排序区间的下、上界初值 */
		while (left <= right) {
			mid = (left + right) / 2;				/* mid指向已排序区间的中间位置 */
			if (temp.key<pvector->record[mid].key)
				right = mid - 1;	 /* 插入元素应在左子区间 */
			else	 
				left = mid + 1;				/* 插入元素应在右子区间 */
		}
		for (j = i - 1; j >= left; j--) 
			pvector->record[j + 1] = pvector->record[j];
		/* 将排序码大的记录后移 */
		if (left != i) pvector->record[left] = temp;
	}
}

/****************************************************************************/


struct Node;				/* 单链表结点类型 */
typedef struct Node ListNode;
struct Node
{
	KeyType key;			    /* 排序码字段 */
	DataType info;			/* 记录的其它字段 */
	ListNode *next;			/* 记录的指针字段 */
};
typedef ListNode * LinkList;

/* 对链表按递增序进行表插入排序，链表中第一个结点为表头结点。 */
void listSort(LinkList  plist) {
	ListNode *now, *pre, *p, *q, *head;
	head = plist;
	pre = head->next;
	if (pre == NULL) return;
	now = pre->next;
	if (now == NULL) return;			/* 为空链表或链表中只有一个结点 */
	while (now != NULL) {
		q = head;	p = head->next;
		while (p != now && p->key <= now->key) { 
			q = p; 
			p = p->next;
		} /* 循环结束找到插入位置 */
		if (p == now) { pre = pre->next; now = pre->next; continue; }		/* now应放在原位置 */
		pre->next = now->next;					/* 使now记录脱链 */
		q->next = now;	now->next = p;				/* 将now记录插入链表中 */
		now = pre->next;
	}
}

/*Shell排序*/
void  shellSort(SortObject * pvector, int d) {	/* 按递增序进行Shell排序 */
	int i, j, increment;
	RecordNode temp;
	for (increment = d; increment > 0; increment /= 2) {/* increment为本趟shell排序增量 */
		for (i = increment; i<pvector->n; i++) {
			temp = pvector->record[i];					/* 保存待插入记录Ri*/
			j = i - increment;
			while (j >= 0 && temp.key<pvector->record[j].key) {/* 查找插入位置 */
				pvector->record[j + increment] = pvector->record[j];	/* 记录后移 */
				j -= increment;
			}
			pvector->record[j + increment] = temp;				/* 插入记录Ri */
		}
	}
}



/*直接选择排序*/
void  selectSort(SortObject * pvector) {  /* 按递增序进行直接选择排序 */
	int i, j, k;
	RecordNode temp;
	for (i = 0; i < pvector->n - 1; i++) {		/* 做n-1趟选择排序 */ k = i; for (j = i + 1; j<pvector->n; j++)		/* 在无序区内找出排序码最小的记录Rk*/
		if (pvector->record[j].key<pvector->record[k].key)  k = j;
	if (k != i) {									/* 记录Rk与Ri互换 */
		temp = pvector->record[i];
		pvector->record[i] = pvector->record[k];
		pvector->record[k] = temp;
	}
	}
}

/*堆排序*/
/*构造堆函数*/
void  sift(SortObject * pvector, int size, int p) {
	RecordNode temp = pvector->record[p];
	int child = 2 * p + 1;
	while (child<size) {
		if ((child<size - 1) && (pvector->record[child].key>pvector->record[child + 1].key))
			child++;	/*选择比较小的子结点 */
		if (temp.key>pvector->record[child].key) {
			pvector->record[p] = pvector->record[child]; /*将小的子结点上移 */
			p = child;
			child = 2 * p + 1;
		}
		else  break;			/* 调整结束 */
	}
	pvector->record[p] = temp;	/* 将temp放入正确位置 */
}

void heapSort(SortObject * pvector) {
	int i, n;
	RecordNode temp;
	n = pvector->n;
	for (i = n / 2 - 1; i >= 0; i--)
		sift(pvector, n, i);   /*首先构造第一个堆*/
	for (i = n - 1; i > 0; i--) {   /*把最小元素与最后一个元素进行交换*/
		temp = pvector->record[0];
		pvector->record[0] = pvector->record[i];
		pvector->record[i] = temp;
		sift(pvector, i, 0);  /*重新调整建堆。注意i在控制调整范围中的作用*/
	}
}


/*起泡排序*/
void  bubbleSort(SortObject * pvector) {
	int i, j, noswap;
	RecordNode temp;
	for (i = 0; i<pvector->n - 1; i++) {							/* 做n-1次起泡 */
		noswap = TRUE; 		/* 置交换标志初态 */
		for (j = 0; j<pvector->n - i - 1; j++)
			if (pvector->record[j + 1].key<pvector->record[j].key) {		/* 从前向后扫描 */
				temp = pvector->record[j];						/* 交换记录 */
				pvector->record[j] = pvector->record[j + 1];
				pvector->record[j + 1] = temp;
				noswap = FALSE;  		/* 修改交换标志 */
			}
		if (noswap)  break;				/* 本趟起泡未发生记录交换，算法结束 */
	}
}

/*快速排序*/
void  quickSort(SortObject * pvector, int l, int r) {
	int i, j;
	RecordNode temp;
	if (l >= r)  return;						/* 只有一个记录或无记录，则无须排序 */
	i = l;  j = r;  temp = pvector->record[i];
	while (i != j) {							/* 寻找Rl的最终位置 */
		while ((pvector->record[j].key >= temp.key) && (j>i))  j--;
		/* 从右向左扫描，查找第1个排序码小于temp.key的记录 */
		if (i<j) pvector->record[i++] = pvector->record[j];
		while ((pvector->record[i].key <= temp.key) && (j>i))  i++;
		/* 从左向右扫描，查找第1个排序码大于temp.key的记录 */
		if (i<j)  pvector->record[j--] = pvector->record[i];
	}
	pvector->record[i] = temp;			/* 找到Rl的最终位置 */
	quickSort(pvector, l, i - 1);  			/* 递归处理左区间 */
	quickSort(pvector, i + 1, r);			/* 递归处理右区间 */
}

/****************************************************************************/

struct Node1;
typedef struct Node1 RadixNode;

struct Node1				/*结点类型 */
{
	KeyType key[4];	        /*D为[0,r-1]中的整数*/
	DataType info;
	RadixNode *next;
};
typedef RadixNode * RadixList; 		/*待排序文件类型 */
typedef struct
{
	RadixNode *f;					/*队列的头指针 */
	RadixNode *e;					/*队列的尾指针 */
}Queue;
RadixList createRadix(){//创建基数，其中基数为10，低位优先，key数组保存排序码的各位数字，其中x的合法输入为3位数及以内，key【2】保存个位，key【1】保存十位，key【0】保存百位
	RadixList plist=(RadixList)malloc(sizeof(RadixNode));//创建基数链表
	RadixList cur=plist;
	RadixNode *tmp;//链表中的节点
	int x;
	printf("please input the value(0 is the end):");
	while(1){
		scanf("%d",&x);//输入
		if(x==0) break;
		tmp=(RadixNode *)malloc(sizeof(RadixNode));//申请空间
		//其中info字段存的是其他字段的信息，比如说info可以存一个学生的结构体，此处仅用到排序的话略去不写
		//tmp->info=x;
		//分解输入的数字
		tmp->key[2]=x%10;tmp->key[1]=x/10%10;tmp->key[0]=x/100%10;
		tmp->next=NULL;
		cur->next=tmp;//不断衔接链表
		cur=tmp;
	}

	return plist;//返回
}

/*基数排序,调用时r可以设为常量7*/
void radixSort(RadixList  plist, int d, int r) {
	int i, j, k;
	Queue queue[10];
	RadixNode *p, *head;
	head = plist->next;
	for (j = d - 1; j >= 0; j--) {					/* 进行d次分配和收集*/
		p = head;
		for (i = 0; i<r; i++) { queue[i].f = NULL; queue[i].e = NULL; }	/* 清队列 */
		while (p != NULL) {
			k = p->key[j];							/* 按排序码的第j个分量进行分配*/
			if (queue[k].f == NULL) queue[k].f = p;	/* 若第k个堆为空，则当前记录为队头*/
			else (queue[k].e)->next = p;			/* 否则当前记录链接到第k队的队尾*/
			queue[k].e = p;  p = p->next;
		}
		i = 0;
		while (queue[i].f == NULL)  i++;			/* 从r个队列中找出第一个非空的队列*/
		p = queue[i].e;  head = queue[i].f;			/* head为收集链表的头指针*/
		for (i++; i<r; i++)
			if (queue[i].f != NULL)
			{
				p->next = queue[i].f;  p = queue[i].e;
			}		/* 收集非空队列 */
		p->next = NULL;
	}
	plist->next = head;
}

/*两组归并算法*/
void merge(RecordNode *r, RecordNode *r1, int low, int m, int high) {
	/* r[low]到r[m]和r[m+1]到r[high]是两个有序文件 */
	int i, j, k;
	i = low;  j = m + 1;  k = low;
	while ((i <= m) && (j <= high)) {  /* 从两个有序文件中的第一个记录中选出小的记录 */
		if (r[i].key <= r[j].key)	r1[k++] = r[i++];
		else  r1[k++] = r[j++];
	}
	while (i <= m)  r1[k++] = r[i++];		/* 复制第一个文件的剩余记录 */
	while (j <= high)  r1[k++] = r[j++];	/* 复制第二个文件的剩余记录 */
}


/* 对r做一趟归并，结果放在r1中 */
void mergePass(RecordNode *r, RecordNode *r1, int n, int length) {
	/* length为本趟归并的有序子文件的长度 */
	int j, i = 0;
	while (i + 2 * length - 1<n) {
		merge(r, r1, i, i + length - 1, i + 2 * length - 1);	/* 归并长度为length的两个子文件*/
		i += 2 * length;
	}
	if (i + length - 1<n - 1)  /* 剩下两个子文件，其中一个长度小于 length */
		merge(r, r1, i, i + length - 1, n - 1);
	else
		for (j = i; j<n; j++) r1[j] = r[j];			/* 将最后一个子文件复制到数组r1中 */
}

/*二路归并排序*/
void mergeSort(SortObject * pvector) {
	RecordNode record[100]; /*不接受变量pvector->n*/
	int length = 1;
	while (length<pvector->n) {
		mergePass(pvector->record, record, pvector->n, length);
		/* 一趟归并，结果放在r1中*/
		length *= 2;
		mergePass(record, pvector->record, pvector->n, length);
		/* 一趟归并，结果放在r中 */
		length *= 2;
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1.  (插入排序)直接插入排序\n");
	printf("2.  (插入排序)二分法排序\n");
	printf("3.  (插入排序)表插入排序\n");
	printf("4.  (插入排序)Shell排序\n");
	printf("5.  (选择排序)直接选择排序\n");
	printf("6.  (选择排序)堆排序\n");
	printf("7.  (交换排序)气泡排序\n");
	printf("8.  (交换排序)快速排序\n");
	printf("9.  (分配排序)基数排序\n");
	printf("10. (归并排序)二路归并排序\n");
	printf("0. 退出\n");
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
	printf("请输入记录,0表示结束:");
	scanf("%d", &key);
	while (key != 0) {
		SO->record[SO->n].key = key;
		SO->n++;
		scanf("%d", &key);
	}
	return SO;
}

void add_heap(PPriorityQueue papq, DataType x) { /*向优先队列中插入x,保持堆序性*/
	int i;
	if (papq->n >= papq->MAXNUM) { printf("Full!\n");	return; }
	for (i = papq->n; i > 0 && papq->pq[(i - 1) / 2] > x; i = (i - 1) / 2)
		papq->pq[i] = papq->pq[(i - 1) / 2];  /*空位向根移动，找插入的位置*/
	papq->pq[i] = x;   papq->n++;   /*将x插入*/
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
	s = --papq->n; /*先删除，*/
	temp = papq->pq[s];  /*把最后元素移到temp*/
						 /*从根结点调整papq所指的完全二叉树为堆*/
	i = 0;  	child = 1;
	while (child < s) {   /*找最后元素存放的位置*/
		if (child < s - 1 && papq->pq[child] > papq->pq[child + 1])
			child++; /*选择比较小的子结点*/
		if (temp > papq->pq[child]) /*空位向叶结点移动*/
		{
			papq->pq[i] = papq->pq[child]; 	i = child; child = 2 * i + 1;
		}
		else break;  /*已经找到适当位置*/
	}
	papq->pq[i] = temp;  /*把最后元素填入*/
}
LinkList createList(){//创建链表（带头结点）
	int x;ListNode * tmp;
	LinkList head=(LinkList)malloc(sizeof( ListNode));
	LinkList cur=head;
	
	printf("please input the value(0 is end):");
	while(1){
		scanf("%d",&x);//输入
		if(x==0) break;
		tmp=(ListNode *)malloc(sizeof( ListNode));//申请空间
		tmp->key=x;tmp->next=NULL;//构造节点
		cur->next=tmp;//衔接
		cur=tmp;
	}
	return head;//返回头结点
}
PPriorityQueue createPriorityQueue(int max){//利用优先队列实现小根堆
	PPriorityQueue papq=(PPriorityQueue )malloc(sizeof(struct PriorityQueue));//创建优先队列指针
	papq->MAXNUM=max;//赋值构造
	papq->n=0;
	papq->pq=(int *)malloc(sizeof(int)*max);//存数据的顺序表示
	return papq;//返回
}
void main() {
	/*
		请实在不会后再看此题解，否则后果自负！
	*/
	int way,x;
	SortObject * object;//排序的物体指针
	LinkList head;//链表排序头结点
	PPriorityQueue priorityQueue;//优先队列指针
	RadixList radixList;//基数链表指针
	while(1){
		scanf("%d",&way);
		if(way==1){//直接插入排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);//创建并输入数据
			insertSort(object);//排序
			printSortedKeys(object);//输出
		}
		else if(way==2){//二分排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			binSort(object);
			printSortedKeys(object);
		}
		else if(way==3){//链表插入排序
			head=createList();//徒手建链表
			listSort(head);
			printSortedLinkedKeys(head);
		}
		else if(way==4){//希尔排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			shellSort(object,object->n/2);//希尔排序，此处采取的d1=n/2
			printSortedKeys(object);
		}
		else if(way==5){//直接选择排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			selectSort(object);
			printSortedKeys(object);
		}
		else if(way==6){//堆排序 此处使用小根堆
			priorityQueue=createPriorityQueue(100);
			while(1){
				scanf("%d",&x);//输入
				if(x==0) break;
				add_heap(priorityQueue,x);//将x加入小根堆
			}
			while(!isEmpty_heap(priorityQueue)){//堆非空
				printf("%d ",priorityQueue->pq[0]);//输出堆顶元素
				removeMin_heap(priorityQueue);//pop掉堆顶元素
			}
			printf("\n");
		}
		else if(way==7){//冒泡排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			bubbleSort(object);
			printSortedKeys(object);
		}
		else if(way==8){//快速排序
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			quickSort(object,0,object->n-1);//指定快排的区间为【0，n-1】
			printSortedKeys(object);
		}
		else if(way==9){//基数排序
			radixList=createRadix();//徒手建基数链表

			radixSort(radixList,3,10);//排序，此处在输入的数据为3位数及以内的条件下，轮数是3，基数为10

			printRadixSortKeys(radixList);//输出（含前导0）
		}
		else if(way==10){//二路归并
			object=(SortObject*)malloc(sizeof(SortObject));
			object=createSortObject(object);
			mergeSort(object);
			printSortedKeys(object);
		}
	}


	




	
}