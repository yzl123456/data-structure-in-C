#pragma warning(disable:4996)
/*HtTree.c*/
/*�������㷨*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXINT 10000

char s[100];

struct HtNode {	/* �����������Ľṹ */
	int ww;
	int parent, llink, rlink;
};
typedef struct HtNode  *PHtNode;

struct HtTree {	/* ���������ṹ */
	int    m;	        	/* �ⲿ���ĸ��� */
	int    root;	/* �����������������е��±� */
	struct HtNode  *ht;        /*���2*m-1���������� */
};
typedef struct HtTree  *PHtTree;	/* �����������͵�ָ������ */


PHtTree huffman(int m, int *w) {    /* �������m���ⲿ���Ĺ�������*/
	PHtTree  pht;
	int i, j, x1, x2, m1, m2;
	pht = (PHtTree)malloc(sizeof(struct HtTree));	/* ������������ռ� */
	if (pht == NULL) {
		printf("Out of space!! \n");
		return pht;
	}
	pht->ht = (PHtNode)malloc(sizeof(struct HtNode)*(2 * m - 1));
	pht->m = m;
	/*����ht����ռ�*/
	if (pht == NULL) {
		printf("Out of space!! \n");	return pht;
	}
	for (i = 0; i<2 * m - 1; i++) {	/* ��ht�����̬ */
		pht->ht[i].llink = -1;
		pht->ht[i].rlink = -1;
		pht->ht[i].parent = -1;
		if (i<m)
			pht->ht[i].ww = w[i];
		else
			pht->ht[i].ww = -1;
	}

	for (i = 0; i < m - 1; i++) {
		/* ÿѭ��һ�ι���һ���ڲ���� */
		m1 = MAXINT;
		m2 = MAXINT;
		/* ��ر�������ֵ */
		x1 = -1;
		x2 = -1;
		for (j = 0; j<m + i; j++)	/* ��������СȨ���޸����Ľ�� */
			if (pht->ht[j].ww<m1 && pht->ht[j].parent == -1)
				/*x1�д����СȨ���޸����Ľ���±�*/
			{
				m2 = m1;
				x2 = x1;
				m1 = pht->ht[j].ww;
				x1 = j;
			}
			else if (pht->ht[j].ww<m2 && pht->ht[j].parent == -1)
			{
				m2 = pht->ht[j].ww;
				x2 = j;
			}
			/*x2�д�Ŵ���СȨ���޸����Ľ���±�*/
			pht->ht[x1].parent = m + i;
			pht->ht[x2].parent = m + i;
			pht->ht[m + i].ww = m1 + m2;
			pht->ht[m + i].llink = x1;
			pht->ht[m + i].rlink = x2;
			/* �����ڲ���� */
	}
	pht->root = 2 * m - 2;
	return pht;
}


/*���ؽ��p�����ӽ����±�*/
PHtNode leftChild_link(PHtTree t, PHtNode p) {
	if (p->llink == -1) return NULL;
	return t->ht + p->llink;
}

/*���ؽ��p�����ӽ����±�*/
PHtNode rightChild_link(PHtTree t, PHtNode p) {
	if (p->rlink == -1) return NULL;
	return t->ht + p->rlink;
}

int visit(PHtNode  t) {
	printf("%d ", t->ww);
	return t->ww;
}


/*���������ȸ��������εĵݹ��㷨*/
void preOrder(PHtTree t, PHtNode  p) {
	if (p == NULL) return;
	visit(p);
	preOrder(t, leftChild_link(t, p));
	preOrder(t, rightChild_link(t, p));
}

/*���������Գ������εĵݹ��㷨*/
void inOrder(PHtTree t, PHtNode  p) {
	if (p == NULL) return;
	inOrder(t, leftChild_link(t, p));
	visit(p);
	inOrder(t, rightChild_link(t, p));
}

/*������������������εĵݹ��㷨*/
void postOrder(PHtTree t, PHtNode  p) {
	if (p == NULL) return;
	postOrder(t, leftChild_link(t, p));
	postOrder(t, rightChild_link(t, p));
	visit(p);
}

void printAllNode(PHtTree t) {
	int i;
	for (i = 0; i < t->m * 2 - 1; i++) {
		printf("%d ", t->ht[i].ww);
	}
	printf("\n");
}

void getHtCode(PHtTree t, int d) {
	//cur(current)��¼��ǰ�ڵ���������±� cur_par(current parent)��¼��ǰ�ڵ�ĸ��ڵ����������±�
	//ans���߹���·����k��ʾ·���ĳ���
	int i,cur,cur_par,ans[105],k=0;
	for(i=0;i<t->m*2-1;i++){
		if(t->ht[i].ww==d){//�ҵ���һ��������Ӧ���±�cur ���丸�ڵ��±�cur_par
			cur=i;cur_par=t->ht[cur].parent;
			break;
		}
	}

	//t->root��ʾ����������ڵ���������е��±꣬������ Ȩֵ238 ��������±�24
	//��cur��û�����ڵ�ʱ���������ϵ���
	while(cur!=t->root){
		if(t->ht[cur_par].llink==cur){//���cur��cur_par������� ��¼·��Ϊ0
			ans[k++]=0;
		}
		else ans[k++]=1;//�����Ҷ��Ӽ�¼·��Ϊ1
		
		cur=cur_par;//��cur_par����cur �������ϵ���
		cur_par=t->ht[cur].parent;//�ҵ���Ӧcur�ĸ��ڵ�
	}


	//ͨ��k�������
	printf("��������:");
	for(i=0;i<k;i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
	printf("����˳��:");
	for(i=k-1;i>=0;i--){
		printf("%d ",ans[i]);
	}

}

void reverse(char *s) {

}

void printScreen() {
	printf("\n*************************\n");
	printf("1. �����������\n");
	printf("2. �ȸ����������������\n");
	printf("3. �Գƴ��������������\n");
	printf("4. ������������������\n");
	printf("5. ��ӡ����������\n");
	printf("0. �˳�\n");
	printf("*************************\n");
}

void main() {
	//way��ʾ���� cnt��¼����ڵ�ĸ��� weight��¼�����Ȩֵ
	int i,x,weight[105]={0},way,cnt;
	//root��ʾָ�����������ָ��
	PHtTree root;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			cnt=0;
			while(scanf("%d",&x)&&x){//������xΪ0ʱ����
				weight[cnt]=x;
				cnt++;
			}
			//����ָ�����������ָ��
			root=huffman(cnt,weight);
		}
		else if(way==2){
			//x��ʾ����������ĸ��ڵ㣨238�� ��������е��±�
			x=root->root;
			//printf("----------------%d\n",x);//24
			preOrder(root,&root->ht[x]);//ע�⴫��ĵڶ���������һ��ָ��ýڵ��ָ�����ͣ�&ȡ��ַ�������ָ��
		}
		else if(way==3){
			x=root->root;//ͬway2
			inOrder(root,&root->ht[x]);
		}
		else if(way==4){
			x=root->root;//ͬway2
			postOrder(root,&root->ht[x]);
		}
		else if(way==5){
			printAllNode(root);//���
			printf("������Ҫ����Ľڵ�:");
			scanf("%d",&x);
			getHtCode(root,x);
		}
		else if(way==0){
			return ;
		}

	}


}