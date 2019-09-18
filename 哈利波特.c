#include <stdio.h>
#include <stdlib.h>
typedef struct GNode *MGraph;
typedef struct ENode *MEdge;
struct GNode 
{
	int Nv;
	int Ne;
	int X[100][100];
};

struct ENode
{
	int V1;
	int V2;
	int Weight;
};

MGraph Creat(int N)     //���������N 
{
	int i,j;
	MGraph Graph=(MGraph)malloc(sizeof(struct GNode)); 
	Graph->Ne=0;
	Graph->Nv=N;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			Graph->X[i][j]=10000;			//���������ֵ ��ʾ���֮��δ���� 
		}
	return Graph;
}

void InsertE(MGraph Graph, MEdge E)
{
	Graph->X[E->V1][E->V2]=E->Weight;
	Graph->X[E->V2][E->V1]=E->Weight;
}

MGraph BuildGraph()			//E��ʾ�߸���   Edge��ʾָ��ָ�� 
{
	int V,E,i;
	scanf("%d %d",&V,&E);
	MGraph Graph=Creat(V);
	Graph->Ne=E;
	if(E!=0)
	{
		MEdge Edge=(MEdge)malloc(sizeof(struct ENode));
		for(i=0;i<E;i++)
		{
			scanf("%d %d %d",&Edge->V1,&Edge->V2,&Edge->Weight);
			Edge->V1--;
			Edge->V2--;					
			InsertE(Graph,Edge);
			//printf("i=%d %d\n",i,Graph->X[Edge->V1][Edge->V2]);
		}
	}
	return Graph;
}

void Print(MGraph Graph)		
{
	int i,j;
	for(i=0;i<Graph->Nv;i++)
	{
		for(j=0;j<Graph->Nv;j++)
			printf("%d		",Graph->X[i][j]);
		printf("\n");	
	}
	printf("\n");
}

void Floyd(MGraph Graph)
{
	int k,i,j,Max,Min,Animal;
	Min=10000;
	int flag=0; 
	int D[100][100]={0};  //��������Distance����Ŀ��: 1.Ϊ�˱���ͼ�Ĳ���  2.���¼�¼�㵽��ľ��� 
	for(i=0;i<Graph->Nv;i++)
			for(j=0;j<Graph->Nv;j++)
				D[i][j]=Graph->X[i][j];

	for(k=0;k<Graph->Nv;k++)
		for(i=0;i<Graph->Nv;i++)
			for(j=0;j<Graph->Nv;j++)
				if(i!=j    &&   D[i][j] > D[i][k] + D[k][j] )
				{
					D[i][j] = D[i][k] + D[k][j];//������ת��kʹ�þ�����   ����! 
				}
	
	/*
	for(i=0;i<Graph->Nv;i++)
	{
		for(j=0;j<Graph->Nv;j++)
			printf("%d		",D[i][j]);		
		printf("\n");
	}
	*/
	



	for(i=0;i<Graph->Nv;i++)
	{
		Max=0;
		for(j=0;j<Graph->Nv;j++)
		{
			if(i!=j  &&  D[i][j] > Max)
				Max=D[i][j]; 
		}
		if(Max==10000)	
		{
			flag=1;//������ֵ10000˵����ͼ��δ��ͨ��. 
		}
		if(Max<Min)
		{
			Min=Max;
			Animal=i+1;
		}
			
	}
	if(flag==0) 
		printf("%d %d",Animal,Min);
	else
		printf("0");
}







int  main()
{
	MGraph Graph= BuildGraph();
	//Print(Graph);
	Floyd(Graph);
	return 0;
} 




