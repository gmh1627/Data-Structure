#include<iostream>
using namespace std;
typedef struct StackList{
    char ope; //储存括号的链栈节点
    struct StackList* next;
}Stack;

Stack* PushStack(Stack** S,char c){//将括号进栈
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

char PopStack(Stack** S){//将栈顶括号出栈
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

char GetStackTop(Stack* S){//取栈顶括号
    if(!S)
        return 0;
    return S->ope;
}

int BracketTest(char* a){//检验括号是否匹配
	int i=0;
	Stack* S=NULL;
	char x;
	while(a[i]&&a[i]!='@'){
		switch (a[i]) {
			case '(':
			case '[':
			case '{':
				PushStack(&S,a[i]);
				i++;			
				break;
			case ')':{
				if(!S)
					return 0;
				char c1=PopStack(&S);
				if(c1=='['||c1=='{')
					return 0;
				i++;	
				break;
			}
			case ']':{
				if(!S)
					return 0;
				char c2=PopStack(&S);
				if(c2=='{'||c2=='('||(GetStackTop(S)&&GetStackTop(S)=='('))//判断优先级
					return 0;
				i++;			
				break;
			}
			case '}':{
				if(!S)
					return 0;
				char c3=PopStack(&S);
				if(c3=='('||c3=='['||(GetStackTop(S)&&(GetStackTop(S)=='('||GetStackTop(S)=='[')))//判断优先级
					return 0;
				i++;			
				break;
			}
			default:{
				i++;
				break;
			}
		}
	}
	if(S)
		return 0;
	return 1;	
}

int main(){
    int n,i;
	FILE *fp=fopen("2.txt","r");
	if (!fp) {
        fprintf(stderr, "无法打开文件\n");
        return 0;
    }
    fscanf(fp, "%d", &n);
    fgetc(fp);//读掉换行符
    char st[10][50];
    for(i=0;i<n;i++)
        fgets(st[i],sizeof(st[i]),fp);
    for(i=0;i<n;i++){
	    if(BracketTest(st[i]))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;	
    }
	fclose(fp);
	return 0;
}
