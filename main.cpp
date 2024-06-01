#pragma warning(disable:4996) // Ϊ�˷�ֹ����
#include<iostream>            //���������������ͺ���
#include<graphics.h>          //����easyxͷ�ļ�
#include<conio.h>             //ͨ������̨������������
#include<time.h>              //��ȡʱ�������ڣ���ʱ�����������ݲ��������ʽ��
#include<queue>               //��������������
#include<Mmsystem.h>          //����������Ҫ��ͷ�ļ�
#include"tool.h"              //ʵ��͸����ͼͷ�ļ�

#pragma comment(lib,"winmm.lib") //���ؾ�̬�⣬���߱�����������winmm.lib���ļ�

using namespace std;             //����׼������б�ʶ����

#define pointWidth 30            //ÿ������Ŀ��

void drawButton(struct button* pB);  //���ư�ťͼ
int item[10][10] = { 0 };            //�����ά����
//�������ɫ��colors[0]�Ǻ�ɫ������ɫ��������ô��޷���(�ѱ�����)
int colors[] = { BLACK,RED,YELLOW,BLUE,GREEN,RGB(128,0,128) };
int score;
int ss = 1;
int cnt;

IMAGE startbkimage;
//����ṹ���   �����Ϊ��Ϸ��ͼ�ϵĵ㣬�������ص�
struct button {
	int x;    //��ĺ�����        
	int y;    //���������
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

//Ϊ���Ƕ�ά�������Ϸ�����ϵ�С�����Ӧ��������һ��point�ṹ��
typedef struct point {
	int x; //��ĺ�����
	int y; //���������
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
	struct button* pB1 = createButton(150, 120, 190, 50, RED, "��ʼ��Ϸ");
	struct button* pB2 = createButton(150, 190, 190, 50, YELLOW, "��������");
	struct button* pB3 = createButton(150, 260, 190, 50, GREEN, "��ͣ����");
	//putimage(0, 0, &startbkimage);

	drawButton(pB1);
	drawButton(pB2);
	drawButton(pB3);
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (pB1->x <= m.x && m.x <= pB1->x + pB1->widih && pB1->y <= m.y && m.y <= pB1->y + pB1->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {

				//���ſ�ʼ����
				mciSendString("open ./assets/readygo.mp3 alias GO", 0, 0, 0);  //aliasȡ����
				mciSendString("play GO ", 0, 0, 0);
				mciSendString("setaudio GO volume to 80", NULL, 0, NULL);      //��������

				break;
			}
		}
		if (pB2->x <= m.x && m.x <= pB2->x + pB2->widih && pB2->y <= m.y && m.y <= pB2->y + pB2->height) {
			if (m.uMsg == WM_LBUTTONDOWN) {

				//���ű�������
				mciSendString("play ./assets/bgm.mp3 repeat", 0, 0, 0);

			}
		}
		if (pB3->x <= m.x && m.x <= pB3->x + pB3->widih && pB3->y <= m.y && m.y <= pB3->y + pB3->height) {
			if (m.uMsg == WM_LBUTTONDOWN)

				//�رձ�������
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

//���·�����cntΪÿ�������ĸ���
void updateScore(int cnt) {
	score += (cnt * cnt * 3);
	_TCHAR S[20];
	sprintf(S, "%d", score);
	// ���ñ�����ɫΪ��ɫ������
	BeginBatchDraw();  //˫����
	cleardevice();

	IMAGE bjt;
	loadimage(&bjt, "./assets/bjt.jpg", getwidth(), getheight());
	putimage(0, 0, &bjt);

	settextcolor(WHITE);  //����������ɫ
	settextstyle(30, 0, _T("��������"));  //�����ֺź�����
	outtextxy(230, 450, S);
	settextcolor(WHITE);  //����������ɫ
	settextstyle(30, 0, _T("��������"));  //�����ֺź�����
	outtextxy(80, 450, _T("��Ϸ�÷�"));
	EndBatchDraw();  //����˫����

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
	//int cnt;  //���ڼ�¼ÿ����������ĸ������ɴ˼���÷�
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

	//����������һ��

	updateScore(0);
	settextcolor(WHITE);
	struct button* pB4 = createButton(150, 120, 190, 50, YELLOW, "������Ϸ");
	struct button* pB5 = createButton(150, 250, 190, 50, YELLOW, "����һ��");
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
	//���ű�������
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
	settextstyle(35, 0, "����");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(pB->x, pB->y, pB->x + pB->widih, pB->y + pB->height);
	outtextxy(pB->x + 20, pB->y + 10, pB->pstr);
}
