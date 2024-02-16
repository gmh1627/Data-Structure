#include<iostream>
using namespace std;

#define MaxVexNum 30
#define INFINITY 65535

typedef int VertexType;
typedef struct{
    VertexType ves[MaxVexNum+1];//顶点表
    int arc[MaxVexNum+1][MaxVexNum+1];//邻接矩阵
    int VertexNum,EdgeNum;//分别是图中当前顶点数和边数
}MGraph;

void CreateMGraph(MGraph &);//创建无向图的邻接矩阵结构
void Prim(MGraph);//Prim算法求最小生成树的各边的长度之和

int main(){
    MGraph G;
    CreateMGraph(G);
    Prim(G);
    return 0;
}

void CreateMGraph(MGraph &G){//创建无向图的邻接矩阵结构
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
    for(k=1;k<=G.EdgeNum;k++){
        cin>>i>>j>>w;
        G.arc[j][i]=G.arc[i][j]=w;   
    }
}

void Prim(MGraph G){//Prim算法求最小生成树的各边的长度之和
	int min=0,length=0,i=0,j=0,k=0;
	int adjvex[MaxVexNum+1]={0};//记录已加入生成树的顶点序号，adjvex[i]的值是生成树上i顶点上一个连接的顶点序号
	int lowcost[MaxVexNum+1]={0};//记录已遍历顶点的邻边中最小的权重
	lowcost[1]=0;
	adjvex[1]=1;
	for(i=2;i<=G.VertexNum;i++){
		lowcost[i]=G.arc[1][i];
		adjvex[i]=1;
	}
	for(i=1;i<G.VertexNum;i++){
		min=INFINITY;
		j=2;
		k=1;
		while(j<=G.VertexNum){
			if(lowcost[j]&&lowcost[j]<min){
				min=lowcost[j];
				k=j;
			}
			j++;
		}
		length+=G.arc[k][adjvex[k]];
		lowcost[k]=0;//此顶点已完成任务
		for(j=2;j<=G.VertexNum;j++){
			if(lowcost[j]&&G.arc[k][j]<lowcost[j]){
				lowcost[j]=G.arc[k][j];
				adjvex[j]=k;
			}
		}
	}
	cout<<"最小生成树的各边的长度之和为"<<length;
}