#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef struct polynode{//储存多项式项的链表节点
    float coefficient;//系数
    int exponent;//指数
    struct polynode *next;
}Node;

#define LinkNum 2

void printMenu();//打印菜单
void clearCache();//清除缓冲区无用数据
Node* Create();//创建多项式链表
Node* reCreate(Node*);//重建多项式链表
void Print(Node*);//打印多项式链表
Node* Addition(Node*,Node*);//多项式加法
Node* Subtraction(Node*,Node*);//多项式减法
void Evaluate(Node*);//多项式求值
float Evaluate2(Node*,float);//已知未知数的多项式求值
Node* Clear(Node*);//多项式链表清空
void Destroy(Node* &);//多项式链表销毁
void Modify(Node* &);//多项式修改
void InsertNode(Node* &);//插入节点
void DeleteNode(Node* &);//删除节点
void ModifyNode(Node* &);//修改节点
Node* Differential(Node*);//多项式微分
Node* Derivation(Node*);//多项式求高阶导
Node* Indefinite_Integral(Node*);//多项式不定积分
void Definite_Integral(Node*);//多项式定积分
Node* Multiplication(Node*,Node*);//多项式乘法
Node* Exponentiation(Node*);//多项式乘方
Node* DeleteZero(Node*);//把系数为0的非零节点删除
Node* AddZero(Node*);//把稀疏多项式中缺少的次数用0补齐
void Division(Node*,Node*);//多项式除法
Node* NewDivision(Node*,Node*);//舍去余式的多项式除法
void Arithmetic(Node*,Node*);//实现给定的多项式四则运算，除法不保留余式

