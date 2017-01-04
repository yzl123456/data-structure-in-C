#pragma warning(disable:4996)
/* HashDictionary.c*/
/*字典的散列表示*/


#include <stdio.h>
#include <stdlib.h>
typedef  int		KeyType;
typedef  int		DataType;

struct DicElement;

typedef struct DicElement *LinkElement;

struct DicElement {
	KeyType key;				/* 字典元素的关键码字段	*/
	DataType value;			/* 字典元素的属性字段	*/
	LinkElement next;
};



typedef struct
{
	int m;					/* m为基本区域长度 */
	LinkElement *element;
} HashDictionary;

int m;

/*创建空散列表*/
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
	printf("Out of space!!\n");    	/* 存储分配失败 */
	return NULL;
}

int h(KeyType key) {

	return key%m;
}

/*散列表的检索*/
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

/*散列表的插入算法*/
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
	LinkElement tmp;//存放一个地址空间指向链表的头结点
	for(i=0;i<phash->m;i++){
		printf("[%d]  ",i);
		tmp=phash->element[i];//得到头结点
		while(tmp!=NULL){
			printf("%d ",tmp->key);//遍历
			tmp=tmp->next;
		}
		printf("\n");
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 创建散列表\n");
	printf("2. 散列表中插入关键码集合\n");
	printf("3. 根据关键码检索散列表\n");
	printf("4. 打印散列表中的关键码\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
    int way,x,key,res;
	HashDictionary* phash;//hash表
	LinkElement tmp;//存放新建立的节点
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
				tmp=(LinkElement )malloc(sizeof(struct DicElement));//创建新节点
				tmp->key=x;tmp->value=h(x);tmp->next=NULL;//赋值
				linearInsert(phash,tmp);//插入
			}
		}
		else if(way==3){
			scanf("%d",&key);//输入
			res=linearSearch(phash,key);//检索
			if(res==0) printf("not found\n");
			else printf("find is ok!\n");

		}
		else if(way==4){
			printHashDirectionary(phash);//打印
		}
	}
}