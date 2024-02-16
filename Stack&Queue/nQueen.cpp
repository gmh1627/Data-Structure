#include "stdio.h"    
#include "stdlib.h"   
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 

typedef int Status;
typedef int SElemType; 

typedef struct{
	SElemType data[MAXSIZE]= {0};
	int top; /* 用于栈顶指针 */
}SqStack;

int count = 0;

/*调用此方法用于检测是否符合N皇后规则*/
int placeQueen(SqStack s, int i, int j) { //测试（i、j）是否与1->i-1皇后有冲突（i：行）								
    int k = 1;
    /*进来的是第一行*/
    if (i == 1) /*当场确定-->第一行第一个位置可放*/		
        return 1;
    while (k <= i - 1){				 //j=1到k-1是已经放置了皇后的列
        /*fabs()是对浮点数取绝对值,s.data[k] == j-->同列，fabs(j - s.data[k]) == fabs(i - k）-->同对角*/
        if ((s.data[k] == j) || fabs(j - s.data[k]) == fabs(i - k)) 
            return 0;
        else
            k++;
    }
    return 1;
}

void queen(int n, SqStack &s) {
	int i, j, k,find = 0;
	/*初始化栈顶指针*/
	s.top = 0;			
	/*行作为栈顶指针进栈，初始值为1*/
	s.top++;		
	/*列作为栈顶指针进栈，初始值为1*/     /*--->（1，1）进栈*/
	s.data[s.top] = 1;
    /*条件：栈不空，循环操作-->开启探寻*/
	while (s.top>0) {
        /*i为行数标志，可作为参数使用，也用于判断是否走尽*/
        i = s.top;    
		//当前皇后行数s.top == n-->已经处理完最后一个皇后，所有皇后均放好，输出一个解
        if (s.top == n) {
            printf("第%d个解：", ++count);
            for (k = 1; k<=s.top; k++)
                printf("(%d,%d)", k, s.data[k]);
            printf("\n");
        }
        find = 0;
    /*在i+1行探寻一个放皇后的位置(i+1,j）*/
        for (j = 1; j <= n; j++)
            if (placeQueen(s, i + 1, j)) {
                s.top++;/*行+1入栈*/
                s.data[s.top] = j; /*列入栈*/
                /*找到标志,如果走完此for循环，标志未变更，则走到下一段代码*/
                find = 1;
                break; 
            }
        /*当前行无目标-->退栈*/					
        if (find == 0) {
            while (s.top > 0) {
                /*1-本行无可放位置，退栈,行-1*/
                if (s.data[s.top] == n) 
                    s.top-- ;
                /*2-未走完位置，从下位置出发探寻*/
                for (j = s.data[s.top] + 1; j <= n; j++)/*在后续列中探寻到合适的位置*/
                    if (placeQueen(s, s.top, j)){
                        s.data[s.top] = j;  
                        break;
                    }
    //当前皇后在本行没有可放位置，退栈
                if (j > n)
                    s.top--;
                else
                    break; 
            }
        }
    }
}

int main(){
	SqStack s;
	int n; 
    printf("请输入需要解决皇后数量n\n");
    scanf("%d", &n); 
    if(n>=4){
        printf("%d皇后问题求解如下：\n", n);
        queen(n,s); 
        printf("\n");
    }
    else
        printf("%d皇后问题无解", n);
}
