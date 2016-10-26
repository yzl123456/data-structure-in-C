#pragma warning(disable:4996)
/*SeqQueue.h*/
/*顺序队列：类型和界面函数声明 */

typedef char DataType;

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
