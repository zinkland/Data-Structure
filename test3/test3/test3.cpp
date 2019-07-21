#include "pch.h"
#include <iostream>
using namespace std;
typedef struct node
{
	char data;
	struct node *lchild, *rchild;
}BinTNode, *BinTree;
//以下为队列
typedef struct QNode 
{
	BinTNode data;
	struct QNode * next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
//以下为堆栈
typedef struct StackNode
{
	BinTNode data;
	struct StackNode *next;
}StackNode,*LinkStack;
void InitStack(LinkStack &S)
{
	S = NULL;
}
void Push(LinkStack &S, BinTNode e)
{
	StackNode *p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
}
void Pop(LinkStack &S)
{
	StackNode *p = new StackNode;
	p = S;
	S = S->next;
	delete p;
}

void Pop_print(LinkStack &S)
{
	int n=0 ,m= 0;
	int i = 0;
	StackNode *p = new StackNode;
	p = S;
	while (S != NULL)
	{
		n++;
		S = S->next;
	}
	BinTNode *a = new BinTNode[n+1];
	while (p!=NULL)
	{
		a[i] = p->data;
		i++;
		p = p->next;
	}
	while (i != 0)
	{
		printf("->%c", a[i-1]);
		i--;
	}
}

int SearchNode(BinTNode &root,LinkStack &S, char node)
{
	if (&root == NULL)
	{
		return 0;
	}
	Push(S, root);
	if (root.data == node)
	{
		return 1;
	}
	int b = 0;
	//先去左子树找
	if (root.lchild != NULL)
	{
		b=SearchNode(*root.lchild, S, node);
	}
	//左子树找不到并且右子树不为空的情况下才去找
	if (!b&&root.rchild != NULL)		//b==0
	{
		b=SearchNode(*root.rchild, S, node);
	}
	//左右都找不到，弹出栈顶元素
	if (!b)
	{
		Pop(S);
	}
	//return b;
}

void Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = new QNode;
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q,BinTNode &e)
{
	QNode *p;
	p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

void DeQueue(LinkQueue &Q)
{
	QNode *p;
	if (Q.front==Q.rear)
	{
		printf("Error");
	}
	p = Q.front->next;
	
	Q.front->next = p->next;
	if (Q.rear==p)
	{
		Q.rear = Q.front;
	}
	delete p;
}

int IsEmptyQueue(LinkQueue &queue) 
{
	if (queue.front == queue.rear) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

 BinTNode QueueFront(LinkQueue &Q)
{
	if (Q.front!=Q.rear)
	{
		return Q.front->next->data;
	}
}

void BinaryTreeLevelOrder(BinTNode &root)
{
	LinkQueue Q;
	Init_Queue(Q);
	EnQueue(Q,root);
	while (IsEmptyQueue(Q))
	{
		//出队保存队头并访问
		BinTNode front = QueueFront(Q);
		printf(" %c", front.data);
		DeQueue(Q);
		//将出队结点的左子树根入队
		if (front.lchild)
			EnQueue(Q, *front.lchild);
		//将出队结点的右子树根入队
		if (front.rchild)
			EnQueue(Q, *front.rchild);
	}
}

void creat_tree(BinTree &T)
{
	char ch;
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}	
	else
	{
		T=new BinTNode;
		T->data=ch;
		creat_tree(T->lchild);
		creat_tree(T->rchild);
	}
}

void PreOrderTraverse(BinTree T)
{
	if (T)
	{
		cout << T->data;
		printf(" ");
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BinTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data;
		printf(" ");
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BinTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
		printf(" ");
	}
}

int main()
{
	int i, j, k, m, n;
	BinTree H;
	while (1)
	{
		printf("\nMenu:\n");
		printf("1．建立二叉树存储结构\n");
		printf("2．求二叉树的先序遍历\n");
		printf("3．求二叉树的中序遍历\n");
		printf("4．求二叉树的后序遍历\n");
		printf("5．求二叉树的层次遍历\n");
		printf("6．求给定结点的路径\n");
		printf("0．退出系统\n");
		printf("\n输入所要执行操作:");
		scanf("%d", &m);
		switch (m)
		{
		case 0:
			exit(0);
			break;
		case 1:
			H = new BinTNode;
			printf("输入结点:");
			creat_tree(H);
			break;
		case 2:
			PreOrderTraverse(H);
			break;
		case 3:
			InOrderTraverse(H);
			break;
		case 4:
			PostOrderTraverse(H);
			break;
		case 5:
			BinaryTreeLevelOrder(*H);
			break;
		case 6:
			char p;
			printf("输入待查找结点:");
			scanf(" %c", &p);
			LinkStack *S = new LinkStack;
			InitStack(*S);
			SearchNode(*H, *S, p);
			if (*S==NULL)
			{
				printf("\n该节点不存在");
			}
			Pop_print(*S);
			
			
			break;
		}
	}	
}
		//测试
		//ABC##DE#G##F###		