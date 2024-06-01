#pragma warning(disable:4996) // 为了防止报错
#include<iostream>            //输入和输出的类流和函数
#include<graphics.h>          //包含easyx头文件
#include<conio.h>             //通过控制台进行输入和输出
#include<time.h>              //获取时间与日期，对时间与日期数据操作及其格式化
#include<queue>               //队列容器适配器
#include<Mmsystem.h>          //播放音乐需要的头文件
#include"tool.h"              //实现透明贴图头文件

#pragma comment(lib,"winmm.lib") //加载静态库，告诉编译器，加载winmm.lib库文件

using namespace std;             //将标准库的所有标识引入

#define pointWidth 30            //每个方块的宽度

void drawButton(struct button* pB);  //绘制按钮图
int item[10][10] = { 0 };            //定义二维数组
//方块的颜色，colors[0]是黑色（背景色），代表该处无方块(已被消除)
int colors[] = { BLACK,RED,YELLOW,BLUE,GREEN,RGB(128,0,128) };
int score;
int ss = 1;
int cnt;

IMAGE startbkimage;
//定义结构体点   这个点为游戏地图上的点，并非像素点
struct button {
	int x;    //点的横坐标        
	int y;    //点的纵坐标
	int widih;
	int height;
	COLORREF color;
	char* pstr;
};
struct button* createButton(int x, int y, int widih, int height, COLORREF color, const char* pstr)
{
	struct button* pB = (struct button*)malloc(sizeof(struct button));
	pB->x = x;
	pB->y = y;
	pB->widih = widih;
	pB->height = height;
	pB->color = color;
	pB->pstr = (char*)malloc(strlen(pstr) + 1);
	strcpy(pB->pstr, pstr);
	return pB;
}

//为了是二维数组和游戏界面上的小方块对应起来定义一个point结构体
typedef struct point {
	int x; //点的横坐标
	int y; //点的纵坐标
	point() {};
	point(int _x, int _y) {
		x = _x;
		y = _y;
	}
}point;

void drawPoint(point p, int color = GREEN) {
	if (ss = 1) {
		setlinecolor(BLACK);
		setfillcolor(color);
		int sx, sy, ex, ey;
		sx = 80 + pointWidth * p.x + 1;
		sy = 120 + pointWidth * p.y + 1;
		ex = sx + pointWidth - 1;
		ey = sy + pointWidth - 1;
		fillroundrect(sx, sy, ex, ey, 5, 5);
	}
	else
	{

		setlinecolor(BLACK);
		setfillcolor(color);
		int sx, sy, ex, ey;
		sx = 80 + pointWidth * p.x + 1;
		sy = 120 + pointWidth * p.y + 1;
		ex = sx + pointWidth - 1;
		ey = sy + pointWidth - 1;
		fillroundrect(sx, sy, ex, ey, 5, 5);

	}
}

void initgame() {
	if (ss == 1) {
		score = 0;
		srand(unsigned(clock()));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				item[i][j] = rand() % 5 + 1;
			}
		}
	}
	else
	{
		score = 0;
		//cleardevice;
		srand(unsigned(clock()));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cleardevice();
				item[i][j] = rand() % 5 + 1;
			}
		}

	}
}


