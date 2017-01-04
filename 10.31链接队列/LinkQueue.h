#pragma warning(disable:4996)
/*LinkQueue.h*/
/*���Ӷ��У����ͺͽ��溯������ */

typedef char DataType;
struct  Node;
typedef  struct  Node  *PNode;
struct  Node			/* ���ṹ */
{
	DataType      info;
	PNode        link;
};
struct  LinkQueue 		/* ���Ӷ������Ͷ��� */
{
	PNode  f;  		/* ͷָ�� */
	PNode  r;  		/* βָ�� */
};
typedef  struct LinkQueue  *PLinkQueue;		/*���Ӷ������͵�ָ������*/

											/*����һ���ն���*/
PLinkQueue  createEmptyQueue_link(void);

/*�ж�plqu��ָ�Ķ����Ƿ�Ϊ�ն�*/
int  isEmptyQueue_link(PLinkQueue plqu);

/*������㣬��plqu��ָ�Ķ����в���һ��ֵΪx��Ԫ��*/
void  enQueue_link(PLinkQueue plqu, DataType x);

/*�������㣬��plqu��ָ�Ķ�����ɾ����ͷԪ��*/
void  deQueue_link(PLinkQueue plqu);

/*ȡ����ͷ��Ԫ�ص�ֵ*/
DataType  frontQueue_link(PLinkQueue plqu);

