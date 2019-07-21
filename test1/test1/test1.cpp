#include "pch.h"
#include <iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
typedef struct HNode
{
	char	roomN[7];	//客房名称
	float   Price;		//标准价格
	float   PriceL;	//入住价格(默认值=标准价格*80%)
	int	   Beds;		//床位数Beds
	char	   State[5];	//入住状态(值域："空闲"、"入住"、"预订"，默认值为"空闲")
	struct HNode  *next;	//指针域
}Hotel, *HLink;

void Build(HLink &H)
{	
	HNode *p;
	HNode *rear;
	FILE *fp;
	H = (HLink)malloc(sizeof(HNode));
	fp = fopen("indata.txt", "r");
	rear = H;
	while (!feof(fp))
	{
		p = (HLink)malloc(sizeof(HNode));
		fscanf(fp,"%s %f %d", &p->roomN, &p->Price, &p->Beds);//客房名称、标准价格、床位数
		p->PriceL = (p->Price)*0.8;
		strcpy(p->State, "空闲");
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
	fclose(fp);
}
void Exp(HLink H)
{	
	HNode *p ;
	p= H->next;
	printf("------------------------------------------------\n");
	printf("客房名称    标准价格    入住价格  床位数    状态\n");
	while (p)
	{	
		printf("%s%12.1f%12.1f%8d%11s\n", p->roomN,p->Price,p->PriceL,p->Beds,p->State);
		p = p->next;
	}
	printf("------------------------------------------------\n");
}

int Find(HLink &H, char *roomN)
{
	int i = 1;
	HNode *p;
	p = H->next;
	while (p)
	{
		if (strcmp(p->roomN,roomN)==0)
		{
			return i;
		}
		i++;
		p = p->next;
	}
	return 0;
}

void updateH(HLink &H, int beds ,char *state)
{
	HNode *p;
	p = H->next;
	while (p)
	{
		if (p->Beds == beds)
		{
			strcpy(p->State, state);
		}
		p = p->next;
	}
}

void Add(HLink &H)
{
	HNode *p;
	p = H->next;
	while (p)
	{
		if (strcmp(p->State,"空闲")==0)
		{
			p->PriceL = (p->PriceL)*1.2;
		}
		p = p->next;
	}
}
HLink FirstH(HLink &H)
{
	float max;
	HNode *p,*q;
	if (H->next==NULL)
	{
		return NULL;
	}
	q = H->next;
	p = q;
	max = q->PriceL;
	while (q)
	{
		if (q->PriceL>max)
		{
			max = q->PriceL;
		}
		q = q->next;
	}
	q = H;
	while (p)
	{
		if (p->PriceL==max)
		{
			break;
		}
		q = q->next;
		p = p->next;
	}
	if (q->next==NULL)
	{
		p = q;
		delete q;
		return p;
		
	}
	else
	{
		q->next = p->next;
		return p;
	}
}
void MoveK1(HLink &H, int k)
{
	HNode *p,*rear;
	p= H->next;
	rear = p;
	int count=1;
	while (p!=NULL)
	{
		if (count<=k+1)
		{
			count++;
		}
		else
		{
			rear = rear->next;
		}
		p = p->next;
	}
	HNode *m,*l,*n;
	n = rear->next->next;
	l = rear->next;
	m = H->next;
	l->next = m;
	H->next = l;
	rear->next = n;
}

void ReverseN2(HLink &H)
{
	HNode *p, *r, *rear, *q, *prev = NULL;
	p = H->next;
	rear = p;
	r = H;
	while (p)
	{
		p = p->next->next;
		rear = rear->next;
		r = r->next;
	}
	while (rear)
	{
		q = rear->next;
		rear->next = prev;
		prev = rear;
		rear = q;
	}
	r->next = prev;
}

void SortPriceL(HLink &H)
{	
	
	HNode *p = new HNode;
	HLink K = p;
	while (H->next)
	{
		p->next =FirstH(H);
		p = p->next;
	}
	H = K;
}
void upBed(HLink &H, int beds)
{
	char roomN[10],state[3];
	float price;
	HNode *p,*a,*b,*c;
	HNode *A = new HNode;
	HNode *B = new HNode;
	HNode *C = new HNode;
	a = A;
	b = B;
	c = C;
	printf("\n新建客房名称:\n");
	scanf("%s", roomN);
	strcpy(B->roomN, roomN);
	printf("输入标准价格:\n");
	scanf("%f", &price);
	B->Price = price;
	B->PriceL = price * 0.8;
	B->Beds = beds;
	strcpy(B->State, "空闲");
	p = H->next;
	while (p)
	{
		if (p->Beds>beds)
		{
			a->next = p;
			a = a->next;
			p = p->next;
		}
		if (p == NULL)
		{
			break;
		}
		if (p->Beds<=beds)
		{
			c->next = p;
			c = c->next;
			p = p->next;
		}
	}
	a->next = B;
	p = C;
	while (p)
	{
		if (p->next==NULL||p->next->Beds>beds)
		{
			p->next = NULL;
			break;
		}
		p = p->next;
	}
	B->next = C->next;
	H = A;
}

void main()
{	
	char n[7];
	int beds, m = 1;
	HLink H;
	HNode *q;
	Build(H);
	printf("初始房屋信息:\n");
	Exp(H);		//输出
	printf("输入要查找客房名称:");
	scanf("%s", &n);
	if (Find(H, n))
	{
		printf("该客房的序号是: %d\n",Find(H,n));
	}
	else
	{
		printf("该客房不存在\n");
	}
	printf("\n输入已入住客房的床位数:\n");
	scanf("%d", &beds);
	char p[5]="入住";
	updateH(H, beds,p);
	printf("\n(4)\n");
	Exp(H);
	Add(H);
	printf("(5)\n");
	Exp(H);
	q = FirstH(H);
	printf("(6)\n");
	printf("\n入住价格最高的客房信息:\n");
	printf("------------------------------------------------\n");
	printf("客房名称    标准价格    入住价格  床位数    状态\n");
	printf("%s%12.1f%12.1f%8d%11s\n", q->roomN, q->Price, q->PriceL, q->Beds, q->State);
	printf("------------------------------------------------\n");
	MoveK1(H, 2);
	printf("(7)\n");
	Exp(H);
	ReverseN2(H);
	printf("(8)\n");
	Exp(H);
	SortPriceL(H);
	printf("(9)\n");
	Exp(H);
	upBed(H, 3);
	printf("\n(10)\n");
	Exp(H);
}