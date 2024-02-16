#include<iostream>
using namespace std;

typedef int VertexType;
#define MaxVexNum 30
#define INFINITY 65535
typedef struct{
    VertexType ves[MaxVexNum+1];//顶点表
    int arc[MaxVexNum+1][MaxVexNum+1];//邻接矩阵
    int VertexNum,EdgeNum;//分别是图中当前顶点数和边数
}MGraph;
int visited[MaxVexNum+1]={0};//记录每个顶点是否被访问过，0为未访问，1为已访问

typedef struct QueueList{
    int vertex;//存顶点序号
    struct QueueList* next;
}Queue;

void CreateMGraph(MGraph &);//创建无向图的邻接矩阵结构
void DFS(MGraph &,int);//深度优先算法(邻接矩阵)
void DFSTraverse(MGraph &,int);//深度优先遍历操作(邻接矩阵)
void BFSTraverse(MGraph &,int);//广度优先遍历操作(邻接矩阵)
void EnQueue(Queue** Q,int n);//把序号为n的顶点入队
int DeQueue(Queue** Q);//将队首顶点出队，返回其序号
int QueueEmpty(Queue *Q);//判断队列是否为空

int main(){
    MGraph G;
    int a,i;
    CreateMGraph(G);
    cout<<"请输入遍历起始的起始顶点"<<endl;
    cin>>a;
	cout<<"图的深度优先搜索遍历结果是:";
    DFSTraverse(G,a);
    cout<<endl;
    for(i=0;i<=G.VertexNum;i++)
        visited[i]=0;
    cout<<"图的广度优先搜索遍历结果是:";
    BFSTraverse(G,a);
    return 0;
}

void CreateMGraph(MGraph &G){//创建无向图的邻接矩阵结构
    int i=0,j=0,k=0;
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
    cout<<"每次输入两个顶点序号以表示其间有边相连"<<endl;
    for(k=1;k<=G.EdgeNum;k++){
        cin>>i>>j;
        G.arc[j][i]=G.arc[i][j]=1;   
    }
}

void DFS(MGraph &G,int a){//深度优先算法(邻接矩阵)
    int i=0;
    visited[a]=1;
    cout<<G.ves[a];
    for(i=1;i<=G.VertexNum;i++)
        if(G.arc[a][i]==1&&!visited[i])
            DFS(G,i);
}

void DFSTraverse(MGraph &G,int a){//深度优先遍历操作(邻接矩阵)
    int i=0;
    for(i=1;i<=G.VertexNum;i++)
	    visited[i]=0;
    DFS(G,a);
}

void EnQueue(Queue** Q,int n){//把序号为n的顶点入队
    Queue *p=(Queue*)malloc(sizeof(Queue));
    if(!p)
        printf("申请空间失败");
    p->vertex=n;
    if(!*Q){
        *Q=p;
        (*Q)->next=NULL;
    }
    else{
        Queue* q=*Q;
        while(q->next)
            q=q->next;
        q->next=p;
        p->next=NULL;
    }
}

int DeQueue(Queue** Q){//将队首顶点出队，返回其序号
    if(!*Q)
        return -1;
    int i;
    Queue *p=*Q;
    i=p->vertex;
    *Q=(*Q)->next;
    free(p);
    return i;
}

int QueueEmpty(Queue *Q){//判断队列是否为空
	if(!Q)
		return 1;
	return 0;
}

void BFSTraverse(MGraph &G,int a){//广度优先遍历操作(邻接矩阵)
	int i=0,j=0,ver=0;
	for(i=1;i<=G.VertexNum;i++)
		visited[i]=0;
    Queue* Q=NULL;
	visited[a]=1;
	cout<<G.ves[a];
	EnQueue(&Q,a);
	while(!QueueEmpty(Q)){
		i=DeQueue(&Q);
		for(j=1;j<=G.VertexNum;j++){
			if(G.arc[i][j]==1&&!visited[j]){
				visited[j]=1;
				cout<<G.ves[j];
				EnQueue(&Q,j);
			}
		}
	}	
}