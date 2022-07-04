#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment (lib,"winmm.lib")

using namespace std;
#define SNAKE_NUM 500;
//struct
struct Snake  
{
	int size;//�j�p
	int dir;//��V
	int speed;//�t��
	POINT xyz [500] ;//�y��
}snake;

//���~���c
struct item
{
	int x;
	int y;
	int radius; //item�b�|
	bool check;//�P�_�O�_�I��
	DWORD color;//�C��
}food,wall;


//snake��V
enum DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

//��l��snake
void GameInit()
{
	//�]�w����
	mciSendString("open ./src/KevinMacLeod.mp3 alias gameBGM", 0, 0, 0);
	mciSendString("open ./src/deadsfx.mp3 alias deadsfx", 0, 0, 0);
	mciSendString("open ./src/coin/coin1.wav alias c1", 0, 0, 0);
	mciSendString("open ./src/coin/coin2.wav alias c2", 0, 0, 0);
	mciSendString("open ./src/coin/coin3.wav alias c3", 0, 0, 0);
	mciSendString("open ./src/coin/coin4.wav alias c4", 0, 0, 0);
	mciSendString("open ./src/coin/coin5.wav alias c5", 0, 0, 0);
	mciSendString("play gameBGM repeat", 0, 0, 0);
	//�ɶ��ü�
	srand(time(0));
	//�ϧΤ�
	initgraph(640, 480,SHOWCONSOLE);
	//��l��snake
	snake.size = 3;
	snake.dir = RIGHT;
	snake.speed = 10;

	//�]�wsnake��l��m
	for (int i = 0; i <3; i++)
	{
		snake.xyz[snake.size-i-1].x = 10 * i+20;
		snake.xyz[snake.size-i-1].y = 10;
	}
	//�]�wfood��l��
	food.x = rand() % 55*10+10;
	food.y = rand() % 39*10+10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.radius = 5;
	food.check = true;
	
	//�]�wwall��l��
	wall.x = rand() % 55 * 10 + 10;
	wall.y = rand() % 39 * 10 + 10;
	wall.radius = 5;
	wall.check = true;

}
//food����
void reFood() 
{
	food.x = rand() % 55 * 10 + 10;
	food.y = rand() % 39 * 10 + 10;
	food.radius = 5;
	food.check = true;
}
//�s�@����
void MakeWall() {
	int xx = rand() % 55 * 10 + 10;
	int yy = rand() % 39 * 10 + 10;	
	while (xx==food.x)
	{
		xx = rand() % 55 * 10 + 10;
	}
	wall.x = xx;
	while (yy == food.y)
	{
		yy = rand() % 39 * 10 + 10;
	}
	wall.y = yy;
}
//�C���I���]�w
void GameSet()
{
	//����{�{
	BeginBatchDraw();
	
	//�]�wBG�C��
	setbkcolor(BLACK);
	cleardevice();
	//�]�w�D���C�� 
	setfillcolor(GREEN);
	for (int i = snake.size - 1; i>=0 ; i--)
	{
		solidcircle(snake.xyz[i].x, snake.xyz[i].y, 5);
	}
	//�e�@��food
	setfillcolor(WHITE);
	if (food.check)
	{
		solidcircle(food.x, food.y, food.radius);
	}
	//�e�@��wall
	setfillcolor(RED);
	if (wall.check)
	{
		//��x�My��wall
		solidrectangle(wall.x - 5,0, wall.x + 5, 480);
		solidrectangle(0, wall.y-5, 640, wall.y+5);
	}
	EndBatchDraw();
}
//snake����
void SnakeMove() 
{
	for (int i = snake.size-1; i >0 ; i--)
	{
		//�ܦ��U�a����m
		snake.xyz[i]= snake.xyz[i-1];
		
	}
		//�P�_�W�U���k���L�W�L���
		switch (snake.dir)
		{
		case UP:
			snake.xyz[0].y-=10;
			if (snake.xyz[0].y==0)//�W�L���tp
			{
				snake.xyz[0].y = 480;
			}
			break;
		case RIGHT:
			if (snake.xyz[0].x ==640)//�W�L���tp
			{
				snake.xyz[0].x = 0;
			}
			snake.xyz[0].x+=10;
			break;
		case DOWN:
			if (snake.xyz[0].y == 480)//�W�L���tp
			{
				snake.xyz[0].y = 0;
			}
			snake.xyz[0].y+=10;
			break;
		case LEFT:
			if (snake.xyz[0].x == 0)//�W�L���tp
			{
				snake.xyz[0].x = 640;
			}
			snake.xyz[0].x-=10;
			break;
		}
		
	
	
}

