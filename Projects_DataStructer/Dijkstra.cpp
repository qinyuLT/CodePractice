/***************************************
* About:    ����ͼ��Dijkstra�㷨ʵ��
***************************************/

#include <stdio.h>

#define maxnum 100
#define maxint 999999


void Dijkstra(int n, int v, int *dist, int *prev, int c[maxnum][maxnum])
{
	bool s[maxnum];    // �ж��Ƿ��Ѵ���õ㵽S������
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // ��ʼ��δ�ù��õ�
		if (dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;

	// ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬������S��
	// һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
	for (int i = 2; i <= n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j]<tmp)
		{
			u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
			tmp = dist[j];
		}
		s[u] = 1;    // ��ʾu���Ѵ���S������

		// ����dist
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && c[u][j]<maxint)
		{
			int newdist = dist[u] + c[u][j];
			if (newdist < dist[j])
			{
				dist[j] = newdist;
				prev[j] = u;
			}
		}
	}
}

void searchPath(int *prev, int v, int u)
{
	int que[maxnum];
	int tot = 1;
	que[tot] = u;
	tot++;
	int tmp = prev[u];
	while (tmp != v)
	{
		que[tot] = tmp;
		tot++;
		tmp = prev[tmp];
	}
	que[tot] = v;
	for (int i = tot; i >= 1; --i)
	if (i != 1)
		printf("%d - > ",que[i]);
	else
		printf("%d \n", que[i]);
}

int main()
{
	// �����鶼���±�1��ʼ
	int dist[maxnum];     // ��ʾ��ǰ�㵽Դ������·������
	int prev[maxnum];     // ��¼��ǰ���ǰһ�����
	int c[maxnum][maxnum];   // ��¼ͼ�������·������
	int n, line;             // ͼ�Ľ������·����

	// ��������
	scanf("%d",&n);
	// ����·����
	scanf("%d", &line);
	int p, q, len;          // ����p, q���㼰��·������

	// ��ʼ��c[][]Ϊmaxint
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		c[i][j] = maxint;

	for (int i = 1; i <= line; ++i)
	{
		scanf("%d%d%d",&p,&q,&len);
		if (len < c[p][q])       // ���ر�
		{
			c[p][q] = len;      // pָ��q
			c[q][p] = len;      // qָ��p��������ʾ����ͼ
		}
	}

	for (int i = 1; i <= n; ++i)
		dist[i] = maxint;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			printf("%8d", c[i][j]);
		printf("\n");
	}

	Dijkstra(n, 1, dist, prev, c);

	// ���·������
	printf("Դ�㵽���һ����������·������: \n",dist[n]);

	// ·��
	printf("Դ�㵽���һ�������·��Ϊ:");
	searchPath(prev, 1, n);
}

#if 0

#include "stdio.h"      
#include "stdlib.h"     
#include "io.h"    
#include "math.h"    
#include "time.h"  

#define OK 1  
#define ERROR 0  
#define TRUE 1  
#define FALSE 0  

#define MAXEDGE 20  
#define MAXVEX 20  
#define INFINITY 65535  

typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */   

typedef struct  
{  
	int vexs[MAXVEX];  
	int arc[MAXVEX][MAXVEX];  
	int numVertexes, numEdges;  
}MGraph;  

typedef int Patharc[MAXVEX];    /* ���ڴ洢���·���±������ */  
typedef int ShortPathTable[MAXVEX];/* ���ڴ洢���������·����Ȩֵ�� */  

