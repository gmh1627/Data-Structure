#include<iostream>
using namespace std;

#define MaxVexNum 30
#define MaxEdgeNum 29
#define INFINITY 65535

typedef int VertexType;
typedef struct{
    VertexType ves[MaxVexNum+1];//顶点表
    int arc[MaxVexNum+1][MaxVexNum+1];//邻接矩阵
    int VertexNum,EdgeNum;//分别是图中当前顶点数和边数
}MGraph;

typedef struct{
	int begin;
	int end;
	int weight;
}Edge;//边集数组结构

Edge edges[MaxEdgeNum+1];

void CreateMGraph(MGraph &);//创建无向图的邻接矩阵结构
void Kruskal(MGraph);//Kruskal算法求最小生成树的各边的长度之和
void SortEdge(Edge *);//将边集数组按权值从小到大排序
int Find(int* parent,int i);//查找连线顶点的尾部下标

int main(){
	MGraph G;
	CreateMGraph(G);
	Kruskal(G);
	return 0;
}

void CreateMGraph(MGraph &G){//创建无向图的邻接矩阵结构和边集数组
    int i=0,j=0,k=0,w;
    cout<<"请依次输入顶点数(<30)和边数(<300)"<<endl;
    cin>>G.VertexNum>>G.EdgeNum;
    for(i=1;i<=G.VertexNum;i++)
        G.ves[i]=i;//顶点序号从1开始
    for(i=1;i<=G.VertexNum;i++)
        for(j=1;j<=G.VertexNum;j++){
            if(i==j)
                G.arc[i][j]=0;
            else
                G.arc[i][j]=INFINITY;
        }
    cout<<"每次输入两个顶点序号以表示其间有边相连,并输入该边的权值"<<endl;
    for(k=1;k<=G.EdgeNum;k++){//输入边的信息
        cin>>i>>j>>w;
        G.arc[j][i]=G.arc[i][j]=w;
		edges[k].begin=i;
		edges[k].end=j;
		edges[k].weight=w;
    }
    for(k=G.EdgeNum+1;k<=MaxEdgeNum;k++)
		edges[k].weight=0;
	for(k=1;k<=G.EdgeNum;k++)
		cout<<edges[k].begin<<" "<<edges[k].end<<" "<<edges[k].weight<<endl;
	cout<<endl;
    SortEdge(edges);//将边集数组按权值从小到大排序
    for(k=1;k<=G.EdgeNum;k++)
		cout<<edges[k].begin<<" "<<edges[k].end<<" "<<edges[k].weight<<endl;
}

void SortEdge(Edge *edges){//将边集数组按权值从小到大排序
	int i,j,temp;
	for(i=1;i<=MaxEdgeNum;i++){
		for(j=1;j<=MaxEdgeNum;j++){
			if(edges[j].weight>edges[j+1].weight&&edges[j+1].weight){
				temp=edges[j].begin;
				edges[j].begin=edges[j+1].begin;
				edges[j+1].begin=temp;
				temp=edges[j].end;
				edges[j].end=edges[j+1].end;
				edges[j+1].end=temp;
				temp=edges[j].weight;
				edges[j].weight=edges[j+1].weight;
				edges[j+1].weight=temp;
			}
		}
	}
}

void Kruskal(MGraph G){//Kruskal算法求最小生成树的各边的长度之和
	int i,n,m,length=0;
	int parent[MaxVexNum+1];//定义一数组用来判断边与边是否形成环路,parent[m]=n表示m与n在同一集合中，而不是表示m和n之间有边
	for(i=0;i<=G.VertexNum;i++)
		parent[i]=0;
	for(i=1;i<=G.EdgeNum;i++){
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		if(n!=m){//如果n与m不等,说明此边没有与现有生成树形成环路
			parent[n]=m;//将此边的结尾顶点放入下标为起点的parent中,表示此顶点已经在生成树集合中
			length+=edges[i].weight;
		}
	}
	cout<<"最小生成树的各边的长度之和为"<<length;
}

int Find(int* parent,int i){//查找连线顶点的尾部下标
	while(parent[i]>0)
		i=parent[i];
	return i;
}