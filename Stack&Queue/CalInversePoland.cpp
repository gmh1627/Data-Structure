//本程序的缺陷在于，当输入的操作数中有多位数时，无法正确计算，因为在将中缀表达式转为逆波兰表达式时，将单个数字转为字符型，没有考虑多位数的情况，或许可以用空格标记一个数字的结束。
#include <stdio.h>
#include <stdlib.h>

typedef struct StackList{
    char ope; //储存操作符的链栈节点
    struct StackList* next;
}Stack;

typedef struct Linklist{
    char ch;//储存操作符和操作数的链表节点
    struct Linklist* next;
}List;

Stack* InitStack(){//初始化链栈
    return NULL;
}

Stack* PushStack(Stack** S,char c){//将操作符进栈
    Stack *p=(Stack*)malloc(sizeof(Stack));
    if(!p){
        printf("申请空间失败");
        return NULL;
    }
    p->ope=c;
    if(!*S){
        *S=p;
        (*S)->next=NULL;
    }
    else{
        p->next=*S;
        *S=p;
    }
    return *S;
}

char PopStack(Stack** S){//将栈顶操作符出栈
    char c;
    if(!*S){
        printf("链栈为空");
        return 0;
    }
    Stack *p=*S;
    c=p->ope;
    (*S)=(*S)->next;
    free(p);
    return c;
}

char GetStackTop(Stack* S){//取栈顶操作符
    if(!S){
        printf("链栈为空");
        return -1;
    }
    return S->ope;
}

int isOperator(char c){//判断是否为操作符
    const char *p="+-*/()";
    while(*p){
        if(c==*p)
            return 1;
        p++;
    }
    return 0;
}

int isPrior(char c1,char c2){//判断操作符优先级
    const char *ch="#+-*/";
    int i=0,j=0;
    while (ch[i]&&ch[i]!=c1)
        i++;
    if(i==2)//加减同级
        i--;
    if(i==4)//乘除同级
        i--;
    while (ch[j]&&ch[j]!=c2)
        j++;
    if(j==2)//加减同级
        j--;
    if(j==4)//乘除同级
        j--;
    if(i>=j)
        return 1;
    else
        return 0;
}

List* InitList(){//初始化链表
    return NULL;
}

List* PushList(List* link,char c){//将新字符插入链表末尾节点
    List* L=(List*)malloc(sizeof(List)),*rear=link;
    if(!L){
        printf("申请空间失败");
        return link;
    }
    if(!link){
        L->ch=c;
        link=L;
        link->next=NULL;
        return link;
    }
    L->ch=c;
    while (rear->next)
        rear=rear->next;
    rear->next=L;
    L->next=NULL;
    return link;
}

List* InversePoland(char* st){//将中缀表达式转为逆波兰（后缀）表达式
    int i=0,j=0;
    char e;
    Stack *Operate=InitStack();//Operate是在转化中储存操作符的链栈指针
    List *Convert=InitList(),*p=NULL;//Convert是储存转化后的逆波兰表达式的链栈指针
    Operate=PushStack(&Operate,st[i]);
    i++;
    while (st[i]!='#'){
        if(!isOperator(st[i])){
            Convert=PushList(Convert,st[i]);//将操作数插入链表
            i++;
        }
        else{
            if(st[i]=='('){
                Operate=PushStack(&Operate,st[i]);//将左括号进栈
                i++;
            }
            else if(st[i]==')'){
                while(GetStackTop(Operate)!='('){
                    if(GetStackTop(Operate)!='#')
                        Convert=PushList(Convert,PopStack(&Operate));//将栈中操作符插入链表
                    else{
                        printf("括号不匹配\n");
                        break;
                    }
                }
                char ch=PopStack(&Operate);
                i++;
            }
            else{
                if(GetStackTop(Operate)!='('&&GetStackTop(Operate)!='#'&&isPrior(GetStackTop(Operate),st[i]))//若当前操作符优先级不高于栈顶操作符优先级，则将栈顶操作符出栈并插入链表
                    Convert=PushList(Convert,PopStack(&Operate));
                else {
                    Operate=PushStack(&Operate,st[i]);
                    i++;
                }
            }  
        }
    }
    while (Operate->ope!='#')
        PushList(Convert,PopStack(&Operate));//将栈中剩余操作符插入链表
    p=Convert;
    while (p){
        printf("%c",p->ch);
        p=p->next;
    }
    printf("\n");
    return Convert;
}

char Calculate(char c1,char op,char c2){//计算两个操作数运算后的值
    int x1,x2,x;
    char ch[2],c[3];
    ch[0]=c1;
    x1=atoi(ch);//将字符转为整型
    ch[0]=c2;
    x2=atoi(ch);
    switch (op){
        case '+':
            x=x1+x2;
            break;
        case '-':
            x=x1-x2;
            break;
        case '*':
            x=x1*x2;
            break;
        case '/':
            x=x1/x2;
            break;
        default:
            break;
    }
    itoa(x,c,10);//将整型转为字符
    return c[0];
}

char Calculate_InversePoland(List* Convert){//计算逆波兰表达式的值
    Stack* Opnd=InitStack();
    int i;
    char c,e1,e2,res;
    List* L=Convert;
    while (L){
        if(!isOperator(L->ch))
            PushStack(&Opnd,L->ch);//将操作数进栈
        else{
            e1=PopStack(&Opnd);
            e2=PopStack(&Opnd);
            res=Calculate(e1,L->ch,e2);
            PushStack(&Opnd,res);
        }
        L=L->next;
    }
    return res;
}

int main(){
    char st[20];
    printf("请输入四则运算式子,且首尾需加上'#'（如#(1+2)*3#)");
    scanf("%s",st);
    List* Convert=InversePoland(st);
    char res=Calculate_InversePoland(Convert);
    printf("%c",res);
}