/* ����ͼ */  
void CreateMGraph(MGraph *G)  
{  
	int i, j;  

	/* printf("����������Ͷ�����:"); */  
	G->numEdges=16;  
	G->numVertexes=9;  

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */  
	{  
		G->vexs[i]=i;  
	}  

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */  
	{  
		for ( j = 0; j < G->numVertexes; j++)  
		{  
			if (i==j)  
				G->arc[i][j]=0;  
			else  
				G->arc[i][j] = INFINITY;  
			    G->arc[j][i] = INFINITY;
		}  
	}  

	G->arc[0][1]=1;  
	G->arc[0][2]=5;   
	G->arc[1][2]=3;   
	G->arc[1][3]=7;   
	G->arc[1][4]=5;   

	G->arc[2][4]=1;   
	G->arc[2][5]=7;   
	G->arc[3][4]=2;   
	G->arc[3][6]=3;   
	G->arc[4][5]=3;  

	G->arc[4][6]=6;  
	G->arc[4][7]=9;   
	G->arc[5][7]=5;   
	G->arc[6][7]=2;   
	G->arc[6][8]=7;  

	G->arc[7][8]=4;  

	/*
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}*/

}

/*  Dijkstra�㷨����������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v] */
/*  P[v]��ֵΪǰ�������±�,D[v]��ʾv0��v�����·�����Ⱥ� */
void ShortestPath_Dijkstra(MGraph G, int x, Patharc *P, ShortPathTable *D)
{
	int v, w, k, min;
	int final[MAXVEX];/* final[w]=1��ʾ��ö���v0��vw�����·�� */
	for (v = 0; v<G.numVertexes; v++)    /* ��ʼ������ */
	{
		final[v] = 0;           /* ȫ�������ʼ��Ϊδ֪���·��״̬ */
		(*D)[v] = G.arc[x][v];/* ����v0�������ߵĶ������Ȩֵ */
		(*P)[v] = 0;                /* ��ʼ��·������PΪ0  */
	}

	(*D)[x] = 0;  /* v0��v0·��Ϊ0 */
	final[x] = 1;    /* v0��v0����Ҫ��·�� */
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·�� */
	for (v = 1; v<G.numVertexes; v++)
	{
		min = INFINITY;    /* ��ǰ��֪��v0������������ */
		for (w = 0; w<G.numVertexes; w++) /* Ѱ����v0����Ķ��� */
		{
			if (!final[w] && (*D)[w]<min)
			{
				k = w;
				min = (*D)[w];    /* w������v0������� */
			}
		}
		final[k] = 1;    /* ��Ŀǰ�ҵ�������Ķ�����Ϊ1 */
		for (w = 0; w<G.numVertexes; w++) /* ������ǰ���·�������� */
		{
			/* �������v�����·������������·���ĳ��ȶ̵Ļ� */
			if (!final[w] && (min + G.arc[k][w]<(*D)[w]))
			{ /*  ˵���ҵ��˸��̵�·�����޸�D[w]��P[w] */
				(*D)[w] = min + G.arc[k][w];  /* �޸ĵ�ǰ·������ */
				(*P)[w] = k;
			}
		}
	}
}

int main(void)
{
	int i, j, v0;
	int x;
	MGraph G;
	Patharc P;
	ShortPathTable D; /* ��ĳ�㵽�����������·�� */
	v0 = 0;


	CreateMGraph(&G);
	scanf_s("%d", &x);

	ShortestPath_Dijkstra(G, x, &P, &D);

	printf("���·����������:\n");
	for (i = 1; i<G.numVertexes; ++i)
	{
		printf("v%d - v%d : ", x, i);
		j = i;
		while (P[j] != 0)
		{
			printf("%d ", P[j]);
			j = P[j];
		}
		printf("\n");
	}
	printf("\nԴ�㵽����������·������Ϊ:\n");
	for (i = 1; i<G.numVertexes; ++i)
		printf("v%d - v%d : %d \n", G.vexs[x], G.vexs[i], D[i]);
	system("pause");
	return 0;
}

#endif

#if 0

