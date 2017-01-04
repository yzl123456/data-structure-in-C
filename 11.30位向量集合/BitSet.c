/*BitSet.c*/
/*���ϵ�λ������ʾ������ʵ��*/

#include <stdio.h>
#include <stdlib.h>
//#include "BitSet.h"

#pragma warning(disable:4996)
/*BitSet.h*/
/*���ϵ�λ������ʾ�����ͺͽ��涨��*/


typedef struct {
	int size;		/*�ַ�����ĳ���*/
	char * array; /*λ�����ռ䡣ÿһ����Ԫ�ر���8λ��*/
} BitSet;

/*�ռ��ϵĴ���*/
BitSet * createEmptySet(int n);

/*��ֵΪindex��Ԫ�ز��뼯��S*/
int insert(BitSet * s, int index);

/*��ֵΪindex��Ԫ�شӼ���S��ɾ��*/
int delete1(BitSet * s, int index);

/*�ж�����index��Ԫ���Ƿ����ڼ���S*/
int member(BitSet * s, int index);

/*�����뼯�ϵĲ�*/
int union1(BitSet * s0, BitSet * s1, BitSet * s2);

/*�����뼯�ϵĽ�*/
int intersection(BitSet * s0, BitSet * s1, BitSet * s2);

/*�����뼯�ϵĲ�*/
int difference(BitSet * s0, BitSet * s1, BitSet * s2);


/*�ռ��ϵĴ���*/
BitSet * createEmptySet(int n) {	/*����nλ��λ����000...0*/
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

/*��ֵΪindex��Ԫ�ز��뼯��S*/
int insert(BitSet * s, int index) {	/*��λ�������±�Ϊindex��λ����Ϊ1*/
	if (index >= 0 && index >> 3 < s->size) {
		s->array[index >> 3] |= (1 << (index & 07)); 
		return 1;
	}
	return 0;
}

/*��ֵΪindex��Ԫ�شӼ���S��ɾ��*/
int delete1(BitSet * s, int index) {	/*��λ�������±�Ϊindex��λ����Ϊ0*/
	if (index >= 0 && index >> 3 < s->size) {
		s->array[index >> 3] &= ~(1 << (index & 07)); 
		return 1;
	}
	return 0;
}

/*�ж�����index��Ԫ���Ƿ����ڼ���S*/
int member(BitSet * s, int index) {	/*���λ�������±�Ϊindex��λ���Ƿ�Ϊ1*/
	if (index >= 0 && index >> 3 < s->size &&(s->array[index >> 3] & (1 << (index & 07))))
		return 1;
	return 0;
}

/*�����뼯�ϵĲ�*/
int unionSet(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*������λ�����������ʱ����1����s2Ϊs0��s1�Ĳ������򷵻�0��*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] | s1->array[i];
	return 1;
}

/*�����뼯�ϵĽ�*/
int intersection(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*������λ�����������ʱ����1����s2Ϊs0��s1�Ľ������򷵻�0��*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] & s1->array[i];
	return 1;
}

/*�����뼯�ϵĲ�*/
int difference(BitSet * s0, BitSet * s1, BitSet * s2) {
	/*������λ�����������ʱ����1����s2Ϊs0��s1�Ĳ���򷵻�0��*/
	int i;
	if (s0->size != s1->size || s2->size != s1->size) 
		return 0;
	for (i = 0; i < s1->size; i++)
		s2->array[i] = s0->array[i] & ~s1->array[i];
	return 1;
}

/*�����е������Զ����Ʒ�ʽ��ӡ����*/
void printSet(BitSet *s) {
	int i,j;//i��ʾ������array�е��±�
	for(i=0;i<s->size;i++){
		//j��ʾ���Ƶ�λ��
		for(j=0;j<8;j++){
			//�жϵ�ǰ λ���� �ĵ�jλ�ǲ���1 ��1 �����1
			//�ж�λ�����ĵ�0λ ��Ҫ������ 1000 0000 �� ����
			//1000 0000 & 1000 0000 = 1000 0000--->128 ����
			if(s->array[i]&(1<<(7-j))){//�����0 �����1
				printf("1 ");
			}
			else printf("0 ");
		}
		printf("\n");
	
	}
}

void printScreen() {
	printf("\n**********************\n");
	printf("1. �����ռ���S0,S1,S2\n");
	printf("2. ��ֵΪindex��Ԫ�ز��뼯��S0��\n");
	printf("3. ��ֵΪindex��Ԫ�ز��뼯��S1��\n");
	printf("4. ��ֵΪindex��Ԫ�شӼ���S0��ɾ��\n");
	printf("5. �ж�����index��Ԫ���Ƿ����ڼ���S0\n");
	printf("6. �����뼯�ϵĲ�\n");
	printf("7. �����뼯�ϵĽ�\n");
	printf("8. �����뼯�ϵĲ�\n");
	printf("9. ��ӡ����S0\n");
	printf("10. ��ӡ����S1\n");
	printf("0. �˳�\n");
	printf("************************\n");
}

void main() {
	/*
		ʵ�ڲ����ٿ���⣬�������Ը�������
	*/
	int way,n,x,ans;
	BitSet *s0;
	BitSet *s1;
	BitSet *s2;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			//����set
			printf("input the n:");
			scanf("%d",&n);
			s0=createEmptySet(n);
			s1=createEmptySet(n);
			s2=createEmptySet(n);
		}
		else if(way==2){
			//����set
			printf("input value:");
			scanf("%d",&x);
			insert(s0,x);
		}
		else if(way==3){
			//����set
			printf("input value:");
			scanf("%d",&x);
			insert(s1,x);
		}
		else if(way==4){
			//ɾ��set
			printf("input value:");
			scanf("%d",&x);
			delete1(s0,x);
		}
		else if(way==5){
			//�жϳ�Ա
			printf("input value:");
			scanf("%d",&x);
			ans=member(s0,x);
			if(ans==0) printf("NO\n");
			else printf("YES\n");
		}
		else if(way==6){
			//����
			unionSet(s0,s1,s2);
			printSet(s2);
		}
		else if(way==7){
			//����
			intersection(s0,s1,s2);
			printSet(s2);
		}
		else if(way==8){
			//�
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


