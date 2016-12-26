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

Vertex firstVertex(Graph g) {
	printf("从%c出发的路径为：", g.vexs[0].value);
	return &g.vexs[0];
}

Vertex nextVertex(Graph g, Vertex v) {
	int i;
	for(i=0;i<g.n;i++)//执行完1轮后清空标记mark
		g.vexs[i].mark=0;
	printf("\n");
	if(getIndex(g,v)==g.n-1)//若是最后一个节点，则返回NULL
		return NULL;
	else {
		printf("从%c出发的路径为：", g.vexs[getIndex(g,v)+1].value);
		return &g.vexs[getIndex(g,v)+1];//否则返回下标+1	
	}
}
int getIndex(Graph g,Vertex v){//得到一个顶点在图中的下标
	int i,pos=-1;//仅适用于图中各节点值均不同
	for(i=0;i<g.n;i++){
		if(g.vexs[i].value==v->value)
			return i;
	}
}
Vertex firstAdjacent(Graph g, Vertex v) {//找到第一个相邻的节点
	int i;
	for(i=0;i<g.n;i++){//遍历
		if(g.vexs[i].mark==0&&g.arcs[getIndex(g,v)][i]==1){//若没有被访问过且存在 v的下标到节点i的下标的路径
			return &g.vexs[i];//返回这个节点i
		} 
	}
	return NULL;//不存在返回null
}

Vertex nextAdjacent(Graph g, Vertex vi, Vertex vj) {//找图G中与vi相邻的，相对相邻顶点vj的，下一个相邻顶点
	int i;
	int pos_i=getIndex(g,vi),pos_j=getIndex(g,vj);//得到对应的下标
	for(i=pos_j+1;i<g.n;i++){//for从j+1到n保证该节点时相对vj的下一个相邻节点
		if(g.vexs[i].mark==0&&g.arcs[pos_i][i]==1){//找未被访问过的节点并且该节点与vi节点有路径
			return &g.vexs[i];
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

void print(Graph g) {
	int i,j;
	for(i=0;i<g.n;i++){//2层for打印图
		for(j=0;j<g.n;j++){
			printf("%d ",g.arcs[i][j]);
		}
		printf("\n");
	}
}

void main(void) {
	/*
		请自行思考后再看此题解，否则后果自负！
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
}