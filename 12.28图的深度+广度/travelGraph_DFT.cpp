#include<stdio.h>
#include <stdlib.h>
#define N 5

/*图的周游*/
//typedef char VerType;
typedef int AdjType;

typedef struct {
	char value;
	int mark;
}VerType;

typedef VerType* Vertex;

typedef struct {
	int n;				    /* 图的顶点个数 */
	Vertex vexs;			/* 顶点信息 */
	AdjType arcs[N][N];		/* 边信息 */
}Graph;

//Queue
typedef Vertex DataType;

struct  SeqQueue {	      /* 顺序队列类型定义 */
	int  MAXNUM;      /* 队列中最大元素个数 */
	int  f, r;
	DataType  *q;
};
typedef  struct SeqQueue  *PSeqQueue;	/* 顺序队列类型的指针类型 */

/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq(int m);

/*判断paqu所指的队列是否为空队列*/
int  isEmptyQueue_seq(PSeqQueue paqu);

/*入队运算，当队列不满时，将元素x插入paqu所指队列的队尾*/
void  enQueue_seq(PSeqQueue paqu, DataType x);

/*出队运算，当队列不空时，删除paqu所指队列的队头元素*/
void  deQueue_seq(PSeqQueue paqu);

/*当paqu所指的队列不空时，取队列头部元素，队列本身保持不变*/
DataType  frontQueue_seq(PSeqQueue paqu);

PSeqQueue createEmptyQueue_seq(int m){
	PSeqQueue tmp=(PSeqQueue )malloc(sizeof(struct SeqQueue)); 
	tmp->MAXNUM=m;
	tmp->f=0;tmp->r=0;
	tmp->q=(DataType *)malloc(sizeof(DataType)*m);
	return tmp;
}
/* 在队尾插入元素x */
void  enQueue_seq(PSeqQueue paqu, DataType x) {
	if (paqu == NULL)
		printf("队列没有创建，无法插入元素!");
	else if ((paqu->r + 1) % paqu->MAXNUM == paqu->f){
		printf("Full queue.\n");
	}
	else {
		paqu->q[paqu->r] = x;
		paqu->r = (paqu->r + 1) % paqu->MAXNUM;
	}
}

/* 删除队列头部元素 */
void  deQueue_seq(PSeqQueue paqu){
	if (paqu == NULL)
		printf("队列没有创建!");
	else if (paqu->f == paqu->r)
		printf("Empty Queue.\n");
	else {
		paqu->f = (paqu->f + 1) % paqu->MAXNUM;
	}
}

DataType  frontQueue_seq(PSeqQueue paqu)
{
	if (paqu == NULL) {
		printf("队列没有创建!\n");
		return '\0';
	}
	else if (paqu->f == paqu->r) {
		printf("队列中没有元素!\n");
		return '\0';
	}
	else
		return (paqu->q[paqu->f]);
}

Vertex firstVertex(Graph g) {
	printf("从%c出发的路径为：", g.vexs[0].value);
	return &g.vexs[0];
}

Vertex nextVertex(Graph g, Vertex v) {
	int i;
	printf("\n");

	// 下个顶点遍历之前, 恢复mark的设置
	for (i = 0; i < g.n; i++) {
		g.vexs[i].mark = 0;
	}

	// 获取下个顶点
	for (i = 0; i < g.n; i++) {
		if (g.vexs[i].value == v->value && i < g.n - 1) {
				printf("从%c出发的路径为：", g.vexs[i + 1].value);
				return &g.vexs[i + 1];
		}
	}
	return NULL;
}

Vertex firstAdjacent(Graph g, Vertex v) {
	int i, j;
	for (i = 0; i < g.n; i++) {
		if (g.vexs[i].value == v->value) {
			for (j = 0; j < g.n; j++) {
				if (g.arcs[i][j] == 1 && g.vexs[j].mark != 1) {
					//printf("%c ", g.vexs[j].value);
					return &g.vexs[j];
				}
			}
		}
	}
	return NULL;
}

Vertex nextAdjacent(Graph g, Vertex vi, Vertex vj) {
	int i, j, w;
	for (w = 0; w < g.n; w++) {
		if (g.vexs[w].value == vi->value)
			i = w;
		if (g.vexs[w].value == vj->value)
			j = w;
	}

	for (w = j + 1; w < g.n; w++) {
		if (g.arcs[i][w] == 1 && g.vexs[w].mark != 1) {
			return &g.vexs[w];
		}
	}
	return NULL;
}

void dfs(Graph g, Vertex v) {
	Vertex v1;
	v->mark = 1;
	printf("%c ", v->value);
	for (v1 = firstAdjacent(g, v); v1 != NULL; v1 = nextAdjacent(g, v, v1))
		dfs(g, v1);/*递归调用*/
}

/*图的深度优先周游算法*/
void dft(Graph g) {
	Vertex v;
	for (v = firstVertex(g); v != NULL; v = nextVertex(g, v))
		if (v->mark == 0)
			dfs(g, v);  /*因为图g不一定连通*/
}

//BFS
void bfs(Graph g,Vertex v){
	Vertex v1,v2;
	PSeqQueue q=createEmptyQueue_seq(100);//创建队列
	enQueue_seq(q,v);//入队
	while(q->r!=q->f){//队列非空
		v1=frontQueue_seq(q);deQueue_seq(q);//取出头结点，出队
		if(v1->mark==1) continue;//访问过则continue
		printf("%c ",v1->value);//未访问过则打印
		v1->mark=1;v2=firstAdjacent(g,v1);//标记刚访问过的节点，并找到与v1相邻的第一个顶点
		while(v2!=NULL){//不断地找下一个相邻的节点
			if(v2->mark==0) enQueue_seq(q,v2);//没有访问过则入队
			v2=nextAdjacent(g,v1,v2);//找下一个相邻的顶点
		}
	}

}
//BFT
void bft(Graph g){
	Vertex v;
	for(v=firstVertex(g);v!=NULL;v=nextVertex(g,v))//从不同顶点BFS
		if(v->mark==0) bfs(g,v);
}
void print(Graph g) {
	int i, j;
	printf("    ");
	for (i = 0; i < N; i++) {
		printf("  [%c]", g.vexs[i]);
	}
	printf("\n");
	for (i = 0; i < N; i++) {
		printf("[%c] ", g.vexs[i]);
		for (j = 0; j < N; j++) {
			printf("%4d ", g.arcs[i][j]);
		}
		printf("\n");
	}
}

void main(void) {
	/*
	请自行思考后实在不会再看此题解，否则后果自负！
	*/
	Graph g;
	VerType vexs[] = { { 'a', 0 },{ 'b', 0 },{ 'c', 0 },{ 'd', 0 },{ 'e', 0 } };
	AdjType adjType[N][N] = { { 0, 1, 0, 0, 0 },{ 1, 0, 0, 0, 1 },{ 0, 1, 0, 1, 0 },{ 1, 0, 0, 0, 0 },{ 0, 0, 0, 1, 0 } };
	int i, j;
	g.vexs = vexs;
	g.n = N;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			g.arcs[i][j] = adjType[i][j];
		}
	}

	/*图的深度优先周游算法*/
	print(g);
	dft(g);
	printf("BFT--------\n");
	bft(g);//BFT
}