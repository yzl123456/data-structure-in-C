#pragma warning(disable:4996)
/*HtTree.c*/
/*哈夫曼算法*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXINT 10000

char s[100];

struct HtNode {	/* 哈夫曼树结点的结构 */
	int ww;
	int parent, llink, rlink;
};
typedef struct HtNode  *PHtNode;

struct HtTree {	/* 哈夫曼树结构 */
	int    m;	        	/* 外部结点的个数 */
	int    root;	/* 哈夫曼树根在数组中的下标 */
	struct HtNode  *ht;        /*存放2*m-1个结点的数组 */
};
typedef struct HtTree  *PHtTree;	/* 哈夫曼树类型的指针类型 */


PHtTree huffman(int m, int *w) {    /* 构造具有m个外部结点的哈夫曼树*/
	PHtTree  pht;
	int i, j, x1, x2, m1, m2;
	pht = (PHtTree)malloc(sizeof(struct HtTree));	/* 分配哈夫曼树空间 */
	if (pht == NULL) {
		printf("Out of space!! \n");
		return pht;
	}
	pht->ht = (PHtNode)malloc(sizeof(struct HtNode)*(2 * m - 1));
	pht->m = m;
	/*分配ht数组空间*/
	if (pht == NULL) {
		printf("Out of space!! \n");	return pht;
	}
	for (i = 0; i<2 * m - 1; i++) {	/* 置ht数组初态 */
		pht->ht[i].llink = -1;
		pht->ht[i].rlink = -1;
		pht->ht[i].parent = -1;
		if (i<m)
			pht->ht[i].ww = w[i];
		else
			pht->ht[i].ww = -1;
	}

	for (i = 0; i < m - 1; i++) {
		/* 每循环一次构造一个内部结点 */
		m1 = MAXINT;
		m2 = MAXINT;
		/* 相关变量赋初值 */
		x1 = -1;
		x2 = -1;
		for (j = 0; j<m + i; j++)	/* 找两个最小权的无父结点的结点 */
			if (pht->ht[j].ww<m1 && pht->ht[j].parent == -1)
				/*x1中存放最小权的无父结点的结点下标*/
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
			/*x2中存放次最小权的无父结点的结点下标*/
			pht->ht[x1].parent = m + i;
			pht->ht[x2].parent = m + i;
			pht->ht[m + i].ww = m1 + m2;
			pht->ht[m + i].llink = x1;
			pht->ht[m + i].rlink = x2;
			/* 构造内部结点 */
	}
	pht->root = 2 * m - 2;
	return pht;
}


/*返回结点p的左子结点的下标*/
PHtNode leftChild_link(PHtTree t, PHtNode p) {
	if (p->llink == -1) return NULL;
	return t->ht + p->llink;
}

/*返回结点p的右子结点的下标*/
PHtNode rightChild_link(PHtTree t, PHtNode p) {
	if (p->rlink == -1) return NULL;
	return t->ht + p->rlink;
}

int visit(PHtNode  t) {
	printf("%d ", t->ww);
	return t->ww;
}


/*哈夫曼树先根次序周游的递归算法*/
void preOrder(PHtTree t, PHtNode  p) {
	if (p == NULL) return;
	visit(p);
	preOrder(t, leftChild_link(t, p));
	preOrder(t, rightChild_link(t, p));
}

/*哈夫曼树对称序周游的递归算法*/
void inOrder(PHtTree t, PHtNode  p) {
	if (p == NULL) return;
	inOrder(t, leftChild_link(t, p));
	visit(p);
	inOrder(t, rightChild_link(t, p));
}

/*哈夫曼树后根次序周游的递归算法*/
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
	//cur(current)记录当前节点在数组的下标 cur_par(current parent)记录当前节点的父节点在数组表的下标
	//ans存走过的路径，k表示路径的长度
	int i,cur,cur_par,ans[105],k=0;
	for(i=0;i<t->m*2-1;i++){
		if(t->ht[i].ww==d){//找到第一个点所对应的下标cur 及其父节点下标cur_par
			cur=i;cur_par=t->ht[cur].parent;
			break;
		}
	}

	//t->root表示建完树后根节点在数组表中的下标，即书中 权值238 在数组表下标24
	//当cur还没到根节点时，继续往上迭代
	while(cur!=t->root){
		if(t->ht[cur_par].llink==cur){//如果cur是cur_par的左儿子 记录路径为0
			ans[k++]=0;
		}
		else ans[k++]=1;//否则右儿子记录路径为1
		
		cur=cur_par;//讲cur_par赋给cur 继续往上迭代
		cur_par=t->ht[cur].parent;//找到对应cur的父节点
	}


	//通过k遍历输出
	printf("编码逆序:");
	for(i=0;i<k;i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
	printf("编码顺序:");
	for(i=k-1;i>=0;i--){
		printf("%d ",ans[i]);
	}

}

void reverse(char *s) {

}

void printScreen() {
	printf("\n*************************\n");
	printf("1. 构造哈夫曼树\n");
	printf("2. 先根次序遍历哈夫曼树\n");
	printf("3. 对称次序遍历哈夫曼树\n");
	printf("4. 后根次序遍历哈夫曼树\n");
	printf("5. 打印哈夫曼编码\n");
	printf("0. 退出\n");
	printf("*************************\n");
}

void main() {
	//way表示操作 cnt记录输入节点的个数 weight记录输入的权值
	int i,x,weight[105]={0},way,cnt;
	//root表示指向哈夫曼树的指针
	PHtTree root;
	while(1){
		printScreen();
		scanf("%d",&way);
		if(way==1){
			cnt=0;
			while(scanf("%d",&x)&&x){//当输入x为0时跳出
				weight[cnt]=x;
				cnt++;
			}
			//创建指向哈夫曼树的指针
			root=huffman(cnt,weight);
		}
		else if(way==2){
			//x表示构建完树后的根节点（238） 在数组表中的下标
			x=root->root;
			//printf("----------------%d\n",x);//24
			preOrder(root,&root->ht[x]);//注意传入的第二个参数是一个指向该节点的指针类型，&取地址把它变成指针
		}
		else if(way==3){
			x=root->root;//同way2
			inOrder(root,&root->ht[x]);
		}
		else if(way==4){
			x=root->root;//同way2
			postOrder(root,&root->ht[x]);
		}
		else if(way==5){
			printAllNode(root);//输出
			printf("请输入要编码的节点:");
			scanf("%d",&x);
			getHtCode(root,x);
		}
		else if(way==0){
			return ;
		}

	}


}