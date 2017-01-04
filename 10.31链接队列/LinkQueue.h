#pragma warning(disable:4996)
/*LinkQueue.h*/
/*链接队列：类型和界面函数声明 */

typedef char DataType;
struct  Node;
typedef  struct  Node  *PNode;
struct  Node			/* 结点结构 */
{
	DataType      info;
	PNode        link;
};
struct  LinkQueue 		/* 链接队列类型定义 */
{
	PNode  f;  		/* 头指针 */
	PNode  r;  		/* 尾指针 */
};
typedef  struct LinkQueue  *PLinkQueue;		/*链接队列类型的指针类型*/

											/*创建一个空队列*/
PLinkQueue  createEmptyQueue_link(void);

/*判断plqu所指的队列是否为空队*/
int  isEmptyQueue_link(PLinkQueue plqu);

/*入队运算，往plqu所指的队列中插入一个值为x的元素*/
void  enQueue_link(PLinkQueue plqu, DataType x);

/*出队运算，从plqu所指的队列中删除队头元素*/
void  deQueue_link(PLinkQueue plqu);

/*取队列头部元素的值*/
DataType  frontQueue_link(PLinkQueue plqu);