#include <iostream>
#include <cstdio>
#define MAX 1000000
using namespace std;
int arcs[10][10];//�ڽӾ���
int D[10];//�������·������
int p[10][10];//·��
int final[10];//��final[i] = 1��˵�� ����vi���ڼ���S��
int n = 0;//�������
int v0 = 0;//Դ��
int v,w;
void ShortestPath_DIJ()
{
	for (v = 0; v < n; v++) //ѭ�� ��ʼ��
	{
		final[v] = 0; D[v] = arcs[v0][v];
		for (w = 0; w < n; w++) p[v][w] = 0;//���·��
		if (D[v] < MAX) {p[v][v0] = 1; p[v][v] = 1;}
	}
	D[v0] = 0; final[v0]=0; //��ʼ�� v0�������ڼ���S
	//��ʼ��ѭ�� ÿ�����v0��ĳ������v�����·�� ����v������S��
	for (int i = 1; i < n; i++)
	{
		int min = MAX;
		for (w = 0; w < n; w++)
		{
			//����Ϊ�ĺ��Ĺ���--ѡ��
			if (!final[w]) //���w������V-S��
			{
				//�����������ѡ���ĵ� Ӧ����ѡ����ǰV-S����S�й�����
				//��Ȩֵ��С�Ķ��� ��������Ϊ ��ǰ��V0����ĵ�
				if (D[w] < min) {v = w; min = D[w];}
			}
		}
		final[v] = 1; //ѡ���õ����뵽�ϼ�S��
		for (w = 0; w < n; w++)//���µ�ǰ���·���;���
		{
			/*�ڴ�ѭ���� vΪ��ǰ��ѡ�뼯��S�еĵ�
			���Ե�VΪ�м�� ���� d0v+dvw �Ƿ�С�� D[w] ���С�� �����
			����ӽ��� 3 ����Ҫ���� D[5] �Ƿ�Ҫ���� �� �ж� d(v0-v3) + d(v3-v5) �ĺ��Ƿ�С��D[5]
			*/
			if (!final[w] && (min+arcs[v][w]<D[w]))
			{
				D[w] = min + arcs[v][w];
				// p[w] = p[v];
				p[w][w] = 1; //p[w] = p[v] +��[w]
			}
		}
	}
}


int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arcs[i][j];
		}
	}
	ShortestPath_DIJ();
	for (int i = 0; i < n; i++) printf("D[%d] = %d\n",i,D[i]);
	return 0;
}

#endif

#if 0

#include<stdio.h>  

#define MAX_VERTEX_NUM 20  
#define INFINITE 10000  //���������  
//ͼ�Ķ���  
typedef struct   
{  
	int vertexNum;  
	char vertex[MAX_VERTEX_NUM];  
	int arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  
}Graph,*PGraph;  

//���������е�Ԫ�ض���  
typedef struct  
{  
	int distance;  
	int path[MAX_VERTEX_NUM];  
}ArrayNode;  


