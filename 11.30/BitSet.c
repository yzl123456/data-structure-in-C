/*BitSet.c*/
/*集合的位向量表示：函数实现*/

#include <stdio.h>
#include <stdlib.h>
//#include "BitSet.h"

#pragma warning(disable:4996)
/*BitSet.h*/
/*集合的位向量表示：类型和界面定义*/


typedef struct {
	int size;		/*字符数组的长度*/
	char * array; /*位向量空间。每一数组元素保存8位。*/
} BitSet;

/*空集合的创建*/
BitSet * createEmptySet(int n);

/*将值为index的元素插入集合S*/
int insert(BitSet * s, int index);

/*将值为index的元素从集合S中删除*/
int delete1(BitSet * s, int index);

/*判断整数index的元素是否属于集合S*/
int member(BitSet * s, int index);

/*集合与集合的并*/
int union1(BitSet * s0, BitSet * s1, BitSet * s2);

/*集合与集合的交*/
int intersection(BitSet * s0, BitSet * s1, BitSet * s2);

/*集合与集合的差*/
int difference(BitSet * s0, BitSet * s1, BitSet * s2);


/*空集合的创建*/
BitSet * createEmptySet(int n) {	/*创建n位的位向量000...0*/
	int i;
	BitSet * s = (BitSet *)malloc(sizeof(BitSet));
	if (s != NULL) {
		s->size = (n + 7) / 8;
		s->array = (char *)malloc(s->size * sizeof(char));
		if (s->array != NULL) {
			for (i = 0; i < s->size; i++)
				s->array[i] = '\0';
			return s;
		}
	}
	return NULL;
}

/*将值为index的元素插入集合S*/
int insert(BitSet * s, int index) {	/*将位向量中下标为index的位，置为1*/
	if (index >= 0 && index >> 3 < s->size) {
		s->array[index >> 3] |= (1 << (index & 07)); 
		return 1;
	}
	return 0;
}

/*将值为index的元素从集合S中删除*/
int delete1(BitSet * s, int index) {	/*将位向量中下标为index的位，置为0*/
	if (index >= 0 && index >> 3 < s->size) {
		s->array[index >> 3] &= ~(1 << (index & 07)); 
		return 1;
	}
	return 0;
}

/*判断整数index的元素是否属于集合S*/
int member(BitSet * s, int index) {	/*检查位向量中下标为index的位置是否为1*/
	if (index >= 0 && index >> 3 < s->size &&(s->array[index >> 3] & (1 << (index & 07))))
		return 1;
	return 0;
}

/*集合与集合的并*/
int unionSet(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*当三个位向量长度相等时返回1，置s2为s0与s1的并；否则返回0。*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] | s1->array[i];
	return 1;
}

/*集合与集合的交*/
int intersection(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*当三个位向量长度相等时返回1，置s2为s0与s1的交；否则返回0。*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] & s1->array[i];
	return 1;
}

/*集合与集合的差*/
int difference(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*当三个位向量长度相等时返回1，置s2为s0与s1的差；否则返回0。*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] & ~s1->array[i];
	return 1;
}

/*集合中的向量以二进制方式打印出来*/
void printSet(BitSet *s) {
	int i,j;//i表示在数组array中的下标
	for(i=0;i<s->size;i++){
		//j表示左移的位数
		for(j=0;j<8;j++){
			//判断当前 位向量 的第j位是不是1 是1 则输出1
			//判断位向量的第0位 则要把它与 1000 0000 与 操作
			//1000 0000 & 1000 0000 = 1000 0000--->128 非零
			if(s->array[i]&(1<<(7-j))){//结果非0 则输出1
				printf("1 ");
			}
			else printf("0 ");
		}
		printf("\n");
	
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. 创建空集合S0,S1,S2\n");
	printf("2. 将值为index的元素插入集合S0中\n");
	printf("3. 将值为index的元素插入集合S1中\n");
	printf("4. 将值为index的元素从集合S0中删除\n");
	printf("5. 判断整数index的元素是否属于集合S0\n");
	printf("6. 集合与集合的并\n");
	printf("7. 集合与集合的交\n");
	printf("8. 集合与集合的差\n");
	printf("9. 打印集合S0\n");
	printf("10. 打印集合S1\n");
	printf("0. 退出\n");
	printf("************************\n");
}

void main() {
	/*
		实在不会再看题解，否则后果自负！！！
	*/
	int way,n,x,ans;
	BitSet *s0;
	BitSet *s1;
	BitSet *s2;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			//创建set
			printf("input the n:");
			scanf("%d",&n);
			s0=createEmptySet(n);
			s1=createEmptySet(n);
			s2=createEmptySet(n);
		}
		else if(way==2){
			//插入set
			printf("input value:");
			scanf("%d",&x);
			insert(s0,x);
		}
		else if(way==3){
			//插入set
			printf("input value:");
			scanf("%d",&x);
			insert(s1,x);
		}
		else if(way==4){
			//删除set
			printf("input value:");
			scanf("%d",&x);
			delete1(s0,x);
		}
		else if(way==5){
			//判断成员
			printf("input value:");
			scanf("%d",&x);
			ans=member(s0,x);
			if(ans==0) printf("NO\n");
			else printf("YES\n");
		}
		else if(way==6){
			//并集
			unionSet(s0,s1,s2);
			printSet(s2);
		}
		else if(way==7){
			//交集
			intersection(s0,s1,s2);
			printSet(s2);
		}
		else if(way==8){
			//差集
			difference(s0,s1,s2);
			printSet(s2);
		}
		else if(way==9){
			printSet(s0);
		}
		else if(way==10){
			printSet(s1);
		}

		
	}
	

}


