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

//Queue
typedef Vertex DataType;

struct  SeqQueue {	      /* ˳��������Ͷ��� */
	int  MAXNUM;      /* ���������Ԫ�ظ��� */
	int  f, r;
	DataType  *q;
};
typedef  struct SeqQueue  *PSeqQueue;	/* ˳��������͵�ָ������ */

/*����һ���ն���*/
PSeqQueue  createEmptyQueue_seq(int m);

/*�ж�paqu��ָ�Ķ����Ƿ�Ϊ�ն���*/
int  isEmptyQueue_seq(PSeqQueue paqu);

/*������㣬�����в���ʱ����Ԫ��x����paqu��ָ���еĶ�β*/
void  enQueue_seq(PSeqQueue paqu, DataType x);

/*�������㣬�����в���ʱ��ɾ��paqu��ָ���еĶ�ͷԪ��*/
void  deQueue_seq(PSeqQueue paqu);

/*��paqu��ָ�Ķ��в���ʱ��ȡ����ͷ��Ԫ�أ����б����ֲ���*/
DataType  frontQueue_seq(PSeqQueue paqu);

PSeqQueue createEmptyQueue_seq(int m){
	PSeqQueue tmp=(PSeqQueue )malloc(sizeof(struct SeqQueue)); 
	tmp->MAXNUM=m;
	tmp->f=0;tmp->r=0;
	tmp->q=(DataType *)malloc(sizeof(DataType)*m);
	return tmp;
}
/* �ڶ�β����Ԫ��x */
void  enQueue_seq(PSeqQueue paqu, DataType x) {
	if (paqu == NULL)
		printf("����û�д������޷�����Ԫ��!");
	else if ((paqu->r + 1) % paqu->MAXNUM == paqu->f){
		printf("Full queue.\n");
	}
	else {
		paqu->q[paqu->r] = x;
		paqu->r = (paqu->r + 1) % paqu->MAXNUM;
	}
}

/* ɾ������ͷ��Ԫ�� */
void  deQueue_seq(PSeqQueue paqu){
	if (paqu == NULL)
		printf("����û�д���!");
	else if (paqu->f == paqu->r)
		printf("Empty Queue.\n");
	else {
		paqu->f = (paqu->f + 1) % paqu->MAXNUM;
	}
}

DataType  frontQueue_seq(PSeqQueue paqu)
{
	if (paqu == NULL) {
		printf("����û�д���!\n");
		return '\0';
	}
	else if (paqu->f == paqu->r) {
		printf("������û��Ԫ��!\n");
		return '\0';
	}
	else
		return (paqu->q[paqu->f]);
}

Vertex firstVertex(Graph g) {
	printf("��%c������·��Ϊ��", g.vexs[0].value);
	return &g.vexs[0];
}

Vertex nextVertex(Graph g, Vertex v) {
	int i;
	printf("\n");

	// �¸��������֮ǰ, �ָ�mark������
	for (i = 0; i < g.n; i++) {
		g.vexs[i].mark = 0;
	}

	// ��ȡ�¸�����
	for (i = 0; i < g.n; i++) {
		if (g.vexs[i].value == v->value && i < g.n - 1) {
				printf("��%c������·��Ϊ��", g.vexs[i + 1].value);
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
		dfs(g, v1);/*�ݹ����*/
}

/*ͼ��������������㷨*/
void dft(Graph g) {
	Vertex v;
	for (v = firstVertex(g); v != NULL; v = nextVertex(g, v))
		if (v->mark == 0)
			dfs(g, v);  /*��Ϊͼg��һ����ͨ*/
}

//BFS
void bfs(Graph g,Vertex v){
	Vertex v1,v2;
	PSeqQueue q=createEmptyQueue_seq(100);//��������
	enQueue_seq(q,v);//���
	while(q->r!=q->f){//���зǿ�
		v1=frontQueue_seq(q);deQueue_seq(q);//ȡ��ͷ��㣬����
		if(v1->mark==1) continue;//���ʹ���continue
		printf("%c ",v1->value);//δ���ʹ����ӡ
		v1->mark=1;v2=firstAdjacent(g,v1);//��Ǹշ��ʹ��Ľڵ㣬���ҵ���v1���ڵĵ�һ������
		while(v2!=NULL){//���ϵ�����һ�����ڵĽڵ�
			if(v2->mark==0) enQueue_seq(q,v2);//û�з��ʹ������
			v2=nextAdjacent(g,v1,v2);//����һ�����ڵĶ���
		}
	}

}
//BFT
void bft(Graph g){
	Vertex v;
	for(v=firstVertex(g);v!=NULL;v=nextVertex(g,v))//�Ӳ�ͬ����BFS
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
	������˼����ʵ�ڲ����ٿ�����⣬�������Ը���
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
	printf("BFT--------\n");
	bft(g);//BFT
}