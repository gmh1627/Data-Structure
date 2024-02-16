#include<iostream>
using namespace std;
typedef struct QueueList{
    int num; //顾客序号
    struct QueueList* next;
}Queue;

Queue* EnQueue(Queue** Q,int n){//将顾客进队
    Queue *p=(Queue*)malloc(sizeof(Queue));
    if(!p){
        printf("申请空间失败");
        return NULL;
    }
    p->num=n;
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
    return *Q;
}

int DeQueue(Queue** Q){//将队首顾客出队
    if(!*Q)
        return -1;
    int i;
    Queue *p=*Q;
    i=p->num;
    *Q=(*Q)->next;
    free(p);
    return i;
}

int main(){
    int n,i,arrive[50]={0},status[50],Time=0,wait[50]={0},waittotal=0,waitaverage=0,closetime=0,avetime=0,Money=0,money[50]={0},moneytemp=0;
    //n为顾客人数，arrive数组记录每个顾客来到银行的时间，status数组记录每个顾客的状态，-1为未来银行，0为正在等待，1为已离开
    //Time表示当前时间，wait数组记录每个顾客等待的时间，waittotal是所有顾客等待的总时间，waitaverage是顾客等待的平均时间,closetime是银行关门时间,avetime是每笔交易的平均时间
	//Money为银行一开始的款额，money数组记录每个顾客的交易金额，正数为存钱，负数为取钱,moneytemp用来记录第一个队列最后一个客户（第二种业务）接待前银行的剩余款额
	cout<<"请依次输入顾客总人数、银行开始营业时拥有的款额、今天预计的营业时长和客户交易时长"<<endl;
	cin>>n>>Money>>closetime>>avetime;
    Queue* Q=NULL;
    cout<<"请依次输入每个顾客要交易的款额（用负值和正值分别表示第一类和第二类业务）和客户来到银行的时间"<<endl;
    for(i=0;i<n;i++){
        cin>>money[i]>>arrive[i];
        status[i]=-1;
    }
    for(i=0;i<n;i++){
        if (arrive[i]>=closetime-avetime) {//在关门前完成不了交易相当于一直等到关门
            status[i]=0;
            break;
        }
        else {
        	if(Time<arrive[i])
			    Time=arrive[i];//重置当前时间
            if(money[i]<0){//第一种业务：取钱
                if(-money[i]<=Money){//银行有足够余额
                    Money+=money[i];
                    wait[i]=Time-arrive[i];
                    status[i]=1;
                    Time+=avetime;//重置当前时间
                    moneytemp=Money;
                    if(Time>=closetime)
                        loop:break;
                }
                else{//银行没有足够余额，进入第二条队等待
                    status[i]=0;
                    EnQueue(&Q,i);
                }
            }
            else{//第二种业务
                Money+=money[i];
                wait[i]=Time-arrive[i];
                status[i]=1;
                Time+=avetime;//重置当前时间
                int status2[50]={0};//用来标记第二条队的顾客是否被检查到，没检查是0，检查到是1
                while (Money>moneytemp){
                	int k=DeQueue(&Q);
                	if(k==-1) 
						break;
                	else if(!status2[k]){
					if(-money[k]<=Money){
                        Money+=money[k];
                        wait[k]=Time-arrive[k];
                        status[k]=1;
                        Time+=avetime;//重置当前时间
                        moneytemp=Money;
                        if(Time>=closetime)
                            goto loop;//跳出while循环和for循环
					}
					else{
                        status2[i]=1;
                        EnQueue(&Q,i);//不满足就重新入队
                    }
                }
            }
        }
    }
}
    for ( i = 0; i < n; i++){
    	if(!status[i])
           wait[i]=closetime-arrive[i];
    	cout<<"第"<<i+1<<"个顾客的等待时间为"<<wait[i]<<endl;
    }
    for ( i = 0; i < n; i++)
        waittotal+=wait[i];
    waitaverage=waittotal/n;
    cout<<n<<"个顾客的平均等待时间为"<<waitaverage<<endl;
    return 0;
}
