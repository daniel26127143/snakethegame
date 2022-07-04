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
	int size;//大小
	int dir;//方向
	int speed;//速度
	POINT xyz [500] ;//座標
}snake;

//物品結構
struct item
{
	int x;
	int y;
	int radius; //item半徑
	bool check;//判斷是否碰到
	DWORD color;//顏色
}food,wall;


//snake方向
enum DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

//初始化snake
void GameInit()
{
	//設定音效
	mciSendString("open ./src/KevinMacLeod.mp3 alias gameBGM", 0, 0, 0);
	mciSendString("open ./src/deadsfx.mp3 alias deadsfx", 0, 0, 0);
	mciSendString("open ./src/coin/coin1.wav alias c1", 0, 0, 0);
	mciSendString("open ./src/coin/coin2.wav alias c2", 0, 0, 0);
	mciSendString("open ./src/coin/coin3.wav alias c3", 0, 0, 0);
	mciSendString("open ./src/coin/coin4.wav alias c4", 0, 0, 0);
	mciSendString("open ./src/coin/coin5.wav alias c5", 0, 0, 0);
	mciSendString("play gameBGM repeat", 0, 0, 0);
	//時間亂數
	srand(time(0));
	//圖形化
	initgraph(640, 480,SHOWCONSOLE);
	//初始化snake
	snake.size = 3;
	snake.dir = RIGHT;
	snake.speed = 10;

	//設定snake初始位置
	for (int i = 0; i <3; i++)
	{
		snake.xyz[snake.size-i-1].x = 10 * i+20;
		snake.xyz[snake.size-i-1].y = 10;
	}
	//設定food初始化
	food.x = rand() % 55*10+10;
	food.y = rand() % 39*10+10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.radius = 5;
	food.check = true;
	
	//設定wall初始化
	wall.x = rand() % 55 * 10 + 10;
	wall.y = rand() % 39 * 10 + 10;
	wall.radius = 5;
	wall.check = true;

}
//food重生
void reFood() 
{
	food.x = rand() % 55 * 10 + 10;
	food.y = rand() % 39 * 10 + 10;
	food.radius = 5;
	food.check = true;
}
//製作圍牆
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
//遊戲背景設定
void GameSet()
{
	//防止閃爍
	BeginBatchDraw();
	
	//設定BG顏色
	setbkcolor(BLACK);
	cleardevice();
	//設定蛇的顏色 
	setfillcolor(GREEN);
	for (int i = snake.size - 1; i>=0 ; i--)
	{
		solidcircle(snake.xyz[i].x, snake.xyz[i].y, 5);
	}
	//畫一個food
	setfillcolor(WHITE);
	if (food.check)
	{
		solidcircle(food.x, food.y, food.radius);
	}
	//畫一個wall
	setfillcolor(RED);
	if (wall.check)
	{
		//用x和y做wall
		solidrectangle(wall.x - 5,0, wall.x + 5, 480);
		solidrectangle(0, wall.y-5, 640, wall.y+5);
	}
	EndBatchDraw();
}
//snake移動
void SnakeMove() 
{
	for (int i = snake.size-1; i >0 ; i--)
	{
		//變成下家的位置
		snake.xyz[i]= snake.xyz[i-1];
		
	}
		//判斷上下左右有無超過邊界
		switch (snake.dir)
		{
		case UP:
			snake.xyz[0].y-=10;
			if (snake.xyz[0].y==0)//超過邊界tp
			{
				snake.xyz[0].y = 480;
			}
			break;
		case RIGHT:
			if (snake.xyz[0].x ==640)//超過邊界tp
			{
				snake.xyz[0].x = 0;
			}
			snake.xyz[0].x+=10;
			break;
		case DOWN:
			if (snake.xyz[0].y == 480)//超過邊界tp
			{
				snake.xyz[0].y = 0;
			}
			snake.xyz[0].y+=10;
			break;
		case LEFT:
			if (snake.xyz[0].x == 0)//超過邊界tp
			{
				snake.xyz[0].x = 640;
			}
			snake.xyz[0].x-=10;
			break;
		}
		
	
	
}

//使用鍵盤操作
void KeyControl()
{
	if (_kbhit())//檢測有無輸入
	{
		//上下左右
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
		case 27://ESC暫停
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
			//重新makewall
			MakeWall();
			//繼續撥放BGM
			mciSendString("resume gameBGM ", 0, 0, 0);
			break;
		}
	}
	
}
//死亡
void GG() 
{
	//暫停播放BGM
	mciSendString("pause gameBGM ", 0, 0, 0);
	//播放死亡音效
	mciSendString("close deadsfx", 0, 0, 0);
	mciSendString("open ./src/deadsfx.mp3 alias deadsfx", 0, 0, 0);
	mciSendString("play deadsfx", 0, 0, 0);
	//R鍵重生 
	while (_getch() == 'r' || _getch() == 'R')
	{
		//snake初始化
		for (int i = 0; i < 3; i++)
		{
			snake.xyz[snake.size - i - 1].x = 10 * i + 20;
			snake.xyz[snake.size - i - 1].y = 10;
		}
		snake.size = 3;
		snake.dir = RIGHT;
		snake.speed = 10;
		//重新makewall
		MakeWall();
		//繼續撥放BGM
		mciSendString("resume gameBGM ", 0, 0, 0);
		break;
	}
}
//吃獎勵
void EatFood() 
{
	//判斷有無碰到
	if (snake.xyz[0].x == food.x && snake.xyz[0].y == food.y)
	{
		//隨機挑選拾取金幣音效
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
		//重整food
		reFood();
		//snake大小變大
		snake.size++;
	}
}

//撞牆GG
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
	//設定起始時間和現在時間
	double st=clock(), ed,set=clock();
	GameInit();
	GameSet();
	
	//迴圈
	while (true)
	{
		ed = clock();
		SnakeMove();
		GameSet();
		EatFood();
		WallAttack();
		//每7秒鐘wall重生
		while (((ed - set) / (double)CLOCKS_PER_SEC) > 7)
		{
			MakeWall();
			//重設時間
			set += (double)7000;
		}
		//設定ed為現在的時間
		for (int i = 0; i < 30; i++)
		{
			KeyControl();
			Sleep(1);
		}
		
	}
	return 0;
}