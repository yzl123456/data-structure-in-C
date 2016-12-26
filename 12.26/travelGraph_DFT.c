#include<stdio.h>
#include <stdlib.h>
#define N 5

/*ͼ������*/
//typedef char VerType;
typedef int AdjType;

typedef struct {
	char value;
	int mark;
}VerType;

typedef VerType* Vertex;

typedef struct {
	int n;				    /* ͼ�Ķ������ */
	Vertex vexs;			/* ������Ϣ */
	AdjType arcs[N][N];		/* ����Ϣ */
}Graph;

Vertex firstVertex(Graph g) {
	printf("��%c������·��Ϊ��", g.vexs[0].value);
	return &g.vexs[0];
}

Vertex nextVertex(Graph g, Vertex v) {
	int i;
	for(i=0;i<g.n;i++)//ִ����1�ֺ���ձ��mark
		g.vexs[i].mark=0;
	printf("\n");
	if(getIndex(g,v)==g.n-1)//�������һ���ڵ㣬�򷵻�NULL
		return NULL;
	else {
		printf("��%c������·��Ϊ��", g.vexs[getIndex(g,v)+1].value);
		return &g.vexs[getIndex(g,v)+1];//���򷵻��±�+1	
	}
}
int getIndex(Graph g,Vertex v){//�õ�һ��������ͼ�е��±�
	int i,pos=-1;//��������ͼ�и��ڵ�ֵ����ͬ
	for(i=0;i<g.n;i++){
		if(g.vexs[i].value==v->value)
			return i;
	}
}
Vertex firstAdjacent(Graph g, Vertex v) {//�ҵ���һ�����ڵĽڵ�
	int i;
	for(i=0;i<g.n;i++){//����
		if(g.vexs[i].mark==0&&g.arcs[getIndex(g,v)][i]==1){//��û�б����ʹ��Ҵ��� v���±굽�ڵ�i���±��·��
			return &g.vexs[i];//��������ڵ�i
		} 
	}
	return NULL;//�����ڷ���null
}

Vertex nextAdjacent(Graph g, Vertex vi, Vertex vj) {//��ͼG����vi���ڵģ�������ڶ���vj�ģ���һ�����ڶ���
	int i;
	int pos_i=getIndex(g,vi),pos_j=getIndex(g,vj);//�õ���Ӧ���±�
	for(i=pos_j+1;i<g.n;i++){//for��j+1��n��֤�ýڵ�ʱ���vj����һ�����ڽڵ�
		if(g.vexs[i].mark==0&&g.arcs[pos_i][i]==1){//��δ�����ʹ��Ľڵ㲢�Ҹýڵ���vi�ڵ���·��
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
		dfs(g, v1);/*�ݹ����*/
}

/*ͼ��������������㷨*/
void dft(Graph g) {
	Vertex v;
	for (v = firstVertex(g); v != NULL; v = nextVertex(g, v))
		if (v->mark == 0)
			dfs(g, v);  /*��Ϊͼg��һ����ͨ*/
}

void print(Graph g) {
	int i,j;
	for(i=0;i<g.n;i++){//2��for��ӡͼ
		for(j=0;j<g.n;j++){
			printf("%d ",g.arcs[i][j]);
		}
		printf("\n");
	}
}

void main(void) {
	/*
		������˼�����ٿ�����⣬�������Ը���
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

	/*ͼ��������������㷨*/
	print(g);
	dft(g);
}