#include <iostream>
#include "mylib.h"
using namespace std;
#define TOP 2
#define BOT 29
#define RIGHT 43
#define LEFT 3
#define WT 1
#define WB 30
#define WL 2
#define WR 50
int SL = 4;
#define MAX 100

void drawWallTop()
{
	int x = WL , y = WT ;
	while (x <= WR)
	{
		gotoXY(x, y);
		cout << "-";
		x++;
	}
}
void drawWallBot()
{
	int x = WL, y = WB;
	while (x <= WR)
	{
		gotoXY(x, y);
		cout << "-";
		x++;
	}
}
void drawWallLeft()
{
	int x = WL, y = WT;
	while (y <= WB)
	{
		gotoXY(x, y);
		cout << "|";
		y++;
	}
}

void drawWallRight()
{
	int x = WR, y = WT;
	while (y <= WB)
	{
		gotoXY(x, y);
		cout << "|";
		y++;
	}
}

void drawWall()
{
	drawWallRight();
	drawWallLeft();
	drawWallBot();
	drawWallTop();
}
void drawSnake(int toadox[], int toadoy[])
{
	for (int i = 0;i < SL ;i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		if (i == 0)
		{
			cout << "0";
		}
		else
			cout<<"o";
	}
}
void initSnake(int toadox[], int toadoy[])
{
	int x = 30 , y = 13;
	for (int i = 0;i < SL;i++)
	{
		toadox[i] = x;
		toadoy[i] = y;
		x--;
	}
}
void removeOneSpace(int toadox[], int toadoy[])
{
	for (int i = 0;i < SL ;i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		cout << " ";
	}
}
void add(int a[],int x)
{
	for (int i = SL;i > 0;i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	SL++;
}
void removeOneElement(int a[],int pos)
{
	for (int i = pos ;i < SL ;i++)
	{
		a[i] = a[i + 1];
	}
	SL--;
}


bool checkWall(int x0,int y0)
{
	//ran cham tuong tren
	if (y0 == WT && (x0 >= WL && x0 <= WR))
	{
		return true;//gameover
	}
	//ran cham tuong duoi
	else if (y0 == WB && (x0 >= WL && x0 <= WR))
	{
		return true;//gameover
	}
	//ran cham tuong phai
	else if (x0 == WR && (y0 >= WT && y0 <= WB))
	{
		return true;//gameover
	}
	//ran cham tuong trai
	else if (x0 == WL && (y0 >= WT && y0 <= WB))
	{
		return true;//gameover
	}
	return false;
}
bool checkTailSnake(int toadox[],int toadoy[])
{
	for (int i = 1;i < SL ;i++)
	{
		if ((toadox[0] == toadox[i]) && (toadoy[0] == toadoy[i]))
		{
			return true;//gameover
		}
	}
	return false;
}
bool checkSnake(int toadox[],int toadoy[])
{
	bool kt1 = checkTailSnake(toadox, toadoy);//gameover = true
	bool kt2 = checkWall(toadox[0], toadoy[0]);//gameover = false
	if (kt1 == true || kt2 == true)
	{
		return true;//gameover
	}
	return false;
}

bool checkSnakeOverWirte(int xqua, int yqua, int toadox[], int toadoy[])
{
	for (int i = 0;i < SL ;i++)
	{
		if ((xqua == toadox[i]) && (yqua == toadoy[i]))
		{
			return true;//ran de len qua
		}
	}
	return false;
}
bool checkSnakeEatFruit(int xqua, int yqua, int x0,int y0)
{
	if ((x0 == xqua) && (y0 == yqua))
	{
		return true;//ran an qua
	}
	return false;
}
void createTarget(int &xqua,int &yqua,int toadox[],int toadoy[])
{
	do
	{
		//11 <= xqua <= 99
		xqua = rand() % (45) + WL + 1;
		//2 <= yqua <= 25
		yqua = rand() % (25) + WT + 1;
	} while (checkSnakeOverWirte(xqua,yqua,toadox,toadoy)==true);
	int i = rand() % (15 - 1 + 1) + 1;
	SetColor(i);
	gotoXY(xqua, yqua);
	cout << "@";
	SetColor(7);//mau trang
}
void snakeHandler(int toadox[],int toadoy[],int x, int y,int &xqua,int &yqua)
{
	//b1: them toa do moi vao dau mang
	add(toadox, x);
	add(toadoy, y);
	//b2: xoa toa do cuoi mang
	if (checkSnakeEatFruit(xqua, yqua, toadox[0], toadoy[0]) == false)
	{
		removeOneElement(toadox, SL - 1);
		removeOneElement(toadoy, SL - 1);
	}
	else
	{
		createTarget(xqua, yqua, toadox, toadoy);
	}
	//b3: ve ran
	drawSnake(toadox, toadoy);
	Nocursortype();
}


int main()
{
	clearScreen();
	bool gameover = false;
	int toadox[MAX], toadoy[MAX];
	drawWall();
	initSnake(toadox, toadoy);
	int x = 29 , y = 13;// dinh hinh vi tri can di chuyen cho ran
	srand(time(NULL));
	int xqua = 0, yqua = 0;
	int check = 1;
	createTarget(xqua, yqua, toadox, toadoy);
	/*
		0 - Top -> BOT
		1 - Bot -> TOP
		3 - Left -> RIGHT
		2 - Right -> LEFT
	*/
	/**/
	while(!gameover)
	{
		//clearScreen(); /*clear screen*/
		removeOneSpace(toadox, toadoy);

		/*Ctrl*/
		/*get ky tu tu ban phim*/
		if(_kbhit()) 
		{
			char ch = _getch();
			if(ch == -32)
			{
				ch = _getch();
				if(ch==72 && check != 0)
				{
					check = 1;
				}
				else if (ch == 80 && check != 1)
				{
					check = 0;
				}
				else if(ch ==75 && check != 3)
				{
					check = 2;
				}
				else if(ch ==77 && check !=2)
				{
					check = 3;
				}
			}
			
		}
		/*move*/
		if(check == 0)
		{
			y++;
		}
		else if(check == 1)
		{
			y--;
		}
		else if(check == 2)
		{
			x--;
		}
		else if(check ==3)
		{
			x++;
		}

		/*check line*/
		snakeHandler(toadox, toadoy,x, y, xqua , yqua);
		Sleep(100);
		//cout<< checkTailSnake(toadox, toadoy);
		gameover = checkSnake(toadox, toadoy);
		Sleep(200);
	}
	return 0;
}