#include <stdio.h>
//#include <conio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <time.h>             /*Tetris 12.07 QZ*/

void gotoxy(int x, int y)	/*鼠标移到(x,y)处*/
{
	COORD coord={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void loado(int a[],int b[],int o[][5])	/*方块装载*/
{
    int X=o[0][4],Y=o[1][4],x=o[2][4],y=o[3][4],i=0;
    for(i=0;i<21;i++) b[i]=0;
    for(i=0;i<4;i++)
        b[i+Y]=((o[y][x]>>(12-4*i))&15)<<X;
}

int crash(int a[],int b[],int o[][5])	/*碰撞检测*/
{
    int i;
	loado(a,b,o);
    for(i=0,o[5][4]=0;i<21;i++) o[5][4]+=(a[i]&b[i]);
        return o[5][4];
}

void n(int a[],int b[],int o[][5])	/*数据初始化*/
{	
	int i;
	for(i=0,a[20]=4095;i<20;i++) a[i]=2049;
	o[0][4]=5,o[1][4]=0,o[2][4]=rand()%4,o[3][4]=rand()%7;
	loado(a,b,o);
}

void tv(int a[],int b[])	/*显示函数*/
{
	int i,j;
	for(i=4;i<20;i++)
	{
		gotoxy(0,i-4);
		for (j=10; j>0; j--)
		{
			if(((a[i]|b[i])>>j)&1) printf("■");
			else printf("  ");
		}
	}
}

void dir(int a[],int b[],int o[][5])	/*方块刷新*/
{
	int i,j;
	for (i=0;i<20;i++) a[i]=a[i]|b[i];
	for (j=19;j>0;j--)
	if(a[j]==4095) for(i=j;i>0;i--) a[i]=a[i-1];
	tv(a,b);
	o[0][4]=5,o[1][4]=0,o[2][4]=rand()%4,o[3][4]=rand()%7;
	loado(a,b,o);
}

void dokey(int a[],int b[],int o[][5])	/*按键执行*/
{
	int i,k[4];
	for (i=0;i<4;i++) k[i]=o[i][4];
	if((o[4][4]=='s')||!o[6][4]) o[1][4]++,o[4][4]='s';
	else if(o[4][4]=='d') o[0][4]--;
	else if(o[4][4]==13) o[2][4]=(o[2][4]+1)%4;
	else if(o[4][4]=='a') o[0][4]++;
	if(crash(a,b,o)) for(i=0;i<4;i++) o[i][4]=k[i];
	loado(a,b,o);
	tv(a,b);
	if((o[4][4]=='s')&&o[5][4]) dir(a,b,o);
	o[4][4]=-1;
	tv(a,b);
}

int main()
{
	int a[21]={0}, b[21]={0},
	o[7][5]={39  , 562, 114 , 305,0,          /*绘制方块*/
		 275 , 71 , 802 , 113,0,      
		 547 , 116, 785 , 23 ,0,     
	 	 4369, 15 , 4369, 15 ,0,     
		 306 , 99 , 306 , 99 ,0,	
		 561 , 54 , 561 , 54 ,0,
		 51  , 51 , 51  , 51 ,0 };	
	srand(time(0));	/*数据初始*/
	n(a,b,o);
	loado(a,b,o);
    while(a[3]==2049)
	{
		if(kbhit()) o[4][4]=getch();	/*如果有按键，获取*/		
		o[6][4]=(o[6][4]+1)%16;	/*计时器*/ 
		if(!o[6][4]||(o[4][4]+1)) dokey(a,b,o);	/*按键执行*/
		Sleep(50);
	}
}