int main() {
    char ch;
    Node* headlist[2];
    int i;
    printf("现在开始创建%d个多项式链表\n",LinkNum);
    for(i=0;i<LinkNum;i++){
        printf("第%d个:\n",i+1);
        headlist[i]=Create();
        printf("第%d个",i+1);
        Print(headlist[i]);
        printf("\n");
        clearCache();
    }
    while (1) {
        printMenu();
        printf("请选择对应功能的序号:");
        scanf("%c", &ch);
        clearCache();
        if (ch == 'q')
            break;
        switch (ch) {
            case'a':{//多项式加法
                int i,j;
                printf("请输入进行运算的多项式序号:");
                scanf("%d%d",&i,&j);
                clearCache();
                Node* res1=Addition(headlist[i-1],headlist[j-1]);
                printf("和");
                Print(res1);
                printf("\n");
                Destroy(res1);
                break;
            }
            case'b':{//多项式减法
                int i,j;
                printf("请输入进行运算的多项式序号:");
                scanf("%d%d",&i,&j);
                clearCache();
                Node* res2=Subtraction(headlist[i-1],headlist[j-1]);
                printf("差");
                Print(res2);
                printf("\n");
                Destroy(res2);
                break;
            }
            case'c':{//多项式求值
                int i;
                printf("请输入进行求值的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Evaluate(headlist[i-1]);
                break;
            }
            case'd':{//多项式修改
                int i;
                printf("请输入进行修改的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Modify(headlist[i-1]);
                printf("\n");
                break;
            }
            case'e':{//多项式求导
                int i;
                printf("请输入求导的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Node* res4=Derivation(headlist[i-1]);
                printf("求导后");
                Print(res4);
                printf("\n");
                Destroy(res4);
                break;
            }
            case'f':{//多项式不定积分
                int i;
                printf("请输入求不定积分的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Node* res5=Indefinite_Integral(headlist[i-1]);
                printf("求不定积分后");
                Print(res5);
                printf("+C(常数)\n");
                Destroy(res5);
                break;
            }
            case'g':{//多项式定积分
                int i;
                printf("请输入求定积分的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Definite_Integral(headlist[i-1]);
                break;
            }
            case'h':{//多项式乘法
                int i,j;
                printf("请输入进行运算的多项式序号:");
                scanf("%d%d",&i,&j);
                clearCache();
                Node* res7=Multiplication(headlist[i-1],headlist[j-1]);
                printf("积");
                Print(res7);
                printf("\n");
                Destroy(res7);
                break;
            }
            case'i':{//多项式乘方
                int i;
                printf("请输入求乘方的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Node* res8=Exponentiation(headlist[i-1]);
                printf("求乘方后");
                Print(res8);
                printf("\n");
                Destroy(res8);
                break;
            }
            case'j':{//多项式除法
                int i,j;
                printf("请输入进行运算的多项式序号:");
                scanf("%d%d",&i,&j);
                clearCache();
                Division(headlist[i-1],headlist[j-1]);
                printf("\n");
                break;
            }
            case'k': {//多项式四则运算
                Arithmetic(headlist[0],headlist[1]);
                printf("\n");
                break;
            }
            case'l':{//多项式链表清空重建
                int i;
                printf("请输入需要清空重建的多项式序号:");
                scanf("%d",&i);
                clearCache();
                Node* res11=Clear(headlist[i-1]);
                printf("清空后");
                Print(res11);
                printf("\n");
                Node* head20=reCreate(res11);
                printf("重建后");
                Print(head20);
                printf("\n");
                Destroy(res11);
                Destroy(head20);
                break;
            }
            default:
                break;
        }
    }
    for(i=0;i<LinkNum;i++)
        Destroy(headlist[i]);
    return 0;
}

void printMenu() {//打印菜单
    printf("************************\n");
    printf("一元多项式运算器功能菜单\n");
    printf("************************\n");
    printf("    q、退出\n");
    printf("    a、多项式加法\n");
    printf("    b、多项式减法\n");
    printf("    c、多项式求值\n");
    printf("    d、多项式修改\n");
    printf("    e、多项式求导\n");
    printf("    f、多项式不定积分\n");
    printf("    g、多项式定积分\n");
    printf("    h、多项式乘法\n");
    printf("    i、多项式乘方\n");
    printf("    j、多项式除法\n");
    printf("    k、多项式四则运算\n");
    printf("    l、多项式清空重建\n");
    printf("************************\n");
}

void clearCache(void) {//清除缓冲区无用数据
    while (getchar() != '\n')
        ;
}

Node* DeleteZero(Node* head){//把系数为0的非零次节点删除
    Node *p=head->next,*rear=head,*q=NULL;
    int i;
    while (p){
        if(!p->coefficient&&p->exponent){//把非零次项的0系数节点删除
            q=p;
            rear->next=p->next;
            p=p->next;
            free(q);
        }
        else if(rear!=head&&!p->coefficient&&!p->exponent){//把有非零系数的非零次项且末项为0的多项式末项删去
            rear->next=NULL;
            q=p;
            free(q);
            p=NULL;
        }
        else{//当只有一项0时能得以保留
            p=p->next;
            rear=rear->next;
        }
    }
    i=0;
    p=head->next;
    while (p){//遍历得到多项式项数
        i++;
        p=p->next;
    }
    if(i){
        head->exponent=i;
        return head;
    }
    else{//将形如0x^3+0x^2的多项式去掉0系数项后还需补一个0，使其还有一项
        p=(Node*)malloc(sizeof(Node));
        if(!p){
            printf("申请空间失败\n");
            return NULL;
        }
        p->coefficient=0;
        p->exponent=0;
        head->exponent=1;
        p->next=NULL;
        head->next=p;
        return head;
    }
}

Node* Create(){//尾插法创建多项式链表，头节点指数域储存多项式项数，每项次数不小于0
    Node *p=NULL,*head=NULL,*rear=NULL;
    int i,n;
    printf("请输入多项式项数");
    scanf("%d",&n);
    clearCache();
    head=(Node*)malloc(sizeof(Node));
    if(!head){
        printf("申请空间失败\n");
        return NULL;
    }
    head->coefficient=0;
    head->next=NULL;
    rear=head;
    if(n){
		printf("请依次输入多项式系数（浮点型)与指数（整型，降序排列且不小于0）");
	    for(i=0;i<n;i++){
	        p=(Node*)malloc(sizeof(Node));
	        if(!p){
	            printf("申请空间失败\n");
	            return NULL;
	        }
	        scanf("%f%d",&p->coefficient,&p->exponent);
            if(p->exponent>=0&&rear!=head&&p->exponent>rear->exponent){
                printf("项要降幂排列\n");
                break;
            }
            else if(p->exponent<0){
                printf("项的次数不能小于零\n");
                break;
            }
            else{
	            rear->next=p;
	            rear=p;
	            rear->next=NULL;
            }
	    }
	    head=DeleteZero(head);
	}
    else
    	head->exponent=0;
    return head;
}

Node* reCreate(Node* given_head){//重建多项式链表，与上面函数类似
    Node *p=NULL,*head=given_head,*rear=NULL;
    int i,n;
    printf("现在重建多项式链表,请输入多项式项数");
    scanf("%d",&n);
    clearCache();
    printf("\n");
    head=(Node*)malloc(sizeof(Node));
    if(!head){
        printf("申请空间失败\n");
        return NULL;
    }
    p=head->next=NULL;
    rear=head;
    printf("请依次输入多项式系数（浮点型)与指数（整型，降序排列且不小于0）");
    if(n){
        for(i=0;i<n;i++){
            p=(Node*)malloc(sizeof(Node));
            if(!p){
                printf("申请空间失败\n");
                return NULL;
            }
            scanf("%f%d",&p->coefficient,&p->exponent);
            if(p->exponent>=0&&rear!=head&&p->exponent>rear->exponent){
                printf("项要降幂排列\n");
                break;
            }
            else if(p->exponent<0){
                printf("项的次数不能小于零\n");
                break;
            }
            else{
	            rear->next=p;
	            rear=p;
	            rear->next=NULL;
            }
        }
        head=DeleteZero(head);
    }
    else
        head->exponent=0;
    return head;
}

void Print(Node *head){//打印多项式链表成类似5x^3+(-x^2)+1的形式，注意考虑0及系数为正负1和一般正负数时的特殊的打印方式
    if(head){
        Node *p=head;
        printf("多项式有%d项",p->exponent);
        if(p->next){
            p=p->next;
            while(p&&p->next){
                if(!p->coefficient)
                    p=p->next;
                else if(p->exponent>1){
                    if(p->coefficient!=1&&p->coefficient>0){
                        printf("%fx^%d+",p->coefficient,p->exponent);
                        p=p->next;
                    }
                    else if(p->coefficient!=-1&&p->coefficient<0){
                        printf("(%fx^%d)+",p->coefficient,p->exponent);
                        p=p->next;
                    }
                    else if(p->coefficient==-1){
                        printf("(-x^%d)+",p->exponent);
                        p=p->next;
                    }
                    else{
                        printf("x^%d+",p->exponent);
                        p=p->next;
                    }
                }
                else if(p->coefficient!=1&&p->coefficient>0){
                    printf("%fx+",p->coefficient);
                    p=p->next;
                }
                else if(p->coefficient==-1){
                    printf("(-x)+");
                    p=p->next;
                }
                else if(p->coefficient!=-1&&p->coefficient<0){
                    printf("(%fx)+",p->coefficient);
                    p=p->next;
                }
                else{
                    printf("x+");
                    p=p->next;
                }
            }
            if(p->exponent){
                if(p->exponent==1){
                    if(p->coefficient!=-1&&p->coefficient<0)
                        printf("(%fx)",p->coefficient);
                    else if(p->coefficient==-1)
                        printf("(-x)");
                    else if(p->coefficient!=1&&p->coefficient>0)
                        printf("%fx",p->coefficient);
                    else
                        printf("x");
                }
                else if(p->coefficient<0&&p->coefficient!=-1)
                    printf("(%fx^%d)",p->coefficient,p->exponent);
                else if(p->coefficient==-1)
                    printf("(-x^%d)",p->exponent);
                else if(p->coefficient!=1&&p->coefficient>0)
                    printf("%fx^%d",p->coefficient,p->exponent);    
                else
                    printf("x^%d",p->exponent);
            }
            else{
                if(p->coefficient>=0)
                    printf("%f",p->coefficient);
                else if(p->coefficient<0)
                    printf("(%f)",p->coefficient);
            }
        }
    }
    else
        printf("多项式无法打印");
}

Node* Addition(Node* head1,Node* head2){//多项式加法，把结果储存到一个新链表
    if(!head1||!head2){
		printf("\n进行加法运算的多项式不能没有项\n");
		return NULL;
	}
    Node *node=(Node*)malloc(sizeof(Node)),*p=head1->next,*q=head2->next,*rear=NULL,*pt=NULL;
    if(!node){
        printf("申请空间失败\n");
        return NULL;
    }
    int i=0;
    node->next=NULL;
    pt=node;
    while(p&&q){
		if(p->exponent>q->exponent){
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=p->coefficient;
			rear->exponent=p->exponent;
			p=p->next;
		}
		else if(q->exponent>p->exponent){
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=q->coefficient;
			rear->exponent=q->exponent;
			q=q->next;
		}
		else{
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=p->coefficient+q->coefficient;
			rear->exponent=q->exponent;
			q=q->next;
			p=p->next;
		}
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
	while(!p&&q){
		rear=(Node*)malloc(sizeof(Node));
		if(!rear){
			printf("申请空间失败\n");
			return NULL;
		}
		rear->coefficient=q->coefficient;
		rear->exponent=q->exponent;
		q=q->next;
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
	while(!q&&p){
		rear=(Node*)malloc(sizeof(Node));
		if(!rear){
			printf("申请空间失败\n");
			return NULL;
		}
		rear->coefficient=p->coefficient;
		rear->exponent=p->exponent;
		p=p->next;
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
    node=DeleteZero(node);
    return node;
}

Node* Subtraction(Node* head1,Node* head2){//多项式减法，把结果储存到一个新链表，与加法基本相同，只是符号有差别
    if(!head1||!head2){
		printf("进行运算的多项式不能没有项\n");
		return NULL;
	}
	Node *node=(Node*)malloc(sizeof(Node)),*p=head1->next,*q=head2->next,*rear=NULL,*pt=NULL;
    if(!node){
        printf("申请空间失败\n");
        return NULL;
    }
    int i=0;
    node->next=NULL;
    pt=node;
    while(p&&q){
		if(p->exponent>q->exponent){
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=p->coefficient;
			rear->exponent=p->exponent;
			p=p->next;
		}
		else if(q->exponent>p->exponent){
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=-q->coefficient;
			rear->exponent=q->exponent;
			q=q->next;
		}
		else{
			rear=(Node*)malloc(sizeof(Node));
			if(!rear){
				printf("申请空间失败\n");
				return NULL;
			}
			rear->coefficient=p->coefficient-q->coefficient;
			rear->exponent=q->exponent;
			q=q->next;
			p=p->next;
		}
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
	while(!p&&q){
		rear=(Node*)malloc(sizeof(Node));
		if(!rear){
			printf("申请空间失败\n");
			return NULL;
		}
		rear->coefficient=-q->coefficient;
		rear->exponent=q->exponent;
		q=q->next;
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
	while(!q&&p){
		rear=(Node*)malloc(sizeof(Node));
		if(!rear){
			printf("申请空间失败\n");
			return NULL;
		}
		rear->coefficient=p->coefficient;
		rear->exponent=p->exponent;
		p=p->next;
		pt->next=rear;
		pt=rear;
		pt->next=NULL;
	}
    node=DeleteZero(node);
    return node;
}

void Evaluate(Node* head){//未知未知数的多项式求值
    if(!head)
        printf("\n进行运算的多项式不能没有项\n");
    else{
        Node *p=head->next;
        float x,val=0;
        printf("请输入未知数的值（浮点型）");
        scanf("%f",&x);
        clearCache();
        printf("\n");
        while(p){
            double temp=p->exponent;
            val=val+(p->coefficient*pow(x,temp));
            p=p->next;
        }
        printf("x=%f时,多项式的值为%f\n",x,val);
    }
}

float Evaluate2(Node* head,float x){//已知未知数的多项式求值，可用于求定积分
    if(!head){
		printf("\n进行运算的多项式不能没有项\n");
		return 0;
    }
    else{
        Node *p=head->next;
        float val=0;
        while(p){
            double temp=p->exponent;
            val=val+(p->coefficient*pow(x,temp));
            p=p->next;
        }
        clearCache();
        return val;
    }
}

void Destroy(Node* &head){//多项式链表销毁
    Node *p=head,*temp;
    while(p){
        temp=p;
        p=p->next;
        free(temp);
    }
}

Node* Clear(Node* head){//多项式链表清空
    if(!head){
        printf("\n多项式链表已为空\n");
        return NULL;
    }
    Node *p=head->next;
    head->exponent=0;
    Destroy(p);
    head->next=NULL;
    return head;
}

void InsertNode(Node* &head){//插入节点
    if(!head)
        printf("\n进行插入的多项式不能没有项\n");
    else{
        Node *p=head->next,*node=NULL;
        float coef;
        int exp;
        printf("请输入要插入节点的系数(浮点型)和指数(整型)");
        scanf("%f%d",&coef,&exp);
        clearCache();
        if(!p){
            head->next=node;
            node->coefficient=coef;
            node->exponent=exp;
            head->next->next=NULL;
            head->exponent++;
            return ;
        }
        while(p){
            if(p->exponent<exp){
                node=(Node*)malloc(sizeof(Node));
                if(!node)
                    printf("申请空间失败\n");
                node->next=p;
                head->next=node;
                node->coefficient=coef;
                node->exponent=exp;
                head->exponent++;
                return ;
            }
            else if(p->exponent>exp&&p->next->exponent>exp)
                p=p->next;
            else if(p->exponent>exp&&p->next->exponent<exp){
                node=(Node*)malloc(sizeof(Node));
                if(!node)
                    printf("申请空间失败\n");
                node->next=p->next;
                p->next=node;
                node->coefficient=coef;
                node->exponent=exp;
                head->exponent++;
                return ;
            }
            else if(p->exponent==exp)
                p->coefficient=p->coefficient+coef;
            else if(p->exponent>exp&&!p->next){
                node=(Node*)malloc(sizeof(Node));
                if(!node)
                    printf("申请空间失败\n");
                p->next=node;
                node->coefficient=coef;
                node->exponent=exp;
                p->next->next=NULL;
                head->exponent++;
                return ;
            }
        }
    }
}

void DeleteNode(Node* &head){//删除节点
    if(!head)
        printf("\n进行插入的多项式不能没有项\n");
    else{
        Node *p=head->next,*prior=head;
        int exp;
        printf("请输入要删除节点的指数(整型)");
        scanf("%d",&exp);
        clearCache();
        while(p){
            if(p->exponent==exp){
                prior->next=p->next;
                free(p);
                head->exponent--;
                return ;
            }
            p=p->next;
            prior=prior->next;
        }
        printf("找不到要删除指数对应的项");
        return ;
    }
}

void ModifyNode(Node* &head){//修改节点
    if(!head)
        printf("\n进行插入的多项式不能没有项\n");
    else{
        Node *p=head->next;
        float coef;
        int exp;
        printf("请输入要修改节点的指数(整型)");
        scanf("%d",&exp);
        clearCache();
        while(p){
            if(p->exponent==exp){
                printf("请输入修改节点后的系数(浮点型)");
                scanf("%f",&coef);
                clearCache();
                p->coefficient=coef;
                return ;
            }
            p=p->next;
        }
        printf("找不到要修改指数对应的项");
        return ;
    }
}

void Modify(Node* &head){//多项式修改
    char ch;
    while (1) {
        printf("************************\n");
        printf("    q、退出\n");
        printf("    a、插入节点\n");
        printf("    b、删除节点\n");
        printf("    c、修改节点\n");
        printf("************************\n");
        printf("请选择对应功能的序号：");
        scanf("%c", &ch);
        clearCache();
        printf("\n");
        if (ch == 'q')
            break;
        switch (ch) {
            case'a':{
                InsertNode(head);
                printf("插入节点后");
                Print(head);
                printf("\n");
                break;
            }
            case'b':{
                DeleteNode(head);
                printf("删除节点后");
                Print(head);
                printf("\n");
                break;
            }
            case'c':{
                ModifyNode(head);
                printf("修改节点后");
                Print(head);
                printf("\n");
                break;
            }
            default:
                break;
        }
    }
}

Node* Differential(Node* head){//多项式微分，把结果储存到一个新链表
    if(!head){
		printf("\n进行求微分运算的多项式不能没有项\n");
		return NULL;
	}
    Node* node=(Node*)malloc(sizeof(Node)),*rear=NULL,*q=NULL,*p=head->next;
    int i;
    if(!node){
        printf("申请空间失败\n");
        return NULL;
    }
    q=node->next;
    rear=node;
    for(i=0;i<head->exponent&&p->exponent;i++){
        q=(Node*)malloc(sizeof(Node));
        if(!q){
            printf("申请空间失败\n");
            return NULL;
        }
        q->coefficient=p->coefficient*p->exponent;
        q->exponent=p->exponent-1;
        rear->next=q;
        rear=q;
        rear->next=NULL;
        p=p->next;
    }
    node=DeleteZero(node);
    return node;
}

Node* Derivation(Node* head){//反复调用求微分的函数求高阶导，把结果储存到一个新链表
    if(!head){
		printf("\n进行求高阶导运算的多项式不能没有项\n");
		return NULL;
	}
    int n,i;
    printf("请输入求导阶数");
    scanf("%d",&n);
    clearCache();
    Node* node=head;
    for(i=0;i<n;i++){
        node=Differential(node);
        if(!node){
            printf("求导异常\n");
            return NULL;
        }
    }
    node=DeleteZero(node);
    return node;
}

Node* Indefinite_Integral(Node* head){//多项式不定积分，把结果储存到一个新链表
    if(!head->next||!head){
		printf("\n进行求不定积分运算的多项式不能没有项\n");
		return NULL;
	}
    Node *node=(Node*)malloc(sizeof(Node)),*rear=NULL,*q=NULL,*p=head;
    int i;
    if(!node){
        printf("申请空间失败\n");
        return NULL;
    }
    q=node->next;
    p=p->next;
    rear=node;
    for(i=0;i<head->exponent;i++){
        q=(Node*)malloc(sizeof(Node));
        if(!q){
            printf("申请空间失败\n");
            return NULL;
        }
        q->coefficient=p->coefficient/(p->exponent+1);
        q->exponent=p->exponent+1;
        rear->next=q;
        rear=q;
        rear->next=NULL;
        p=p->next;
    }
    node=DeleteZero(node);
    node->exponent++;//因为还有一个常数项
    return node;
}

void Definite_Integral(Node* head){//多项式定积分
    if(!head)
        printf("\n进行求定积分运算的多项式不能没有项\n");
    else{
        Node *node=(Node*)malloc(sizeof(Node)),*rear=NULL,*q=NULL,*p=head;
        int i;
        float lower,upper;
        if(!node)
            printf("申请空间失败\n");
        q=node->next;
        p=p->next;
        rear=node;
        for(i=0;i<head->exponent;i++){
            q=(Node*)malloc(sizeof(Node));
            if(!q)
                printf("申请空间失败\n");
            q->coefficient=p->coefficient/(p->exponent+1);
            q->exponent=p->exponent+1;
            rear->next=q;
            rear=q;
            rear->next=NULL;
            p=p->next;
        }
        node=DeleteZero(node);
        printf("请分别输入积分下限和上限（浮点数）");
        scanf("%f%f",&lower,&upper);
        printf("以%f和%f作为积分下上限的定积分结果是%f\n",lower,upper,Evaluate2(node,upper)-Evaluate2(node,lower));
        Destroy(node);
    }
}

Node* Multiplication(Node* head1,Node* head2){//多项式乘法，把结果储存到一个新链表。原理是用第一个乘数的每一项依次乘以第二个乘数后依次把结果的头指针储存到一个长为head1->exponent的指针数组里
    if(!head1||!head2){
		printf("\n进行乘法运算的多项式不能没有项\n");
		return NULL;
	}
    Node *node=NULL,*p=head1,*q=head2->next,*list[head1->exponent];
    int i;
    for(i=0;i<head1->exponent;i++){
        p=p->next;
        list[i]=(Node*)malloc(sizeof(Node));
        if(!list){
            printf("申请空间失败\n");
            return NULL;
        }
        list[i]->exponent=head2->exponent;
        Node *rear=NULL,*pt=list[i];
        while (q){
            rear=(Node*)malloc(sizeof(Node));
            if(!rear){
                printf("申请空间失败\n");
                return NULL;
            }
            rear->exponent=p->exponent+q->exponent;
            rear->coefficient=p->coefficient*q->coefficient;
            q=q->next;
            pt->next=rear;
            pt=rear;
            pt->next=NULL;
        }
        q=head2->next;
    }
    for(i=1;i<head1->exponent;i++)//将指针数组里的多项式累加得到结果
        list[i]=Addition(list[i-1],list[i]);
    node=list[head1->exponent-1];
    node=DeleteZero(node);
    for(i=0;i<head1->exponent-1;i++)
        Destroy(list[i]);
    return node;
}

Node* Exponentiation(Node* head){//反复调用乘法函数求多项式乘方，把结果储存到一个新链表
    if(!head){
		printf("\n进行乘方运算的多项式不能没有项\n");
		return NULL;
	}
    int i,n;
    printf("请输入次方数");
    scanf("%d",&n);
    clearCache();
    Node* list[n];
    list[0]=head;
    for(i=1;i<n;i++)//将原多项式乘上n次
        list[i]=Multiplication(head,list[i-1]);
    list[n-1]=DeleteZero(list[n-1]);
    for(i=0;i<n-1;i++)
        Destroy(list[i]);
    return list[n-1];
}

Node* AddZero(Node* head){//把稀疏多项式中缺少的次数用0补齐，用于除法函数的被除式
    Node *p=head->next,*rear=NULL;
    while(p){
        if(p->next&&p->next->exponent!=p->exponent-1){
            rear=(Node*)malloc(sizeof(Node));
            if(!rear){
                printf("申请空间失败\n");
                return NULL;
            }
            rear->coefficient=0;
            rear->exponent=p->exponent-1;
            rear->next=p->next;
            p->next=rear;
        }
        else if(!p->next&&p->exponent){
            rear=(Node*)malloc(sizeof(Node));
            if(!rear){
                printf("申请空间失败\n");
                return NULL;
            }
            rear->coefficient=0;
            rear->exponent=p->exponent-1;
            p->next=rear;
			p->next->next=NULL;
        }
        p=p->next;
    }
    p=head->next;
    int i=0;
    while (p){
        i++;
        p=p->next;
    }
    head->exponent=i;
    return head;
}

void Division(Node* head1,Node* head2){//多项式除法，打印商式和余式
    if(!head1||!head2)
        printf("\n进行除法运算的多项式不能没有项\n");
    else{
        Node *Dividend=AddZero(head1),*Divisor=DeleteZero(head2);
        if(!Divisor->next->coefficient)
            printf("除数不能为零！");
        Node *Remainder=Dividend,*Quotient=(Node*)malloc(sizeof(Node)),*p=NULL,*rear=NULL;//Dividen表示被除式指针，Divisor表示除式指针，Quotient表示商式指针，Remainder表示余式指针
        if(!Quotient)
            printf("申请空间失败\n");
        rear=Quotient;
        rear->exponent=1;//首先把商式置为0
        rear->next=NULL;
        p=(Node*)malloc(sizeof(Node));
        if(!p)
            printf("申请空间失败\n");
        p->coefficient=0;
        p->exponent=0;
        rear->next=p;
        rear=p;
        rear->next=NULL;
		Remainder=Subtraction(Remainder,Multiplication(Quotient,Divisor));
        while (Remainder->next->exponent>Divisor->next->exponent){//余式次数高于除式，进入循环
            Node* pt=Remainder->next;
            if(!rear->coefficient&&!rear->exponent){//初始状态商式为0时
                rear->coefficient=pt->coefficient/Divisor->next->coefficient;
                rear->exponent=pt->exponent-Divisor->next->exponent;
            }
            else
            {
                p=(Node*)malloc(sizeof(Node));
                if(!p)
                    printf("申请空间失败\n");
                p->coefficient=pt->coefficient/Divisor->next->coefficient;
                p->exponent=pt->exponent-Divisor->next->exponent;
                rear->next=p;
                rear=p;
                rear->next=NULL;
            }
            Node *temp=(Node*)malloc(sizeof(Node));//temp的内容为商式的最后一项
            if(!temp){
                printf("申请空间失败\n");
                break;
            }
            temp->exponent=1;
            temp->next=(Node*)malloc(sizeof(Node));
            if(!temp->next){
                printf("申请空间失败\n");
                break;
            }
            temp->next->coefficient=rear->coefficient;
            temp->next->exponent=rear->exponent;
            temp->next->next=NULL;
            Remainder=Subtraction(Remainder,Multiplication(temp,Divisor));
        }
		if(Remainder->next->exponent==Divisor->next->exponent){//余式次数等于除式
			Node* pt=Remainder->next;
            if(!rear->coefficient&&!rear->exponent){
                rear->coefficient=pt->coefficient/Divisor->next->coefficient;
                rear->exponent=pt->exponent-Divisor->next->exponent;
            }
            else{
                p=(Node*)malloc(sizeof(Node));
                if(!p)
                    printf("申请空间失败\n");
                p->coefficient=pt->coefficient/Divisor->next->coefficient;
                p->exponent=pt->exponent-Divisor->next->exponent;
                rear->next=p;
                rear=p;
                rear->next=NULL;
            }
            Node *temp=(Node*)malloc(sizeof(Node));
            if(!temp)
                printf("申请空间失败\n");
            temp->exponent=1;
            temp->next=(Node*)malloc(sizeof(Node));
            if(!temp->next)
                printf("申请空间失败\n");
            temp->next->coefficient=rear->coefficient;
            temp->next->exponent=rear->exponent;
            temp->next->next=NULL;
            Remainder=Subtraction(Remainder,Multiplication(temp,Divisor));
		}
        Quotient=DeleteZero(Quotient);
        printf("商");
        Print(Quotient);
        printf("\n");
        Remainder=DeleteZero(Remainder);
        printf("余");
        Print(Remainder);
        Destroy(Remainder);
        printf("\n");
    }
}

Node* NewDivision(Node* head1,Node* head2){//舍去余式的多项式除法，返回商式
    if(!head1||!head2){
        printf("\n进行除法运算的多项式不能没有项\n");
        return NULL;
    }
    else{
        Node *Dividend=AddZero(head1),*Divisor=DeleteZero(head2);
        if(!Divisor->next->coefficient)
            printf("除数不能为零！");
        Node *Remainder=Dividend,*Quotient=(Node*)malloc(sizeof(Node)),*p=NULL,*rear=NULL;//Dividen表示被除式指针，Divisor表示除式指针，Quotient表示商式指针，Remainder表示余式指针
        if(!Quotient)
            printf("申请空间失败\n");
        rear=Quotient;
        rear->exponent=1;//首先把商式置为0
        rear->next=NULL;
        p=(Node*)malloc(sizeof(Node));
        if(!p)
            printf("申请空间失败\n");
        p->coefficient=0;
        p->exponent=0;
        rear->next=p;
        rear=p;
        rear->next=NULL;
		Remainder=Subtraction(Remainder,Multiplication(Quotient,Divisor));
        while (Remainder->next->exponent>Divisor->next->exponent){//余式次数高于除式，进入循环
            Node* pt=Remainder->next;
            if(!rear->coefficient&&!rear->exponent){//初始状态商式为0时
                rear->coefficient=pt->coefficient/Divisor->next->coefficient;
                rear->exponent=pt->exponent-Divisor->next->exponent;
            }
            else{
                p=(Node*)malloc(sizeof(Node));
                if(!p)
                    printf("申请空间失败\n");
                p->coefficient=pt->coefficient/Divisor->next->coefficient;
                p->exponent=pt->exponent-Divisor->next->exponent;
                rear->next=p;
                rear=p;
                rear->next=NULL;
            }
            Node *temp=(Node*)malloc(sizeof(Node));//temp的内容为商式的最后一项
            if(!temp){
                printf("申请空间失败\n");
                break;
            }
            temp->exponent=1;
            temp->next=(Node*)malloc(sizeof(Node));
            if(!temp->next){
                printf("申请空间失败\n");
                break;
            }
            temp->next->coefficient=rear->coefficient;
            temp->next->exponent=rear->exponent;
            temp->next->next=NULL;
            Remainder=Subtraction(Remainder,Multiplication(temp,Divisor));
        }
		if(Remainder->next->exponent==Divisor->next->exponent){//余式次数等于除式
			Node* pt=Remainder->next;
            if(!rear->coefficient&&!rear->exponent){
                rear->coefficient=pt->coefficient/Divisor->next->coefficient;
                rear->exponent=pt->exponent-Divisor->next->exponent;
            }
            else{
                p=(Node*)malloc(sizeof(Node));
                if(!p)
                    printf("申请空间失败\n");
                p->coefficient=pt->coefficient/Divisor->next->coefficient;
                p->exponent=pt->exponent-Divisor->next->exponent;
                rear->next=p;
                rear=p;
                rear->next=NULL;
            }
            Node *temp=(Node*)malloc(sizeof(Node));
            if(!temp)
                printf("申请空间失败\n");
            temp->exponent=1;
            temp->next=(Node*)malloc(sizeof(Node));
            if(!temp->next)
                printf("申请空间失败\n");
            temp->next->coefficient=rear->coefficient;
            temp->next->exponent=rear->exponent;
            temp->next->next=NULL;
            Remainder=Subtraction(Remainder,Multiplication(temp,Divisor));
		}
        Quotient=DeleteZero(Quotient);
        Destroy(Remainder);
        return Quotient;
    }
}

void Arithmetic(Node* head1,Node* head2){//实现给定的多项式四则运算，除法不保留余式
	printf("(1式+2式)*1式/2式后");
    Print(NewDivision(Multiplication(Addition(head1,head2),head1),head2));
}
