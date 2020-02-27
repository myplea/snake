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

//�ߵ�����
struct mySnake
{
	int num;     
	MYPOINT xy[MAX];
	char position;
}snake;

//ʳ�������
struct myFood
{
	MYPOINT fdxy;
	int flag;
	int eatgrade;
}food;
//ö������
enum movPostion
{
	right = 72,
	left = 75,
	down = 77,
	up = 80
};
//�ߵĹ���
void initSnake();	//��ʼ����
void drawSnake();   //����
void moveSnake();   //�ƶ���
void keyDown();     //�������ƶ�
//ʳ��Ĺ���
void initFood();	//��ʼ��ʳ��
void drawFood();    //��ʳ��

//3.�߼�����
//��ʳ��
void eatFood();		//��ʳ��
//��ʲôʱ��GameOver
int gameOver(); 	//ײǽ+ײ�Լ�
void gamePause();	//��ͣ
void showScore();	//��ʾ����


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
		while (_kbhit())	//�а�����������
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

void initSnake()	//��ʼ����
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
void drawSnake()    //����
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake()    //�ƶ���
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
void keyDown()      //�������ƶ�
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
void initFood() 	//��ʼ��ʳ��
{
	food.fdxy.x = rand() % 65*10;
	food.fdxy.y = rand() % 48*10;
	food.flag = 1;

	//ʳ�ﲻ�����ߵ������ظ�
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
void drawFood()     //��ʳ��
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand()% 255, rand()% 255, rand()% 255));
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}
void eatFood() 		//��ʳ��
{
	if (food.fdxy.x == snake.xy[0].x&&food.fdxy.y == snake.xy[0].y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
int gameOver() 	//ײǽ+ײ�Լ�
{
	//ײǽ
	if (snake.xy[0].x < 0 || snake.xy[0].y < 0 ||
		snake.xy[0].x>640-10 || snake.xy[0].y>480-10)
	{
		outtextxy(320, 240, "��ײǽ�ˣ�GameOver");
		MessageBox(hwnd, "��Ϸ����", "ײǽ�ˣ�", 0);
		return 1;
	}
	//ײ�Լ�
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x&&snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(320, 240, "��ײ�Լ��ˣ�GameOver");
			MessageBox(hwnd, "��Ϸ����", "ײ�Լ��ˣ�", 0);
			return 1;
		}
	}
	return 0;
}
void gamePause() 	//��ͣ
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}
void showScore() 	//��ʾ����
{
	char grade[100] = { "" };
	sprintf(grade, "������%d", food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(570, 20, grade);
	
}
