#pragma warning(disable:4996)
/*SeqQueue.h*/
/*˳����У����ͺͽ��溯������ */

typedef char DataType;

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