//�ϥ���L�ާ@
void KeyControl()
{
	if (_kbhit())//�˴����L��J
	{
		//�W�U���k
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			snake.dir = UP;
			break;
		case 'd':
		case 'D':
		case 77:
				snake.dir = RIGHT;
			break;
		case 's':
		case 'S':
		case 80:
				snake.dir = DOWN;
			break;
		case 'a':
		case 'A':
		case 75:
			snake.dir = LEFT;
			break;
		case 27://ESC�Ȱ�
			mciSendString("pause gameBGM ", 0, 0, 0);
			while (_getch() != 27)
			{

			}
			mciSendString("resume gameBGM ", 0, 0, 0);
			break;
		case 'r':
		case 'R':
			for (int i = 0; i < 3; i++)
			{
				snake.xyz[snake.size - i - 1].x = 10 * i + 20;
				snake.xyz[snake.size - i - 1].y = 10;
			}
			snake.size = 3;
			snake.dir = RIGHT;
			snake.speed = 10;
			//���smakewall
			MakeWall();
			//�~�򼷩�BGM
			mciSendString("resume gameBGM ", 0, 0, 0);
			break;
		}
	}
	
}
//���`
void GG() 
{
	//�Ȱ�����BGM
	mciSendString("pause gameBGM ", 0, 0, 0);
	//���񦺤`����
	mciSendString("close deadsfx", 0, 0, 0);
	mciSendString("open ./src/deadsfx.mp3 alias deadsfx", 0, 0, 0);
	mciSendString("play deadsfx", 0, 0, 0);
	//R�䭫�� 
	while (_getch() == 'r' || _getch() == 'R')
	{
		//snake��l��
		for (int i = 0; i < 3; i++)
		{
			snake.xyz[snake.size - i - 1].x = 10 * i + 20;
			snake.xyz[snake.size - i - 1].y = 10;
		}
		snake.size = 3;
		snake.dir = RIGHT;
		snake.speed = 10;
		//���smakewall
		MakeWall();
		//�~�򼷩�BGM
		mciSendString("resume gameBGM ", 0, 0, 0);
		break;
	}
}
//�Y���y
void EatFood() 
{
	//�P�_���L�I��
	if (snake.xyz[0].x == food.x && snake.xyz[0].y == food.y)
	{
		//�H���D��B����������
		int rd = rand() % 5 + 1;
		switch (rd)
		{
		case 1:
			mciSendString("close c1", 0, 0, 0);
			mciSendString("open ./src/coin/coin1.wav alias c1", 0, 0, 0);
			mciSendString("play c1", 0, 0, 0);
			break;
		case 2:
			mciSendString("close c2", 0, 0, 0);
			mciSendString("open ./src/coin/coin2.wav alias c2", 0, 0, 0);
			mciSendString("play c2", 0, 0, 0);
			break;
		case 3:
			mciSendString("close c3", 0, 0, 0);
			mciSendString("open ./src/coin/coin3.wav alias c3", 0, 0, 0);
			mciSendString("play c3", 0, 0, 0);
			break;
		case 4:
			mciSendString("close c4", 0, 0, 0);
			mciSendString("open ./src/coin/coin4.wav alias c4", 0, 0, 0);
			mciSendString("play c4", 0, 0, 0);
			break;
		case 5:
			mciSendString("close c5", 0, 0, 0);
			mciSendString("open ./src/coin/coin5.wav alias c5", 0, 0, 0);
			mciSendString("play c5", 0, 0, 0);
			break;
		}
		//����food
		reFood();
		//snake�j�p�ܤj
		snake.size++;
	}
}

//����GG
void WallAttack() 
{
	if (snake.xyz[0].x == wall.x || snake.xyz[0].y == wall.y)
	{
		GG();
	}
}
//Main
int main()
{	
	//�]�w�_�l�ɶ��M�{�b�ɶ�
	double st=clock(), ed,set=clock();
	GameInit();
	GameSet();
	
	//�j��
	while (true)
	{
		ed = clock();
		SnakeMove();
		GameSet();
		EatFood();
		WallAttack();
		//�C7����wall����
		while (((ed - set) / (double)CLOCKS_PER_SEC) > 7)
		{
			MakeWall();
			//���]�ɶ�
			set += (double)7000;
		}
		//�]�wed���{�b���ɶ�
		for (int i = 0; i < 30; i++)
		{
			KeyControl();
			Sleep(1);
		}
		
	}
	return 0;
}