//����������  
void createdGraph(PGraph g)  
{  
	int i,j;  
	g->vertexNum=6;  
	for(i=0;i<g->vertexNum;i++)  
		g->vertex[i]=i;  
	for(i=0;i<g->vertexNum;i++)  
	for(j=0;j<g->vertexNum;j++)  
		g->arc[i][j] = INFINITE;
	g->arc[0][2]=10;  
	g->arc[0][4]=30;  
	g->arc[0][5]=100;  
	g->arc[1][2]=5;  
	g->arc[2][3]=50;  
	g->arc[3][5]=10;  
	g->arc[4][3]=20;  
	g->arc[4][5]=60;  

	printf("�ڽӾ���\n");
	for (i = 0; i < g->vertexNum; ++i)
	{
		for (j = 0; j < g->vertexNum; ++j)
		{
			printf("%8d", g->arc[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}  

//�Ͻ�˹�����㷨  
void Dijkstra(PGraph g,int from,int to)  
{  
	int i,j,index=-1;  
	int n=1;//��¼�Ѿ������������֮�����̾���ĸ���  
	ArrayNode shortestPath[MAX_VERTEX_NUM];  
	int flag[MAX_VERTEX_NUM]={0};//��ǣ�Ϊ1��ʾ������������̾��������  

	//1.��from�����������ֱ�Ӿ��룬����ʼ��shortestPath����  
	for(i=0;i<g->vertexNum;i++){  
		if(from==i){  
			shortestPath[i].distance=0;  
			shortestPath[i].path[0]=i;  
			flag[from]=1;  
		}  
		else if(g->arc[from][i]>0){  
			shortestPath[i].path[0]=from;  
			shortestPath[i].path[1]=i;  
			shortestPath[i].distance=g->arc[from][i];  
		}else  
			shortestPath[i].distance=INFINITE;  
	}  
	//2.ÿ����һ�����·��  
	while(n<g->vertexNum){  
		//ѡ��shortestPath�о�����С�ģ����from�������������·��  
		index=-1;  
		for(i=0;i<g->vertexNum;i++){  
			if(i==from)  
				continue;  
			if(flag[i]==0 && index==-1 && shortestPath[i].distance!=INFINITE)  
				index=i;  
			if(flag[i]==0 && index!=-1 && shortestPath[i].distance<shortestPath[index].distance)  
				index=i;  
		}  
		flag[index]=1;  
		//�޸ĵ�������������·��  
		for(i=0;i<g->vertexNum;i++){  
			if(i==from)  
				continue;  
			if(g->arc[index][i]>0 && g->arc[index][i]+shortestPath[index].distance<shortestPath[i].distance){  
				shortestPath[i].distance=g->arc[index][i]+shortestPath[index].distance;  
				//�޸�·��  
				j=0;  
				while(1){  
					shortestPath[i].path[j]=shortestPath[index].path[j];  
					if(shortestPath[index].path[j]==index)  
						break;  
					j++;  
				}  
				shortestPath[i].path[j+1]=i;  
			}  
		}  
		n++;  
	}  
	//���from��to�����·��������  
	if(shortestPath[to].distance==INFINITE){  
		printf("%c��%cû��·��\n",from,to);  
		return;  
	}  
	printf("%d��%d�����·�������ǣ�%d\n",from,to,shortestPath[to].distance);  
	printf("�����Ķ��㣺  ");  
	i=0;  
	while(1){  
		printf("%-3d",shortestPath[to].path[i]);  
		if(shortestPath[to].path[i]==to)  
			break;  
		i++;  
	}  
	printf("\n");  
}  

void main()  
{  
	Graph graph;  
	int i, j;
	createdGraph(&graph);  
	printf("���������:");
	scanf_s("%d",&i);
	printf("�������յ�:");
	scanf_s("%d", &j);
	printf("\n�Ͻ�˹�����㷨:\n");  
	Dijkstra(&graph,i,j);  
} 



/***************************************
*  ͼ�����·��
*     �Ͻ�˹����Dijkstra�㷨ʵ��
***************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 30       //�����������ֵ�����ڽӾ������Ϊ 30 x 30
#define MAXINT 999999   //��ʾ�����������Ϊ����Զ

// �������±� �Լ� ���� ����1��ʼ

void Dijkstra(int n, int v, int *dist, int *prev, int (*c)[MAXNUM])
{
	int i, j, u;      // uΪ����±꣬��v��ʼ
	int min;
	int newdist;      // �µ�distֵ
	int s[MAXNUM];    // ����Ƿ��Ѿ��ҵ���v��㵽�ý�����̾���
	for (i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // 0���δ�ҵ���̾���
		if (dist[i] == MAXINT)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;        // v���������Ҫ�Ƚϣ����Ϊ1

	// ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬������S��
	// һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
	for (i = 2; i <= n; ++i)
	{
		min = MAXINT;
		u = v;
		// �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for (j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j]<min)
		{
			u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
			min = dist[j];
		}
		s[u] = 1;              // ��ʾu���Ѵ���s������

		// ����dist
		for (j = 1; j <= n; ++j)
		if ((!s[j]) && c[u][j]<MAXINT)
		{
			newdist = dist[u] + c[u][j];
			if (newdist < dist[j])
			{
				dist[j] = newdist;
				prev[j] = u;
			}
		}
	}
}

void SearchPath(int *prev, int v, int u)
{
	int path[MAXNUM];   // path�����������·��
	int count = 1;      // ������
	path[count++] = u;  // �±�Ϊ1�Ĵ�����һ�����u
	int tmp = prev[u];  // ȡ���һ������ǰ�����
	while (tmp != v)    // ��������path��ֱ���ҵ��ý���ǰ��Ϊv����Դ���
	{
		path[count++] = tmp;
		tmp = prev[tmp];
	}
	path[count] = v;   // ����Դ����������que��
	for (int i = count; i >= 1; --i)// ����������·��
	{
		if (i != 1)
		{
			printf("%d -> ", path[i]);
		}
		else
		{
			printf("%d\n", path[i]);
		}
	}
}

int main1()
{
	int dist[MAXNUM];        // ��ʾ��ǰ�㵽Դ������·������
	int prev[MAXNUM];        // ��¼��ǰ���ǰһ�����
	int c[MAXNUM][MAXNUM];   // �ڽӾ����¼ͼ�������·������
	int n, line;             // ͼ�Ľ������·����
	int p, q, len;           // ����p, q���㼰��·������
	int v, u;                // ���v��㵽u�������·��
	int i, j;

	printf("�������������");
	scanf_s("%d", &n);
	printf("������·��������");
	scanf_s("%d", &line);

	// ��ʼ���ڽӾ��� c��dist Ϊ MAXINT
	for (i = 1; i <= n; ++i)
	{
		for (j = 1; j <= n; ++j)
		{
			c[i][j] = MAXINT;
			
		}
		dist[i] = MAXINT;
	}

/*	c[1][2] = 10;  c[2][3] = 50;
	c[1][4] = 30;  c[3][5] = 10;
	c[1][5] = 100; c[4][3] = 20; c[4][5] = 60;

	
	c[1][2] = 1; c[1][3] = 5; c[2][3] = 3; c[2][4] = 7; 
	c[2][5] = 5; c[3][5] = 1; c[3][6] = 7; c[4][5] = 2; 
	c[4][7] = 3; c[5][6] = 3; c[5][7] = 6; c[5][8] = 9; 
	c[6][8] = 5; c[7][8] = 2; c[7][9] = 7; c[8][9] = 4;
	c[2][1] = 1; c[3][1] = 5; c[3][2] = 3; c[4][2] = 7;
	c[5][2] = 5; c[5][3] = 1; c[6][3] = 7; c[5][4] = 2;
	c[7][4] = 3; c[6][5] = 3; c[7][5] = 6; c[8][5] = 9;
	c[8][6] = 5; c[8][7] = 2; c[9][7] = 7; c[9][8] = 4;
*/
	printf("\n��������������Լ�������룺\n");
	for (i = 1; i <= line; ++i)
	{
		printf("��%d��·�� ", i);
		scanf_s("%d%d%d", &p, &q, &len);
		if (len < c[p][q])      // ���ر�
		{
			c[p][q] = len;      // pָ��q
			//c[q][p] = len;      // qָ��p��������ʾ����ͼ
		}
	}

	printf("\n�ڽӾ���\n");
	for (i = 1; i <= n; ++i)
	{
		for (j = 1; j <= n; ++j)
		{
			printf("%8d", c[i][j]);
		}
		printf("\n\n");
	}

	printf("\n����v��n�����·��\n");
	printf("��������ʼ���v��");
	scanf_s("%d", &v);
	printf("��������ֹ���u��");
	scanf_s("%d", &u);
	Dijkstra(n, v, dist, prev, c);
	printf("\n��%d����㵽��%d���������·������: %d\n", v,u,dist[u]);

/*	for (i = 1; i <= n; ++i)
	{
		printf("%d ", dist[i]);
	}
	printf("\n");
	for (i = 1; i <= n; ++i)
	{
		printf("%d ", prev[i]);
	}
*/
	printf("��%d����㵽��%d���������·����ʾ: ", v, u);
	SearchPath(prev, v, u);

	return 0;
}

#endif