void startinterface() {
	putimage(0, 0, &startbkimage);
	struct button* pB1 = createButton(150, 120, 190, 50, RED, "开始游戏");
	struct button* pB2 = createButton(150, 190, 190, 50, YELLOW, "播放音乐");
	struct button* pB3 = createButton(150, 260, 190, 50, GREEN, "暂停音乐");
	//putimage(0, 0, &startbkimage);

	drawButton(pB1);
	drawButton(pB2);
	drawButton(pB3);
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (pB1->x <= m.x && m.x <= pB1->x + pB1->widih && pB1->y <= m.y && m.y <= pB1->y + pB1->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {

				//播放开始音乐
				mciSendString("open ./assets/readygo.mp3 alias GO", 0, 0, 0);  //alias取别名
				mciSendString("play GO ", 0, 0, 0);
				mciSendString("setaudio GO volume to 80", NULL, 0, NULL);      //调节音量

				break;
			}
		}
		if (pB2->x <= m.x && m.x <= pB2->x + pB2->widih && pB2->y <= m.y && m.y <= pB2->y + pB2->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {

				//播放背景音乐
				mciSendString("play ./assets/bgm.mp3 repeat", 0, 0, 0);

			}
		}
		if (pB3->x <= m.x && m.x <= pB3->x + pB3->widih && pB3->y <= m.y && m.y <= pB3->y + pB3->height) {
			if (m.uMsg == WM_LBUTTONDOWN)

				//关闭背景音乐
				mciSendString("close ./assets/bgm.mp3", 0, 0, 0);
		}
	}
}

void gameinterface() {
	if (ss == 1) {

		point p;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				p.x = i;
				p.y = j;
				drawPoint(p, colors[item[i][j]]);
			}
		}
	}
	else
	{
		mciSendString("play ./assets/bgm.mp3 repeat", 0, 0, 0);
		//cleardevice();
		point p;
		cleardevice();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				p.x = i;
				p.y = j;

				drawPoint(p, colors[item[i][j]]);
			}
		}

	}

}


bool ifCanPop(point p) {
	for (int i = p.x - 1; i <= p.x + 1; i++) {
		for (int j = p.y - 1; j <= p.y + 1; j++) {
			if (item[i][j] != 0 && item[i][j] == item[p.x][p.y] && ((p.x == i && p.y != j) || (p.x != i && p.y == j))) {
				return true;
			}
		}
	}
	return false;
}

//更新分数，cnt为每次消除的个数
void updateScore(int cnt) {
	score += (cnt * cnt * 3);
	_TCHAR S[20];
	sprintf(S, "%d", score);
	// 设置背景颜色为黑色并清屏
	BeginBatchDraw();  //双缓冲
	cleardevice();

	IMAGE bjt;
	loadimage(&bjt, "./assets/bjt.jpg", getwidth(), getheight());
	putimage(0, 0, &bjt);

	settextcolor(WHITE);  //设置字体颜色
	settextstyle(30, 0, _T("华文琥珀"));  //设置字号和字体
	outtextxy(230, 450, S);
	settextcolor(WHITE);  //设置字体颜色
	settextstyle(30, 0, _T("华文琥珀"));  //设置字号和字体
	outtextxy(80, 450, _T("游戏得分"));
	EndBatchDraw();  //结束双缓冲

}

bool isDeadlock()
{
	for (int i = 0; i < 10; i++) {
		for (int j = i % 2; j < 10; j += 2) {
			point p(i, j);
			if (ifCanPop(p)) return false;
		}
	}
	return true;
}
void game() {

	initgraph(480, 720);
	IMAGE bjt;
	loadimage(&bjt, "./assets/bjt.jpg", 480, 720);
	putimage(0, 0, &bjt);

	IMAGE yh, yh1, jiayou;
	loadimage(&yh, "./assets/yh.png");
	loadimage(&yh1, "./assets/yh1.png");
	loadimage(&jiayou, "./assets/jiayou.png");
	drawImg(350, 30, &yh);
	drawImg(20, 20, &yh1);
	drawImg(300, 450, &jiayou);

	startinterface();
	gameinterface();
}

void popstar(point p) {
	setfillcolor(TRANSPARENT);
	drawPoint(p, BLACK);
	item[p.x][p.y] = 0;
}

