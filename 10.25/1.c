#pragma warning(disable:4013)
#pragma warning(disable:4616)
#pragma warning(disable:4996)

/*LinkString.c*/
/*字符串的链接表示*/
/*注意：这里没有给出全部的函数实现*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct StrNode;						/* 链串的结点 */
typedef struct StrNode *PStrNode;		/* 结点指针类型 */
struct StrNode {					/* 链串的结点结构 */
	char      c;
	PStrNode  link;
};
typedef  struct  StrNode  *LinkString;  	/* 链串的类型 */
LinkString createNullStr_link(){
	LinkString pstr=(LinkString)malloc(sizeof(struct StrNode));
	pstr->link=NULL;
	return pstr;
}
LinkString subStr_link(LinkString s, int i, int j) {
/* 求从s所指的带头结点的链串中第i(i>0)个字符开始连续取j个字符所构成的子串 */
	LinkString s1;
	PStrNode p, q, t;
	int k;
	s1 = createNullStr_link();  /* 创建空链串 */
	if (s1 == NULL) {
		printf("Out of space!\n");
		return (NULL);
	}
	if (i<1 || j<1) 
		return(s1);	/* i,j值不合适，返回空串 */
	p = s;
	for (k = 1; k <= i; k++)  		/*找第i个结点*/
		if (p != NULL)
			p = p->link;
		else
			return(s1);
	if (p == NULL) 
		return(s1);
	t = s1;
	for (k = 1; k <= j; k++) 		 /*连续取j个字符*/
		if (p != NULL) {
			q = (PStrNode)malloc(sizeof(struct StrNode));
			if (q == NULL) {
				printf("Out of space!\n");
				return(s1);
			}
			q->c = p->c;
			q->link = NULL;
			t->link = q;			/* 结点放入子链串中 */
			t = q;
			p = p->link;
		}
		else {
			break;
		}
	return(s1);
}
LinkString append(LinkString s,char need[]){
	LinkString p=s;
	PStrNode tmp;
	int i=0,len=strlen(need);
	while(p->link!=NULL)
		p=p->link;
	for(i=0;i<len;i++){
		tmp = (PStrNode)malloc(sizeof(struct StrNode));
		tmp->c=need[i];
		tmp->link=NULL;
		p->link=tmp;
		p=p->link;
	}
	p->link=NULL;
	return s;
}
void printScreen() {
	printf("\n*************************\n");
	printf("1. 创建空字符串t\n");
	printf("2. 输入字符串t\n");
	printf("3. 打印字符串t\n");
	printf("4. 在t串中寻找位置从i开始之后j个字符所构成的子串\n");
	printf("5. 寻找t串中p串第一次出现的位置\n");
	printf("0. 退出\n");
	printf("*************************\n");
}
void printStr(LinkString s){
	LinkString p=s->link;
	while(p){
		printf("%c",p->c);
		p=p->link;
	}
	printf("\n");
}
int getLength(LinkString s){
	LinkString tmp=s->link;
	int cnt=0;
	while(tmp!=NULL){
		cnt++;tmp=tmp->link;
	}
	return cnt;
}
void KMP(LinkString s,char need[]){
	int i=0,len=strlen(need),ans=0,flag=0;
	LinkString p=s->link;
	while(p!=NULL){
		i=0;
		while(i<len){
			if(p->c==need[i]){
				i++;p=p->link;ans++;
			}
			else{
				p=p->link;ans++;
				break;
			}
		}
		if(i==len){
			printf("%d\n",ans-len+1);flag=1;break;
			//return ans-len+1;
		}
	}
	if(flag==0)
	printf("Not Found!");
	return ;
}



int KMP2(LinkString s,LinkString need){
	int i=0,len=getLength(need),ans=1,flag=0;
	LinkString p1=s->link,p2=need->link,need_start=need->link,last_start=p1;
	while(p1!=NULL&&p2!=NULL){
		p2=need_start;
		while(p2!=NULL){
			if(p1->c==p2->c){
				if(p2==need_start) 
					last_start=p1;
				p1=p1->link;p2=p2->link;
			}
			else{
				if(p1==last_start->link){
					last_start=last_start->link;
				}
				ans++;p1=last_start->link;
				break;
			}
		}
		if(p2==NULL){
			return ans;
			printf("%d\n",ans-len+1);flag=1;break;
			//return ans-len+1;
		}
	}
	//if(flag==0)
		//printf("Not Found!");
	return 0;
}
void main() {
	int way,start,end,ans;
	char need[100];
	LinkString str1,sub_str,str2;
	
	while(1){
		scanf("%d",&way);
		if(way==1){
			str1=createNullStr_link();
			str2=createNullStr_link();
		}
		else if(way==2){
			scanf("%s",need);
			str1=append(str1,need);
		}
		else if(way==3){
			printStr(str1);
		}
		else if(way==4){
			scanf("%d%d",&start,&end);
			 sub_str=subStr_link(str1,start ,end);
			 printStr(sub_str);
		}
		else if(way==5){
			scanf("%s",need);
			str2=createNullStr_link();
			str2=append(str2,need);
			ans=KMP2(str1,str2);
			printf("%d\n",ans);
		}
	}

}