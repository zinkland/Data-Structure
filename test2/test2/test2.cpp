#include "pch.h"
#include<stdio.h>
#include <iostream>
#include<string.h>
using namespace std;

typedef struct
{
	char ch[256];
	int length;
}SString;

int Index_BF(SString S, SString T, int pos)
{
	int i, j,p,n,k=1,l=0,m=0;
	i = pos;
	j = 1;
	int a = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j])
		{
			++i;
			++j;
			++l;
		}
		else
		{
			++m;
			printf("\n第%d次匹配字符数:%d\n", m, l);
			printf("\n");
			l = 0;
			p = j;
			cout << S.ch + 1 << endl;
			n = i - j;
			while (n)
			{
				printf(" ");
				n--;
			}
			while (p>0)
			{
				printf("%c", T.ch[a]);
				a++;
				p--;
			}
			a = 1;
			printf("\n");
			printf("\ni=%d\n", i);
			printf("\nj=%d\n", j);
			i = i - j + 2;
			j = 1;
			k = k + 1;
		}
	}
	printf("\n第%d次匹配字符数:%d\n", m + 1, T.length);
	cout << S.ch + 1 << endl;
	n = i - j;
	while (n)
	{
		printf(" ");
		n--;
	}
	cout << T.ch + 1 << endl;
	printf("\n匹配次数:%d次\n", k);
	if (j > T.length)
	{
		return i - T.length;
	}
	else
	{
		return 0;
	}
}

void Next(SString T, int next[])
{
	int i, j,n;
	i = 1;
	j = 0;
	n = 0;
	next[1] = 0;
	while (i < T.length)
	{
		if (j == 0 || (T.ch[i] == T.ch[j]))
		{
			++i; ++j;
			next[i] = j;
		}
		else
		{
			j = next[j] ;
		}
	}
}

int Index_KMP(SString S, SString T, int pos,int next[])
{
	int i, j,k=1,l=0,m=0;
	int a = 1, b = pos-1 , c;
	i = pos;
	j = 1;
	while (i<=S.length&&j<=T.length)
	{
		
		if (j==0)
		{
			++i;
			++j;
		}
		if (S.ch[i] == T.ch[j])
		{
			++i;
			++j;
			++l;
		}
		else
		{
			c = j;
			++m;
			printf("\n第%d次匹配字符数:%d\n", m, l);
			printf("\n");
			cout << S.ch+1<<endl;
			while (b>0)
			{
					printf(" ");
					b--;
			}
			while (c)
			{
				printf("%c", T.ch[a]);
				a++;
				c--;

			}
			printf("\n");
			if (next[j]==0)
			{
				b = i;
			}
			else 
			{
				b = b+j-next[j]+pos-1;
			}
			a = 1;
			l = 0;
			printf("\ni=%d\n", i);
			printf("\nj=%d\n", j);
			j = next[j];
			k = k + 1;
		}
		
	}
	b = i - j;
	printf("\n第%d次匹配字符数:%d\n", m + 1, T.length);
	cout << S.ch + 1 << endl;
	while (b)
	{
		printf(" ");
		b--;
	}
	cout << T.ch+1<<endl;
	printf("\n匹配次数:%d次\n", k);
	if (j>T.length)
	{
		return i - T.length;
	}
	else
	{
		return 0;
	}
}

void next_val(SString T, int nextval[])
{
	int i, j;
	i = 1;
	j = 0;
	nextval[1] = 0;
	while (i<T.length)
	{
		if (j==0||T.ch[i]==T.ch[j])
		{
			++i;
			++j;
			if (T.ch[i]!=T.ch[j])
			{
				nextval[i] = j;
			}
			else
			{
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
}

void main()
{
	SString M;		//主串
	SString N;		//子串
	int n, m, position,i;
	int next[100];
	int nextval[100];
	while (1)
	{
		printf("\nMenu:\n");
		printf("1．输入主串、子串和匹配起始位置\n");
		printf("2．朴素的模式匹配算法\n");
		printf("3．KMP算法\n");
		printf("4．KMP改进算法\n");
		printf("0．退出管理系统\n");
		printf("\n选择需要执行的操作:");
		scanf("%d", &m);//菜单选择
		switch (m)
		{
		case 1:
			char A[100];
			char B[100];
			printf("输入主串:\n");
			cin >> (A + 1);		//从[1]开始输入字符串
			strcpy(M.ch, A);
			printf("输入子串:\n");
			cin >> (B + 1);
			strcpy(N.ch, B);
			M.length = strlen(M.ch) - 1;
			N.length = strlen(N.ch) - 1;
			printf("输入匹配起始位置:");
			scanf("%d", &n);
			break;
		case 2:
			position = Index_BF(M, N, n);
			if (position==0)
			{
				printf("\n匹配失败\n");
			}
			else
			{
				printf("\n匹配成功序号:%d\n", position);
			}
			break;
		case 3:
			Next(N, next);
			printf("\nnext的值:\n");
			printf("--------------------\n");
			for (i = 1; i < N.length + 1; i++)
			{
				printf(" %c", N.ch[i]);
			}
			printf("\n--------------------\n");
			for (i = 1; i < N.length + 1; i++)
			{
				printf(" %d", next[i]);
			}
			printf("\n--------------------\n");
			position = Index_KMP(M, N, n, next);
			if (position == 0)
			{
				printf("\n匹配失败\n");
			}
			else
			{
				printf("\n匹配成功序号:%d\n", position);
			}
			break;
		case 4:
			next_val(N, nextval);
			printf("\nnextval的值:\n");
			printf("--------------------\n");
			for (i = 1; i < N.length + 1; i++)
			{
				printf(" %c", N.ch[i]);
			}
			printf("\n--------------------\n");
			for (i = 1; i < N.length + 1; i++)
			{
				printf(" %d", nextval[i]);
			}
			printf("\n--------------------\n");
			position = Index_KMP(M, N, n, nextval);
			if (position == 0)
			{
				printf("\n匹配失败\n");
			}
			else
			{
				printf("\n匹配成功序号:%d\n", position);
			}
			break;
		case 0:
			exit(0);
			break;
		}	
	}
}
			//strcpy(M.ch, "Mebababababcaababababcabadaaaac");	
			//strcpy(N.ch, "Nbabababcabad");			
			//N.length = strlen(N.ch) - 1;		
			//M.length = strlen(M.ch) - 1;//测试
			//n = 2;

			//strcpy(M.ch, "Macabaabaabcacaabc");	
			//strcpy(N.ch, "Nabaabcac");			
			//N.length = strlen(N.ch) - 1;		
			//M.length = strlen(M.ch) - 1;//测试
			//n = 1;