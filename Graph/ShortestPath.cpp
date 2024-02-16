#include<iostream>
using namespace std;

typedef long long int VertexType;
#define MaxVexNum 300
#define MaxEdgeNum 1000
#define INFINITY 65535

typedef struct{
    VertexType ves[MaxVexNum+1];//顶点表
    int arc[MaxVexNum+1][MaxVexNum+1];//邻接矩阵
    int VertexNum,EdgeNum;//分别是图中当前顶点数和边数
}MGraph;

int Patharc[MaxVexNum];//Patharc[v]的值为最短路径下前驱顶点的坐标
int ShortestPath[MaxEdgeNum];//储存起点到各点最短路径的权值和

void CreateMGraph(MGraph &);//创建无向图的邻接矩阵结构
void Dijkstra(MGraph, int start,int end);//Dijkstra算法求最短路径

int main(){
    int start,end;
    MGraph G;
    CreateMGraph(G);
    cout<<"请输入起点和终点序号";
    cin>>start>>end;
    Dijkstra(G,start,end);
    return 0;
}

void CreateMGraph(MGraph &G){//创建无向图的邻接矩阵结构
	int i=0,j=0,k=0,w=0;
    cout<<"请依次输入顶点数(<300)和边数(<1000)"<<endl;
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
    for(k=1;k<=G.EdgeNum;k++){
        cin>>i>>j>>w;
        G.arc[j][i]=G.arc[i][j]=w;    
    }
}

void Dijkstra(MGraph G, int start,int end){//Dijkstra算法求求start到end最短路径
    int i,j,k,min;
    int Final[MaxVexNum];//Final[v]为1表示已经求得从start到v的最短路径
    for(i=1;i<=G.VertexNum;i++){//初始化
        Final[i]=0;
        ShortestPath[i]=G.arc[start][i];
        Patharc[i]=-1;
    }
    ShortestPath[start]=0;//start到start的最短路径为0
    Final[start]=1;//start到start的最短路径已经求得
    for(i=1;i<G.VertexNum;i++){//每次循环求得从start到某个顶点v的最短路径
        min=INFINITY;
        for(j=1;j<=G.VertexNum;j++){//找到当前未求得最短路径的顶点中距离start最近的顶点
            if(!Final[j]&&ShortestPath[j]<min){
                k=j;
                min=ShortestPath[j];
            }
        }
        Final[k]=1;
        for(j=1;j<=G.VertexNum;j++){//修正当前最短路径及距离
            if(!Final[j]&&min+G.arc[k][j]<ShortestPath[j]){
                ShortestPath[j]=min+G.arc[k][j];
                Patharc[j]=k;
            }
        }
    }
    cout<<"从"<<start<<"到"<<end<<"的最短路径是"<<ShortestPath[end];
}