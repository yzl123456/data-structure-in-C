#pragma warning(disable: 4996)
/* SeqDictionary.c*/
/*字典的顺序表示方式*/

#include<stdio.h>
#include<stdlib.h>

typedef  int		KeyType;
typedef  int		DataType;
typedef struct {
	KeyType key;				/* 字典元素的关键码字段	*/
	DataType value;			    /* 字典元素的属性字段	*/
}DicElement;

typedef struct {
	int MAXNUM; 		/*字典中元素的个数上界*/
	int n;					/*为字典中实际元素的个数 */
	DicElement *element; 		 /*存放字典中的元素*/
} SeqDictionary;
SeqDictionary* create(int m){
	//创建字典集合
	SeqDictionary* node=(SeqDictionary *)malloc(sizeof(SeqDictionary));
	node->MAXNUM=m;
	node->n=0;
	node->element=(DicElement *)malloc(sizeof(DicElement)*m);
	return node;
}
/*顺序检索算法*/
int seqSearch(SeqDictionary * pdic, KeyType key, int * position) {
	/*在字典中顺序检索关键码为key的元素*/
	int i;
	for (i = 0; i<pdic->n; i++)			/* 从头开始向后扫描	*/
		if (pdic->element[i].key == key)
		{
			*position = i;
			return(1);
		}	/* 检索成功 */

	*position = pdic->n;
	return(0);				/* 检索失败 */
}

/* 在字典中用二分法查找关键码为key的元素 */
int binarySearch(SeqDictionary * pdic, KeyType key, int *position) {
	int low, mid, high;
	low = 0;  high = pdic->n - 1;
	while (low <= high) {
		mid = (low + high) / 2;							/* 当前检索的中间位置 */
		if (pdic->element[mid].key == key) {
			*position = mid;  
			return(1);
		}	/* 检索成功 */
		else if (pdic->element[mid].key>key)
			high = mid - 1;	        /* 要检索的元素在左半区 */
		else  low = mid + 1;		 /* 要检索的元素在右半区 */
	}
	*position = low;  
	return(0);				/* 检索失败 */
}
//手写的未排序的插入
void noSortInsertDictionary(SeqDictionary * pdic, KeyType key, DataType value){
	int number=pdic->n;
	//构造字典元素
	pdic->element[number].key=key;
	pdic->element[number].value=value;
	pdic->n++;
}
int insertDictionary(SeqDictionary * pdic, KeyType key, DataType value) {
	int pos,i;
	if (pdic->n >= pdic->MAXNUM) {   /* 溢出 */
		printf("Overflow!\n");
		return (0);
	}
	if (pdic->n == 0) {                    /*空顺序表插入 */
		pdic->element[0].key = key;        /* 插入Key */
		pdic->element[0].value = value;    /* 插入value */
		pdic->n = 1;                       /* 元素个数为1 */
		return (1);
	}
	for (pos = 0; pos < pdic->n; pos++) {
		if (key < pdic->element[pos].key)
			break;
	}

	for (i = pdic->n-1; i >= pos; i--) {         /* 插入位置及之后的元素均后移一个位置 */
		pdic->element[i + 1] = pdic->element[i];
	}
	pdic->element[pos].key = key;        /* 插入Key */
	pdic->element[pos].value = value;    /* 插入value */
	pdic->n = pdic->n + 1;                /* 元素个数加1 */
	return (1);
}

void printDictionary(SeqDictionary * pdic) {
	int i;
	//遍历
	for(i=0;i<pdic->n;i++){
		printf("key: %d  value:%d\n",pdic->element[i].key,pdic->element[i].value);
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 创建字典\n");
	printf("2. 顺序法检索字典\n");
	printf("3. 为二分法检索创建字典\n");
	printf("4. 二分法检索字典\n");
	printf("5. 打印字典\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
	int way,key,val,res,flag;//way控制输入，flag控制最后输出的是字典1还是字典2
	int *pos=(int *)malloc(sizeof(int));
	SeqDictionary* dic1;//字典指针
	SeqDictionary* dic2;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			flag=1;
			dic1=create(20);//创建字典
			while(1){
				//输入
				printf("input key(输入0终止):");
				scanf("%d",&key);
				if(key==0) break;
				printf("input value:");
				scanf("%d",&val);
				//普通字典不排序
				noSortInsertDictionary(dic1,key,val);
			}
		}
		else if(way==2){
			printf("input the key what you want:");
			scanf("%d",&key);
			//普通遍历，位置结果保存到int *pos里,*pos为一个整型，即找到的位置，下面用element时也一样
			res=seqSearch(dic1,key,pos);
			if(res==0){
				printf("not found");
			}
			else printf("key-->%d   value-->%d    pos-->%d\n",dic1->element[*pos].key,dic1->element[*pos].value,*pos);
		}
		else if(way==3){
			flag=2;
			dic2=create(20);//创建
			while(1){
				//输入
				printf("input key(输入0终止):");
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
			//二分
			res=binarySearch(dic2,key,pos);
			if(res==0){
				printf("not found");
			}
			else printf("key-->%d   value-->%d    pos-->%d\n",dic1->element[*pos].key,dic1->element[*pos].value,*pos);
		}
		else if(way==5){
			//遍历
			if(flag==1)
				printDictionary(dic1);
			else printDictionary(dic2);
		}
	}
}
    