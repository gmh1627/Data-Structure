#include<iostream>
using namespace std;

#define MAXNUM 500
typedef struct{
    int Address[MAXNUM];//哈希表地址
    int Keyword[MAXNUM];//哈希表关键字
    int keynum;//关键字个数
    int SuccessFind[MAXNUM]={0};//成功查找次数
    int FailFind[MAXNUM]={0};//失败查找次数
    float AveSuccess=0;//查找成功的平均查找次数
    float AveFail=0;//查找失败时在各个位置上的平均查找次数
}HashTable;

int p=1;//除留余数法中的除数
int Hash(int);//哈希函数(除留余数法)
void InsertHash1(HashTable*,int);//线性探测再散列把关键字插入哈希表
void SearchHash1(HashTable*,int);//在哈希表中查找关键字
void JudgeFail1(HashTable*);//求在每个地址查找失败时的最小散列次数

int main(){
    int i,key[MAXNUM];
    HashTable *hashtable = new HashTable;
    cout<<"请依次输入关键字个数、关键字和除留余数法中的除数"<<endl;
    cin>>hashtable->keynum;
    for(i=0;i<hashtable->keynum;i++)
        cin>>key[i];
    cin>>p;
    for(i=0;i<p;i++){
        hashtable->Address[i]=i;
        hashtable->Keyword[i]=-1;//初始化哈希表中没有关键字的位置为-1
    }
    cout<<"哈希表地址：";
    for(i=0;i<p;i++)
        cout<<hashtable->Address[i]<<"  ";
    cout<<endl;
    for(i=0;i<hashtable->keynum;i++)
        InsertHash1(hashtable,key[i]);
    cout<<"表中关键字：";
    for(i=0;i<p;i++)
        if(hashtable->Keyword[i]!=-1)
            cout<<i<<":"<<hashtable->Keyword[i]<<" ";
    cout<<endl;
    for(i=0;i<hashtable->keynum;i++)
        SearchHash1(hashtable,key[i]);
    cout<<"成功查找次数：";
    for(i=0;i<p;i++){
        cout<<i<<":"<<hashtable->SuccessFind[i]<<" ";
        hashtable->AveSuccess+=hashtable->SuccessFind[i];
    }
    cout<<endl;
    JudgeFail1(hashtable);//求在每个地址查找失败时的最小散列次数
    cout<<"失败查找次数：";
    for(i=0;i<p;i++){
        cout<<i<<":"<<hashtable->FailFind[i]<<" ";
        hashtable->AveFail+=hashtable->FailFind[i];
    }
    cout<<endl;
    cout<<"查找成功的平均查找次数："<<hashtable->AveSuccess/hashtable->keynum<<endl;
    cout<<"查找失败的平均查找次数："<<hashtable->AveFail/p<<endl;
    delete hashtable; 
}

int Hash(int m){//哈希函数(除留余数法)
    return m%p;
}

void InsertHash1(HashTable* H,int key){//用线性探测再散列把关键字插入哈希表
    int address=Hash(key);
    while (H->Keyword[address]!=-1)
        address=(address+1)%p;//线性探测再散列
    H->Keyword[address]=key;
}

void SearchHash1(HashTable* H,int key){//在哈希表中查找关键字
    int address=Hash(key),num=0;
    while (H->Keyword[address]!=key){
        num++;
        address=(address+1)%p;
        if(H->Keyword[address]==-1||address==Hash(key)){//假如查找到一个没有关键字的位置或者查找了一圈回到原来的位置，说明哈希表中没有该关键字
            cout<<"哈希表中没有该关键字"<<endl;
            break;
        }
    }
    H->SuccessFind[address]=++num;
}

void JudgeFail1(HashTable* H){//求在每个地址查找失败时的最小散列次数
    int i,temp;
    for(i=0;i<p;i++){
        H->FailFind[i]++;
        temp=i;
        while (H->Keyword[temp]!=-1){
            temp=(temp+1)%p;
            if(H->Keyword[temp]!=H->Keyword[i])
                H->FailFind[i]++;
            else{
                H->FailFind[i]++;
                break;
            }
        }
    }
}