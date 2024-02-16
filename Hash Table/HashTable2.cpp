#include<iostream>
using namespace std;

#define MAXNUM 500

typedef struct Node{
    int data;
    Node* next=NULL;
}Node;

typedef struct SuccessNode{
    int SuccessNum;
    SuccessNode* next=NULL;
}SuccessNode;

typedef struct{
    int Address[MAXNUM];//哈希表地址
    int keynum=0;//关键字个数
    Node* Link[MAXNUM];//哈希表链地址
    SuccessNode* SuccessLink[MAXNUM];//成功查找次数
    int FailFind[MAXNUM]={0};//失败查找次数
    float AveSuccess=0;//查找成功的平均查找次数
    float AveFail=0;//查找失败时在各个位置上的平均查找次数
}HashTable;

int p=1;//除留余数法中的除数
int Hash(int);//哈希函数(除留余数法)
void InsertHash2(HashTable*,int);//把关键字插入哈希表
void SearchHash2(HashTable*,int);//在哈希表中查找关键字
void JudgeFail2(HashTable*);//求在每个地址查找失败时的最小散列次数

int main(){
    int i,j,key[MAXNUM];
    HashTable *hashtable = new HashTable;
    cout<<"请依次输入关键字个数、关键字和除留余数法中的除数"<<endl;
    cin>>hashtable->keynum;
    for(i=0;i<hashtable->keynum;i++)
        cin>>key[i];
    cin>>p;
    for(i=0;i<p;i++){
        hashtable->Address[i]=i;
        hashtable->Link[i]=NULL;
        hashtable->SuccessLink[i]=NULL;
    }
    cout<<"哈希表地址：";
    for(i=0;i<p;i++)
        cout<<hashtable->Address[i]<<"  ";
    cout<<endl;
    for(i=0;i<hashtable->keynum;i++)
        InsertHash2(hashtable,key[i]);
    Node* pt[p];
    for(i=0;i<p;i++)
        pt[i]=hashtable->Link[i];
    cout<<"表中关键字：";
    for(j=0;j<p;j++){
        if(pt[j]){
            cout<<j<<"(";
            while(pt[j]){
                if(pt[j]->next){
                    cout<<pt[j]->data<<" ";
                    pt[j]=pt[j]->next;
                }
                else{
                    cout<<pt[j]->data;
                    break;
                }
            }
            cout<<") ";
        }
    }
    cout<<endl;
    SuccessNode* pt2[p];
    for(i=0;i<hashtable->keynum;i++)
        SearchHash2(hashtable,key[i]);
    for(i=0;i<p;i++)
        pt2[i]=hashtable->SuccessLink[i];
    cout<<"成功查找次数：";
    for(j=0;j<p;j++){
        if(pt2[j]){
            cout<<j<<"(";
            while(pt2[j]){
                if(pt2[j]->next){
                    cout<<pt2[j]->SuccessNum<<" ";
                    pt2[j]=pt2[j]->next;
                }
                else{
                    cout<<pt2[j]->SuccessNum;
                    break;
                }
            }
            cout<<") ";
        }
        else
            cout<<j<<"(0) ";
    }
    cout<<endl;
    JudgeFail2(hashtable);//求在每个地址查找失败时的最小散列次数
    cout<<"失败查找次数：";
    for(i=0;i<p;i++){
        cout<<i<<":"<<hashtable->FailFind[i]<<"  ";
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

void InsertHash2(HashTable* H,int key){//链地址法把关键字插入哈希表
    int address=Hash(key);
    Node* newNode = new Node;
    newNode->data = key;
    newNode->next = NULL;
    if(!H->Link[address])
        H->Link[address] = newNode;
    else {
        Node* pt = H->Link[address];
        while (pt->next) 
            pt = pt->next;
        pt->next = newNode;
    }
}

void SearchHash2(HashTable* H,int key){//在哈希表中查找关键字
    int address=Hash(key),num=0;
    Node* pt=H->Link[address];
    if(!pt){
        cout<<"哈希表中没有该关键字"<<endl;
        return;
    }
    while(pt){
        num++;
        if(pt->data == key){
            if(!H->SuccessLink[address]){
                SuccessNode* newNode = new SuccessNode;
                newNode->SuccessNum=num;
                newNode->next = NULL;
                H->AveSuccess+=num;
                H->SuccessLink[address]=newNode;
            }
            else {
                SuccessNode* pt2 = H->SuccessLink[address];
                SuccessNode* newNode = new SuccessNode;
                newNode->SuccessNum=num;
                newNode->next = NULL;
                H->AveSuccess+=num;
                while (pt2->next) 
                    pt2 = pt2->next;
                pt2->next = newNode;
            }
            return;
        }
        pt = pt->next;
    }
    cout<<"哈希表中没有该关键字"<<endl;   
}

void JudgeFail2(HashTable* H){//求在每个地址查找失败时的最小散列次数
    int i,temp;
    for(i=0;i<p;i++){
        H->FailFind[i]++;
        if(H->Link[i]){
            Node* pt=H->Link[i];
            while(pt){
                H->FailFind[i]++;
                pt=pt->next;
            }
        }
    }
}
