#pragma warning(disable:4996)

/* HashDictionary.c*/
/*字典的散列表示*/


#include <stdio.h>
#include <stdlib.h>
typedef  int		KeyType;
typedef  int		DataType;
typedef struct {
	KeyType key;				/* 字典元素的关键码字段	*/
	DataType value;			/* 字典元素的属性字段	*/
}DicElement;

typedef struct
{
	int m;					/* m为基本区域长度 */
	DicElement *element;
} HashDictionary;

int m;

/*创建空散列表*/
HashDictionary* createEmptyDictionary(int m) {
	int i;
	HashDictionary* phd = (HashDictionary*)malloc(sizeof(HashDictionary));
	if (phd != NULL) {
		phd->element = (DicElement *)malloc(sizeof(DicElement)*m);
		if (phd->element) {
			phd->m = m;
			for (i = 0; i<m; i++)
				phd->element[i].key = 0;   /*初始化*/
			return (phd);
		}
		else
			free(phd);
	}
	printf("Out of space!!\n");    	/* 存储分配失败 */
	return NULL;
}

int h(KeyType key) {
	return key%m;
}

/*散列表的检索算法—用线性探查法解决碰撞*/
int linearSearch(HashDictionary * phash, KeyType key, int *position) {
	int d, inc;
	d = h(key);				/* d为散列地址，散列函数为h(key) */
	for (inc = 0; inc<phash->m; inc++) {
		if (phash->element[d].key == key) {
			*position = d;					/* 检索成功 */
			return(1);
		}
		else if (phash->element[d].key == 0) {
			*position = d;					/* 检索失败，找到插入位置 */
			return(0);
		}
		d = (d + 1) % phash->m;
	}
	*position = -1;						/* 散列表溢出 */
	return(0);
}

/*散列表的插入算法—用线性探查法解决碰撞*/
int linearInsert(HashDictionary *phash, DicElement ele) {
	int position;
	/*散列表中已有关键码为key的结点 */
	if (linearSearch(phash, ele.key, &position) == 1)
		printf("Find\n");
	else if (position != -1)
		phash->element[position] = ele;		/* 插入结点*/
	else  
		return(0);						/* 散列表溢出 */
	return(1);
}

void printHashDirectionary(HashDictionary *phash) {
	int i;
	for(i=0;i<phash->m;i++){//从头到尾依次打印每个key
		printf("%d ",phash->element[i].key);
	}
	printf("\n");
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 创建散列表\n");
	printf("2. 散列表中插入关键码集合\n");
	printf("3. 打印散列表中的关键码\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
    int way,x;
	HashDictionary* phash;//Hash表
	DicElement* tmp;//存放新节点
	while(1){
		scanf("%d",&way);
		if(way==1){
			scanf("%d",&m);
			phash=createEmptyDictionary(m);//创建
		}
		else if(way==2){
			while(1){
				scanf("%d",&x);//输入
				if(x==0) break;
				tmp=(DicElement* )malloc(sizeof( DicElement));//创建新节点
				tmp->key=x;tmp->value=h(x);//赋值
				linearInsert(phash,*tmp);//插入
			}
		}
		else if(way==3){
			printHashDirectionary(phash);//打印
		}
	}

}