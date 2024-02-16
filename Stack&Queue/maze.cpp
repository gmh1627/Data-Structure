#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define MAXLEN 25		//迷宫包括外墙的最大行列数
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 15
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define UNDERFLOW -3
using namespace std;

typedef int status;
 
//坐标位置类型
typedef struct {
	int r;		//迷宫中第r行
	int c;		//迷宫中第c列
}PosType;
 
//栈中元素值域的类型
typedef struct {
	int ord;		//通道块在路径上的序号
	PosType seat;		//通道块在迷宫上的通道位置
	int di;		//从此通道块走向下一通道的方向
}SElemType;
 
//定义链式栈的存储结构
struct LNode {
	SElemType data;		//数据域
	LNode *next;		//指针域
};
 
typedef struct LStack {
	LNode *top;		//栈顶指针
	LNode *base;		//栈底指针
	int stacksize;		//栈的大小
}SqStack;
 
//迷宫类型(需要打印呈现)
typedef struct {
	int	r;
	int c;
	char addr[MAXLEN][MAXLEN];		//表示通道的矩阵
}MazeType;

void InitStack(LStack &s);
status StackEmpty(LStack s);
void PushStack(LStack &s, SElemType e);
void Pop(LStack &s, SElemType &e);
status DestroyStack(LStack &s);
void OverturnStack(SqStack S, SqStack &T);
void InitMaze(MazeType &maze);
status CreatMaze(MazeType &maze, PosType &start, PosType &end);
status WhetherPass(MazeType &maze, PosType curpos);
void FootPrint(MazeType &maze, PosType curpos);
PosType NextPos(PosType &curpos, int i);
void MarkPrint(MazeType &maze, PosType curpos);
status MazePath(MazeType &maze, PosType start, PosType end, SqStack &S);
void PrintMaze(MazeType &maze, PosType start, PosType end);
void PrintStack(SqStack S);
 
//主函数
int main(void) {
	SqStack S, T;
	InitStack(T);
	MazeType maze;
	PosType start, end;
	start.c = start.r = 0; end.c = end.r = 0;
	while (1) {
		//Sleep(200);
        InitStack(S);		//每次都要将S和maze进行初始化，否则将记录上一次的数据，产生错误
		InitMaze(maze);
		printf("----------------创建迷宫开始----------------\n");
		if (!CreatMaze(maze, start, end)) {
			printf("初始化失败!!!\n");
			exit(OVERFLOW);
		}
		printf("----------------创建迷宫结束----------------\n");
		printf("\n");
		printf("----------------原始迷宫模型图(障碍物随机生成)----------------\n");
		PrintMaze(maze, start, end);
		if (!MazePath(maze, start, end, S)){	//当栈被销毁的时候，则没有一条通路
			system("cls"); 
			continue;
		}
		else break;
	}
	printf("\n");
	printf("----------------走出迷宫的路径----------------\n");
	OverturnStack(S, T); PrintStack(T); DestroyStack(S);
	printf("----------------迷宫路径模型图(o代表一条通路)----------------\n");
	PrintMaze(maze, start, end);
}
 
//---------栈的算法开始------------
//构造一个空栈
void InitStack(LStack &s) {
	s.top = (LNode*)malloc(STACK_INIT_SIZE * sizeof(LNode));		//为指针p分配空间
	s.base=(LNode*)malloc(STACK_INIT_SIZE * sizeof(LNode));
	if (!s.base) {
		printf("分配失败，退出程序!");
		exit(OVERFLOW);
	}
	s.base=s.top;		//将栈底和栈顶指针指向p指向的位置		
	s.stacksize = STACK_INIT_SIZE;
}
 
//若栈s为空栈，则返回true，否则返回false
status StackEmpty(LStack s) {
	if (s.top == s.base) return TRUE;		//若栈顶指针与栈底指针重合，则是空栈
	else return FALSE;
}
 