void left() {
	bool isBlankCol;
	int count = 0;
	for (int i = 0; i < 10; i++) {
		isBlankCol = true;
		for (int j = 0; j < 10; j++) {
			if (item[i][j] != 0)
				isBlankCol = false;
		}
		if (isBlankCol) { count++; }
		else {
			for (int jj = 0; jj < 10; jj++) {
				item[i - count][jj] = item[i][jj];
			}
		}
	}
	for (int k = 10 - count; k < 10; k++) {
		for (int j = 0; j < 10; j++) {
			item[k][j] = 0;
		}
	}
}
void down() {
	for (int i = 0; i < 10; i++) {
		int d = 0;
		for (int j = 9; j >= 0; j--) {
			if (item[i][j] == 0)
				d++;
			else
				item[i][j + d] = item[i][j];
		}
		for (int k = 0; k < d; k++) {
			item[i][k] = 0;
		}
	}
}

void play() {
	MOUSEMSG m;
	queue<point> a;
	point p;
	//int cnt;  //用于记录每次消除方块的个数，由此计算得分
	bool isGameOver = false;
	while (true) {
		m = GetMouseMsg();
		if (m.mkLButton && m.x >= 80 && m.x < (80 + pointWidth * 10) && m.y >= 120 && m.y <= (120 + pointWidth * 10)) {
			cnt = 0;
			p.x = (m.x - 80) / pointWidth;
			p.y = (m.y - 120) / pointWidth;
			if (item[p.x][p.y] != 0 && ifCanPop(p)) {
				a.push(p);
				while (!a.empty()) {
					point temp = a.front();
					for (int i = temp.x - 1; i <= (temp.x + 1) && i < 10; i++) {
						for (int j = temp.y - 1; j <= (temp.y + 1) && j < 10; j++) {
							if (item[i][j] != 0 && item[i][j] == item[temp.x][temp.y] && ((temp.x == i && temp.y != j) || (temp.x != i && temp.y == j))) {
								point pp(i, j);
								a.push(pp);
								mciSendString("play ./assets/towstars.mp3", NULL, NULL, NULL);
							}
						}
					}
					a.pop();
					popstar(temp);
					cnt++;
				}
				updateScore(cnt);
				down();
				left();
				gameinterface();
				if (isDeadlock()) {
					int leftStar = 0;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (item[i][j] != 0) leftStar++;
						}
					}
					if (leftStar <= 10)
						score = 2000 - leftStar * 5;
					isGameOver = true;
					//updateScore(0);
					//aa();
					break;



				}
			}


		}
	}
}
void aa() {
	cleardevice();
	mciSendString("close ./assets/bgm.mp3", 0, 0, 0);
	mciSendString("play ./assets/guoguan.mp3", 0, 0, 0);

	//结束或者下一局

	updateScore(0);
	settextcolor(WHITE);
	struct button* pB4 = createButton(150, 120, 190, 50, YELLOW, "结束游戏");
	struct button* pB5 = createButton(150, 250, 190, 50, YELLOW, "再来一局");
	drawButton(pB4);
	drawButton(pB5);


	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (pB5->x <= m.x && m.x <= pB5->x + pB5->widih && pB5->y <= m.y && m.y <= pB5->y + pB5->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				mciSendString("close ./assets/guoguan.mp3", 0, 0, 0);
				mciSendString("close ./assets/bjm.mp3", 0, 0, 0);


				ss++;
				initgame();
				updateScore(0);
				gameinterface();
				//startinterface();
				play();
				//cleardevice();
				updateScore(0);
				aa();
				break;
				//gameinterface();
			}
			//break;
		}
		if (pB4->x <= m.x && m.x <= pB4->x + pB4->widih && pB4->y <= m.y && m.y <= pB4->y + pB4->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				exit(0);
			}
		}
	}
}
int main() {
	initgame();
	//播放背景音乐
	mciSendString("play ./assets/bgm.mp3 repeat", 0, 0, 0);

	game();
	play();
	aa();
	gameinterface();
	_getch();
	closegraph();
}
void drawButton(struct button* pB) {
	setfillcolor(pB->color);
	settextstyle(35, 0, "隶书");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(pB->x, pB->y, pB->x + pB->widih, pB->y + pB->height);
	outtextxy(pB->x + 20, pB->y + 10, pB->pstr);
}
