#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#define MAX 100
HWND hwnd = NULL;

typedef struct point
{
	int x;
	int y;
}MYPOINT;

//蛇的属性
struct mySnake
{
	int num;     
	MYPOINT xy[MAX];
	char position;
}snake;

//食物的属性
struct myFood
{
	MYPOINT fdxy;
	int flag;
	int eatgrade;
}food;
//枚举类型
enum movPostion
{
	right = 72,
	left = 75,
	down = 77,
	up = 80
};
//蛇的过程
void initSnake();	//初始化蛇
void drawSnake();   //画蛇
void moveSnake();   //移动蛇
void keyDown();     //控制蛇移动
//食物的过程
void initFood();	//初始化食物
void drawFood();    //画食物

//3.逻辑分析
//吃食物
void eatFood();		//吃食物
//蛇什么时候GameOver
int gameOver(); 	//撞墙+撞自己
void gamePause();	//暂停
void showScore();	//显示分数


int main()
{
	srand((unsigned int)time(NULL));
	hwnd = initgraph(640, 480);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	while (1)
	{
		cleardevice();
		if(food.flag==0)
			initFood();
		drawFood();
		drawSnake();
		showScore();

		if (gameOver())
		{
			break;
		}
		eatFood();
		moveSnake();
		while (_kbhit())	//有按键才做处理
		{
			gamePause();
			keyDown();
		}
		
		Sleep(100);
	}

	getchar();
	closegraph();
	system("pause");
	return 0;
}

void initSnake()	//初始化蛇
{
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;
	snake.position = right;

	food.flag = 0;

}
void drawSnake()    //画蛇
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake()    //移动蛇
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch (snake.position)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:break;
	}

}
void keyDown()      //控制蛇移动
{
	char ch = '0';
	ch = _getch();
	switch (ch)
	{
	case right:
		if (snake.position != down)
			snake.position = up;
		break;
	case left:
		if (snake.position != right)
			snake.position = left;
		break;
	case down:
		if (snake.position != left)
			snake.position = right;
		break;
	case up:
		if (snake.position != up)
			snake.position = down;
		break;
	default:
		break;
	}
}
void initFood() 	//初始化食物
{
	food.fdxy.x = rand() % 65*10;
	food.fdxy.y = rand() % 48*10;
	food.flag = 1;

	//食物不能与蛇的坐标重复
	for (int i=0;i<snake.num;i++)
	{
		if ((food.fdxy.x == snake.xy[i].x&&food.fdxy.y == snake.xy[i].y)||
			food.fdxy.x==650|| food.fdxy.y==480)
		{
			food.fdxy.x = rand() % 65*10;
			food.fdxy.y = rand() % 48*10;
		}
	}
}
void drawFood()     //画食物
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand()% 255, rand()% 255, rand()% 255));
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}
void eatFood() 		//吃食物
{
	if (food.fdxy.x == snake.xy[0].x&&food.fdxy.y == snake.xy[0].y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
int gameOver() 	//撞墙+撞自己
{
	//撞墙
	if (snake.xy[0].x < 0 || snake.xy[0].y < 0 ||
		snake.xy[0].x>640-10 || snake.xy[0].y>480-10)
	{
		outtextxy(320, 240, "你撞墙了！GameOver");
		MessageBox(hwnd, "游戏结束", "撞墙了！", 0);
		return 1;
	}
	//撞自己
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x&&snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(320, 240, "你撞自己了！GameOver");
			MessageBox(hwnd, "游戏结束", "撞自己了！", 0);
			return 1;
		}
	}
	return 0;
}
void gamePause() 	//暂停
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}
void showScore() 	//显示分数
{
	char grade[100] = { "" };
	sprintf(grade, "分数：%d", food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(570, 20, grade);
	
}