//插入元素e成为新的栈顶元素
void PushStack(LStack &s, SElemType e) {
	if (s.top - s.base >= s.stacksize) {
		s.base = (LNode*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(LNode));
		if (!s.base) exit(OVERFLOW);
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	(*s.top).data.di= e.di;
	(*s.top).data.ord = e.ord;
	(*s.top).data.seat.r = e.seat.r;
	(*s.top).data.seat.c = e.seat.c;
	s.top++;
	return;
}
 
//删除s的栈顶元素，并用e返回其值
void Pop(LStack &s, SElemType &e) {
	if (s.top == s.base) exit(ERROR);		//如果为空栈，退出
	s.top--;
	e = (*s.top).data;
	return;
}
 
//栈s的销毁
status DestroyStack(LStack &s) {
	free(s.base);
	s.base = NULL;
	s.top = NULL;
	s.stacksize = 0;
	return OK;
}
 
//将栈S中的所有元素翻转至栈T:用于对于路径的输出，由于栈不能直接访问栈底指针，所以需要翻转
void OverturnStack(SqStack S, SqStack &T) {
	SElemType e;
	do {
		Pop(S, e); PushStack(T, e);
	} while (S.base != S.top);
}
//---------栈的算法结束------------
 
//---------迷宫实现开始------------
//初始化迷宫
void InitMaze(MazeType &maze) {
	maze.c = 0;
	maze.r = 0;
	return;
}
 
//创建迷宫
status CreatMaze(MazeType &maze, PosType &start, PosType &end) {
	int i, j, m = 0, n = 0,random;
	srand((unsigned)time(NULL));
	//迷宫的行和列的范围为[3,25]
	printf("随机生成迷宫的行数和列数(包含外墙):");
	maze.r = rand()%23+3; maze.c = rand() % 23 + 3;
	printf("行数:%d,列数:%d\n",maze.r,maze.c);
	for (i = 0; i < maze.c; i++) {
		maze.addr[0][i] = '#';		//给出上下围墙
		maze.addr[maze.r - 1][i] = '#';
	}
	for (i = 1; i < maze.r - 1; i++) {
		maze.addr[i][0] = '#';		//给出左右围墙
		maze.addr[i][maze.c - 1] = '#';
	}
	for (i = 1; i < maze.r - 1; i++) {
		for (j = 1; j < maze.c - 1; j++) {
			//random的范围为[0,1]之间的整数
			random = rand()%2;
			if(!random)
				maze.addr[i][j] = ' ';		//将围墙内的通道块随机赋空值表示可通行
			else 
				maze.addr[i][j] = '#';		//将围墙内的通道块随机赋#值表示障碍
		}
	}
	//随机生成的迷宫入口:入口的r只能在[1,(maze.r-2)]之间,c只能为0
	printf("\n随机生成的迷宫入口：");
	start.r = rand()%(maze.r-2)+1;
	start.c = 0;
	printf("(%d,%d)\n",start.r,start.c);
	//随机生成的迷宫出口:出口的r只能在[1,(maze.r-2)]之间,c只能为maze.c
	printf_s("\n随机生成的迷宫出口：");
	end.r = rand() % (maze.r - 2) + 1;
	end.c = maze.c-1;
	printf("(%d,%d)\n", end.r, end.c);
	maze.addr[start.r][start.c] = ' ';
	maze.addr[end.r][end.c] = ' ';
	return OK;
}
 
//判断当前位置可否通过，可通过返回true
status WhetherPass(MazeType &maze, PosType curpos) {
	if (maze.addr[curpos.r][curpos.c] == ' ') return TRUE;
	else return FALSE;
}
 
//若该通道块走过并且可通，就记录下来
void FootPrint(MazeType &maze, PosType curpos) {
	maze.addr[curpos.r][curpos.c] = 'o';
}
 
//指示并返回下一位置的坐标
PosType NextPos(PosType &curpos, int i) {
	switch (i) {		//向各个方向前进一个单位，并返回位置值
		case 1:curpos.c += 1; break;		//向东前进一个单位
		case 2:curpos.r += 1; break;		//向南前进一个单位
		case 3:curpos.c -= 1; break;		//向西前进一个单位
		case 4:curpos.r -= 1; break;		//向北前进一个单位
		default:exit(ERROR);
	}
	return curpos;
}
 
//曾经走过，但不是通路，就标记
void MarkPrint(MazeType &maze, PosType curpos) {
	maze.addr[curpos.r][curpos.c] = '@';
}
 
//若迷宫存在一条通路，则求出一条通路存放到栈中
status MazePath(MazeType &maze, PosType start, PosType end, SqStack &S) {
	PosType curpos;		//记录当前元素位置
	int curstep = 1, flag = 0;	//记录能通行的通道块在栈中的路径顺序
	SElemType e;		//记录可压住栈中的当前通道块的信息
	curpos = start;
	do {
		if (WhetherPass(maze, curpos)) {		//如果该路径块可通行
			FootPrint(maze, curpos);		//记录下通行过的痕迹
			e.ord = curstep;			//将栈中的顺序给e的ord属性
			e.seat.c = curpos.c;		//将该通道块的位置给e的curpos属性
			e.seat.r = curpos.r;
			e.di = 1;		//将初始方向设为向东(1)
			PushStack(S, e);		//将该可通的通道块压入栈
			if (curpos.r == end.r&&curpos.c == end.c) 	//如果遇到了出口则退出
				return TRUE;
			else {		//如果没有遇到出口
				curpos = NextPos(curpos, 1);		//那么寻找下一个位置
				curstep++;		//计数器加1
			}
		}
		else {		//如果该路径块不通
			if (!StackEmpty(S)) {		//如果栈不为空
				Pop(S, e);		//将栈顶元素出栈也就是退回上一个元素，将e返回出来判断是否再次进行方向的改变，也就是将栈顶元素进行悬挂操作
				while (e.di == 4 && !StackEmpty(S)) {		//当四个方向都不通并且栈b不为空时
					MarkPrint(maze, e.seat);		//记录该通道块不通
					Pop(S, e);
					//将栈顶元素出栈也就是退回上一个位置
				}
				if (e.di < 4) {		//当四个方向没有尝试完时
					e.di++;		//换一个方向
					PushStack(S, e);		//将换方向之后的位置压栈
					curpos = NextPos(e.seat, e.di);		//当前位置下移
				}
			}
		}
	} while (!StackEmpty(S));
	return FALSE;
}
 
//将标记路径信息输出到终端显示屏
void PrintMaze(MazeType &maze, PosType start, PosType end) {
	int i, j;
	printf("          ");		//10个空格
	for (i = 0; i <maze.c; i++) printf("%2d", i);
	printf("\n");
	for (i = 0; i < maze.r; i++) {
		if (i == start.r - 1) printf("entrance%2d", start.r - 1);
		else if (i == start.r)	printf("      ->%2d", start.r);
		else printf("%10d", i);
		for (j = 0; j < maze.c; j++) {
			printf("%2c", maze.addr[i][j]);
			if (i == end.r - 1 && j == end.c) printf(" exit");
			else if (i == end.r&&j == end.c) printf("<-");
		}
		printf("\n");
	}
	return;
}
 
//输出栈中的路径
void PrintStack(SqStack S) {
	int flag = 0;
	printf("迷宫中的一条通路如下:\n");
	do {
		S.top--;		//将栈顶指针指向想要输出的栈顶元素
		if (flag % 5 == 0) printf("\n");
		switch (S.top->data.di) {
		case 1:
			printf("(%d,%d)向东->", S.top->data.seat.r, S.top->data.seat.c);
			flag++; break;
		case 2:
			printf("(%d,%d)向南->", S.top->data.seat.r, S.top->data.seat.c);
			flag++; break;
		case 3:
			printf("(%d,%d)向西->", S.top->data.seat.r, S.top->data.seat.c);
			flag++; break;
		case 4:
			printf("(%d,%d)向北->", S.top->data.seat.r, S.top->data.seat.c);
			flag++; break;
		}
	} while (S.base != S.top);
	printf("结束\n");
	return;
}
//---------迷宫实现结束------------
