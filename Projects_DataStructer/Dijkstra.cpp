/***************************************
* About:    有向图的Dijkstra算法实现
***************************************/

#include <stdio.h>

#define maxnum 100
#define maxint 999999


void Dijkstra(int n, int v, int *dist, int *prev, int c[maxnum][maxnum])
{
	bool s[maxnum];    // 判断是否已存入该点到S集合中
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // 初始都未用过该点
		if (dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;

	// 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
	// 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
	for (int i = 2; i <= n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// 找出当前未使用的点j的dist[j]最小值
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j]<tmp)
		{
			u = j;              // u保存当前邻接点中距离最小的点的号码
			tmp = dist[j];
		}
		s[u] = 1;    // 表示u点已存入S集合中

		// 更新dist
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
	// 各数组都从下标1开始
	int dist[maxnum];     // 表示当前点到源点的最短路径长度
	int prev[maxnum];     // 记录当前点的前一个结点
	int c[maxnum][maxnum];   // 记录图的两点间路径长度
	int n, line;             // 图的结点数和路径数

	// 输入结点数
	scanf("%d",&n);
	// 输入路径数
	scanf("%d", &line);
	int p, q, len;          // 输入p, q两点及其路径长度

	// 初始化c[][]为maxint
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		c[i][j] = maxint;

	for (int i = 1; i <= line; ++i)
	{
		scanf("%d%d%d",&p,&q,&len);
		if (len < c[p][q])       // 有重边
		{
			c[p][q] = len;      // p指向q
			c[q][p] = len;      // q指向p，这样表示无向图
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

	// 最短路径长度
	printf("源点到最后一个顶点的最短路径长度: \n",dist[n]);

	// 路径
	printf("源点到最后一个顶点的路径为:");
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

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */   

typedef struct  
{  
	int vexs[MAXVEX];  
	int arc[MAXVEX][MAXVEX];  
	int numVertexes, numEdges;  
}MGraph;  

typedef int Patharc[MAXVEX];    /* 用于存储最短路径下标的数组 */  
typedef int ShortPathTable[MAXVEX];/* 用于存储到各点最短路径的权值和 */  

/* 构件图 */  
void CreateMGraph(MGraph *G)  
{  
	int i, j;  

	/* printf("请输入边数和顶点数:"); */  
	G->numEdges=16;  
	G->numVertexes=9;  

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */  
	{  
		G->vexs[i]=i;  
	}  

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */  
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

/*  Dijkstra算法，求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */
/*  P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */
void ShortestPath_Dijkstra(MGraph G, int x, Patharc *P, ShortPathTable *D)
{
	int v, w, k, min;
	int final[MAXVEX];/* final[w]=1表示求得顶点v0至vw的最短路径 */
	for (v = 0; v<G.numVertexes; v++)    /* 初始化数据 */
	{
		final[v] = 0;           /* 全部顶点初始化为未知最短路径状态 */
		(*D)[v] = G.arc[x][v];/* 将与v0点有连线的顶点加上权值 */
		(*P)[v] = 0;                /* 初始化路径数组P为0  */
	}

	(*D)[x] = 0;  /* v0至v0路径为0 */
	final[x] = 1;    /* v0至v0不需要求路径 */
	/* 开始主循环，每次求得v0到某个v顶点的最短路径 */
	for (v = 1; v<G.numVertexes; v++)
	{
		min = INFINITY;    /* 当前所知离v0顶点的最近距离 */
		for (w = 0; w<G.numVertexes; w++) /* 寻找离v0最近的顶点 */
		{
			if (!final[w] && (*D)[w]<min)
			{
				k = w;
				min = (*D)[w];    /* w顶点离v0顶点更近 */
			}
		}
		final[k] = 1;    /* 将目前找到的最近的顶点置为1 */
		for (w = 0; w<G.numVertexes; w++) /* 修正当前最短路径及距离 */
		{
			/* 如果经过v顶点的路径比现在这条路径的长度短的话 */
			if (!final[w] && (min + G.arc[k][w]<(*D)[w]))
			{ /*  说明找到了更短的路径，修改D[w]和P[w] */
				(*D)[w] = min + G.arc[k][w];  /* 修改当前路径长度 */
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
	ShortPathTable D; /* 求某点到其余各点的最短路径 */
	v0 = 0;


	CreateMGraph(&G);
	scanf_s("%d", &x);

	ShortestPath_Dijkstra(G, x, &P, &D);

	printf("最短路径倒序如下:\n");
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
	printf("\n源点到各顶点的最短路径长度为:\n");
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
int arcs[10][10];//邻接矩阵
int D[10];//保存最短路径长度
int p[10][10];//路径
int final[10];//若final[i] = 1则说明 顶点vi已在集合S中
int n = 0;//顶点个数
int v0 = 0;//源点
int v,w;
void ShortestPath_DIJ()
{
	for (v = 0; v < n; v++) //循环 初始化
	{
		final[v] = 0; D[v] = arcs[v0][v];
		for (w = 0; w < n; w++) p[v][w] = 0;//设空路径
		if (D[v] < MAX) {p[v][v0] = 1; p[v][v] = 1;}
	}
	D[v0] = 0; final[v0]=0; //初始化 v0顶点属于集合S
	//开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
	for (int i = 1; i < n; i++)
	{
		int min = MAX;
		for (w = 0; w < n; w++)
		{
			//我认为的核心过程--选点
			if (!final[w]) //如果w顶点在V-S中
			{
				//这个过程最终选出的点 应该是选出当前V-S中与S有关联边
				//且权值最小的顶点 书上描述为 当前离V0最近的点
				if (D[w] < min) {v = w; min = D[w];}
			}
		}
		final[v] = 1; //选出该点后加入到合集S中
		for (w = 0; w < n; w++)//更新当前最短路径和距离
		{
			/*在此循环中 v为当前刚选入集合S中的点
			则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新
			比如加进点 3 则若要考察 D[5] 是否要更新 就 判断 d(v0-v3) + d(v3-v5) 的和是否小于D[5]
			*/
			if (!final[w] && (min+arcs[v][w]<D[w]))
			{
				D[w] = min + arcs[v][w];
				// p[w] = p[v];
				p[w][w] = 1; //p[w] = p[v] +　[w]
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
#define INFINITE 10000  //当做无穷大  
//图的定义  
typedef struct   
{  
	int vertexNum;  
	char vertex[MAX_VERTEX_NUM];  
	int arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  
}Graph,*PGraph;  

//辅助数组中的元素定义  
typedef struct  
{  
	int distance;  
	int path[MAX_VERTEX_NUM];  
}ArrayNode;  


//构造有向网  
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

	printf("邻接矩阵：\n");
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

//迪杰斯特拉算法  
void Dijkstra(PGraph g,int from,int to)  
{  
	int i,j,index=-1;  
	int n=1;//记录已经求出的两个点之间的最短距离的个数  
	ArrayNode shortestPath[MAX_VERTEX_NUM];  
	int flag[MAX_VERTEX_NUM]={0};//标记，为1表示到这个顶点的最短距离已求出  

	//1.求from到各个顶点的直接距离，即初始化shortestPath数组  
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
	//2.每次求一个最短路径  
	while(n<g->vertexNum){  
		//选择shortestPath中距离最小的，求出from到这个顶点的最短路径  
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
		//修改到各个顶点的最短路径  
		for(i=0;i<g->vertexNum;i++){  
			if(i==from)  
				continue;  
			if(g->arc[index][i]>0 && g->arc[index][i]+shortestPath[index].distance<shortestPath[i].distance){  
				shortestPath[i].distance=g->arc[index][i]+shortestPath[index].distance;  
				//修改路径  
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
	//输出from到to的最短路径及长度  
	if(shortestPath[to].distance==INFINITE){  
		printf("%c到%c没有路径\n",from,to);  
		return;  
	}  
	printf("%d到%d的最短路径长度是：%d\n",from,to,shortestPath[to].distance);  
	printf("经过的顶点：  ");  
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
	printf("请输入起点:");
	scanf_s("%d",&i);
	printf("请输入终点:");
	scanf_s("%d", &j);
	printf("\n迪杰斯特拉算法:\n");  
	Dijkstra(&graph,i,j);  
} 



/***************************************
*  图的最短路径
*     迪杰斯特拉Dijkstra算法实现
***************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 30       //结点个数的最大值，即邻接矩阵最大为 30 x 30
#define MAXINT 999999   //表示两个结点间距离为无穷远

// 各数组下标 以及 结点号 都从1开始

void Dijkstra(int n, int v, int *dist, int *prev, int (*c)[MAXNUM])
{
	int i, j, u;      // u为结点下标，从v开始
	int min;
	int newdist;      // 新的dist值
	int s[MAXNUM];    // 标记是否已经找到从v结点到该结点的最短距离
	for (i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // 0标记未找到最短距离
		if (dist[i] == MAXINT)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;        // v结点自身不需要比较，标记为1

	// 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
	// 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
	for (i = 2; i <= n; ++i)
	{
		min = MAXINT;
		u = v;
		// 找出当前未使用的点j的dist[j]最小值
		for (j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j]<min)
		{
			u = j;              // u保存当前邻接点中距离最小的点的号码
			min = dist[j];
		}
		s[u] = 1;              // 表示u点已存入s集合中

		// 更新dist
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
	int path[MAXNUM];   // path存放逆序的最短路径
	int count = 1;      // 计数器
	path[count++] = u;  // 下标为1的存放最后一个结点u
	int tmp = prev[u];  // 取最后一个结点的前驱结点
	while (tmp != v)    // 构造数组path，直到找到该结点的前驱为v，即源结点
	{
		path[count++] = tmp;
		tmp = prev[tmp];
	}
	path[count] = v;   // 最后把源结点存入数组que中
	for (int i = count; i >= 1; --i)// 逆序输出最短路径
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
	int dist[MAXNUM];        // 表示当前点到源点的最短路径长度
	int prev[MAXNUM];        // 记录当前点的前一个结点
	int c[MAXNUM][MAXNUM];   // 邻接矩阵记录图的两点间路径长度
	int n, line;             // 图的结点数和路径数
	int p, q, len;           // 输入p, q两点及其路径长度
	int v, u;                // 求从v结点到u结点的最短路径
	int i, j;

	printf("请输入结点个数：");
	scanf_s("%d", &n);
	printf("请输入路径条数：");
	scanf_s("%d", &line);

	// 初始化邻接矩阵 c和dist 为 MAXINT
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
	printf("\n请输入两个结点以及结点间距离：\n");
	for (i = 1; i <= line; ++i)
	{
		printf("第%d条路： ", i);
		scanf_s("%d%d%d", &p, &q, &len);
		if (len < c[p][q])      // 有重边
		{
			c[p][q] = len;      // p指向q
			//c[q][p] = len;      // q指向p，这样表示无向图
		}
	}

	printf("\n邻接矩阵：\n");
	for (i = 1; i <= n; ++i)
	{
		for (j = 1; j <= n; ++j)
		{
			printf("%8d", c[i][j]);
		}
		printf("\n\n");
	}

	printf("\n求结点v到n的最短路径\n");
	printf("请输入起始结点v：");
	scanf_s("%d", &v);
	printf("请输入终止结点u：");
	scanf_s("%d", &u);
	Dijkstra(n, v, dist, prev, c);
	printf("\n第%d个结点到第%d个结点的最短路径长度: %d\n", v,u,dist[u]);

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
	printf("第%d个结点到第%d个结点的最短路径表示: ", v, u);
	SearchPath(prev, v, u);

	return 0;
}

#endif