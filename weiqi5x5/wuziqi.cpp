#ifdef _MSC_VER
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <iostream>
#include <windows.h>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include <math.h>
#include <graphics.h>
#include <string.h>
#include "rule.h"
using namespace cv;
int vord(int x, int y, int v);
int AI(int v);//AI思考函数
int lianziqingkuang[4];
int lianzibaxiang[8];
int lianzizhongduan[8];
int local_info;
MOUSEMSG chess_click;
int AIchessx,AIchessy,AIplot_x,AIplot_y;//可下棋子的坐标
int deal_x[120], deal_y[120];//已清点的棋子坐标
int offsetx, offsety;
CHESSMAN_CLASS wuziqi[CHESSBOARD_WIDTH][CHESSBOARD_HEIGHT];
int turn_black=1;
int mode=3;
int turn = 1;
char turn_str[3];
int main(int argc, char *argv[]) {
	ShowWindow(FindWindow("ConsoleWindowClass", argv[0]), 0);
	chessboard_init();

	memset(wuziqi, sizeof(wuziqi), 0);
	for (;;) {
		switch (mode) {
		case FREE_MODE:{
			chess_click=GetMouseMsg();
			if (chess_click.uMsg == WM_LBUTTONUP) {
				for (AIchessx = 454; AIchessx <= 986; AIchessx += 38) {
					for (AIchessy = 94; AIchessy <= 626; AIchessy += 38) {
						if (100>((chess_click.x - AIchessx)*(chess_click.x - AIchessx) + (chess_click.y - AIchessy)*(chess_click.y - AIchessy))) {
							AIplot_x = (AIchessx - 454) / 38;
							AIplot_y = (AIchessy - 94) / 38;
							if(wuziqi[AIplot_x][AIplot_y].chessman_state==0)
							{
								if (turn_black == 1) {
									wuziqi[AIplot_x][AIplot_y].chessman_state = 1;
									setfillcolor(BLACK);
									solidcircle(AIchessx, AIchessy, 15);
									if (vord(AIplot_x, AIplot_y,1)==0)
									{
										settextcolor(BLACK);
										setbkmode(TRANSPARENT);//设置字体背景透明
										settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
										outtextxy(454 + 7 * 38, 94 + 7 * 38, "黑五子连珠");
									}
									turn_black = 0;
								}
								else {
									wuziqi[AIplot_x][AIplot_y].chessman_state = 2;
									setfillcolor(WHITE);
									solidcircle(AIchessx, AIchessy, 15);
									if (vord(AIplot_x, AIplot_y,2)==0)
									{
										settextcolor(WHITE);
										setbkmode(TRANSPARENT);//设置字体背景透明
										settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
										outtextxy(454 + 7 * 38, 94 + 7 * 38, "白五子连珠");
									}
									turn_black = 1;
								}
							}
							AIchessx = 986;
							AIchessy = 626;
						}
					}
				}
			}
			else {

			}
		}break;
		case AI_MODE_BLACK: {
			chess_click = GetMouseMsg();
			if (chess_click.uMsg == WM_LBUTTONUP) {
				for (AIchessx = 454; AIchessx <= 986; AIchessx += 38) {
					for (AIchessy = 94; AIchessy <= 626; AIchessy += 38) {
						if (100 > ((chess_click.x - AIchessx)*(chess_click.x - AIchessx) + (chess_click.y - AIchessy)*(chess_click.y - AIchessy))) {
							AIplot_x = (AIchessx - 454) / 38;
							AIplot_y = (AIchessy - 94) / 38;
							if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
							{
								wuziqi[AIplot_x][AIplot_y].chessman_state = 1;
								setfillcolor(BLACK);
								solidcircle(AIchessx, AIchessy, 15);
								if (vord(AIplot_x, AIplot_y, 1)==0)
								{
									settextcolor(BLACK);
									setbkmode(TRANSPARENT);//设置字体背景透明
									settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
									outtextxy(454 + 7 * 38, 94 + 7 * 38, "黑五子连珠");
								}
								local_info = AI(2);
								AIplot_x = local_info / 100;
								AIplot_y = local_info % 100;
								if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
								{
									wuziqi[AIplot_x][AIplot_y].chessman_state = 2;
									setfillcolor(WHITE);
									AIchessx = AIplot_x * 38 + 454;
									AIchessy = AIplot_y * 38 + 94;
									solidcircle(AIchessx, AIchessy, 15);
									if (vord(AIplot_x, AIplot_y, 2) == 0)
									{
										settextcolor(BLACK);
										setbkmode(TRANSPARENT);//设置字体背景透明
										settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
										outtextxy(454 + 7 * 38, 94 + 7 * 38, "白五子连珠");
									}
								}
							}
							AIchessx = 986;
							AIchessy = 626;
						}
					}
				}
			}
			else {

			}
		}break;
		case AI_MODE_WHITE: {
			chess_click = GetMouseMsg();
			if (wuziqi[7][7].chessman_state != 1) {
				wuziqi[7][7].chessman_state = 1;
				setfillcolor(BLACK);
				solidcircle(454 + 7 * 38, 94 + 7 * 38, 15);
				break;
			}
			if (chess_click.uMsg == WM_LBUTTONUP) {
				for (AIchessx = 454; AIchessx <= 986; AIchessx += 38) {
					for (AIchessy = 94; AIchessy <= 626; AIchessy += 38) {
						if (100 > ((chess_click.x - AIchessx)*(chess_click.x - AIchessx) + (chess_click.y - AIchessy)*(chess_click.y - AIchessy))) {
							AIplot_x = (AIchessx - 454) / 38;
							AIplot_y = (AIchessy - 94) / 38;
							if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
							{
								wuziqi[AIplot_x][AIplot_y].chessman_state = 2;
								setfillcolor(WHITE);
								solidcircle(AIchessx, AIchessy, 15);
								if (vord(AIplot_x, AIplot_y, 2)==0)
								{
									settextcolor(BLACK);
									setbkmode(TRANSPARENT);//设置字体背景透明
									settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
									outtextxy(454 + 7 * 38, 94 + 7 * 38, "白五子连珠");
								}
								local_info = AI(1);
								AIplot_x = local_info / 100;
								AIplot_y = local_info % 100;
								if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
								{
									wuziqi[AIplot_x][AIplot_y].chessman_state = 1;
									setfillcolor(BLACK);
									AIchessx = AIplot_x * 38 + 454;
									AIchessy = AIplot_y * 38 + 94;
									solidcircle(AIchessx, AIchessy, 15);
									if (vord(AIplot_x, AIplot_y, 1) == 0)
									{
										settextcolor(BLACK);
										setbkmode(TRANSPARENT);//设置字体背景透明
										settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
										outtextxy(454 + 7 * 38, 94 + 7 * 38, "黑五子连珠");
									}
								}
							}
							AIchessx = 986;
							AIchessy = 626;
						}
					}
				}
			}
			else {

			}
		}break;
		case AI_MODE:
		{
			chess_click = GetMouseMsg();
			if (wuziqi[7][7].chessman_state != 1) {
				wuziqi[7][7].chessman_state = 1;
				setfillcolor(BLACK);
				solidcircle(454 + 7 * 38, 94 + 7 * 38, 15);
				settextcolor(WHITE);
				setbkmode(TRANSPARENT);//设置字体背景透明
				settextstyle(20, 0, "黑体");//设置文字样式，宽度20，高度自适应
				turn_str[0] = (turn / 100) + '0';
				turn_str[1] = (turn / 10) + '0';
				turn_str[2] = (turn % 10) + '0';
				outtextxy(454 + 7 * 38 - 5, 94 + 7 * 38, turn_str);
				turn++;
				break;
			}
			if (chess_click.uMsg == WM_LBUTTONUP) {
				local_info = AI(2);
				AIplot_x = local_info / 100;
				AIplot_y = local_info % 100;
				if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
				{
					wuziqi[AIplot_x][AIplot_y].chessman_state = 2;
					setfillcolor(WHITE);
					AIchessx = AIplot_x * 38 + 454;
					AIchessy = AIplot_y * 38 + 94;
					solidcircle(AIchessx, AIchessy, 15);

					settextcolor(BLACK);
					setbkmode(TRANSPARENT);//设置字体背景透明
					settextstyle(20, 0, "黑体");//设置文字样式，宽度20，高度自适应
					turn_str[0] = (turn / 100)+'0';
					turn_str[1] = (turn %100/ 10)+'0';
					turn_str[2] = (turn % 10)+'0';
					outtextxy(AIchessx-5, AIchessy, turn_str);
					turn++;

					if (vord(AIplot_x, AIplot_y, 2) == 0)
					{
						settextcolor(BLACK);
						setbkmode(TRANSPARENT);//设置字体背景透明
						settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
						outtextxy(454 + 7 * 38, 94 + 7 * 38, "白五子连珠");
					}
					local_info = AI(1);
					AIplot_x = local_info / 100;
					AIplot_y = local_info % 100;
					if (wuziqi[AIplot_x][AIplot_y].chessman_state == 0)
					{
						wuziqi[AIplot_x][AIplot_y].chessman_state = 1;
						setfillcolor(BLACK);
						AIchessx = AIplot_x * 38 + 454;
						AIchessy = AIplot_y * 38 + 94;
						solidcircle(AIchessx, AIchessy, 15);

						settextcolor(WHITE);
						setbkmode(TRANSPARENT);//设置字体背景透明
						settextstyle(20, 0, "黑体");//设置文字样式，宽度20，高度自适应
						turn_str[0] = (turn / 100) + '0';
						turn_str[1] = (turn %100/ 10) + '0';
						turn_str[2] = (turn % 10) + '0';
						outtextxy(AIchessx-5, AIchessy, turn_str);
						turn++;

						if (vord(AIplot_x, AIplot_y, 1) == 0)
						{
							settextcolor(BLACK);
							setbkmode(TRANSPARENT);//设置字体背景透明
							settextstyle(40, 0, "黑体");//设置文字样式，宽度20，高度自适应
							outtextxy(454 + 7 * 38, 94 + 7 * 38, "黑五子连珠");
						}
					}
				}
				AIchessx = 986;
				AIchessy = 626;
			}
		}break;
		}

	}
	return 0;
}

int AI(int v)//AI思考函数
{
	int x = 0, y = 0, i = 0, jieduan[4] = {0,0,0,0}, score = 0, score_max = 0, score_jingong = 0, score_fangshou = 0;
	int x_r = 0, y_r = 0;
	int lx_min = 0, ly_min = 0;
	int lx_max = 0, ly_max = 0;
	for (x = 0; x < 15; x++)//对每个未落子点进行评估
	{
		for (y = 0; y < 15; y++)
		{
			if (wuziqi[x][y].chessman_state == 0)
			{
				if (vord(x, y, v) == 0)
				{
					return x * 100 + y;
				}
				else
				{
					for (i = 0; i < 4; i++)
					{
						if ((lianzizhongduan[i * 2] != 0) || (lianzizhongduan[i * 2] != 0))
						{
							jieduan[i] = 1;
						}
						else if ((lianzizhongduan[i * 2] != 0) && (lianzizhongduan[i * 2] != 0))
						{
							jieduan[i] = 2;
						}
						else
						{
							jieduan[i] = 0;
						}
						switch (lianziqingkuang[i])
						{
						case 2: {
							if (jieduan[i] == 0)
							{
								score_jingong += 30;
							}
							else if (jieduan[i] == 1)
							{
								score_jingong += 10;
							}
							else if (jieduan[i] == 2)
							{
								score_jingong += 0;
							}
						}; break;
						case 3: {
							if (jieduan[i] == 0)
							{
								score_jingong += 50;
							}
							else if (jieduan[i] == 1)
							{
								score_jingong += 20;
							}
							else if (jieduan[i] == 2)
							{
								score_jingong += 0;
							}
						}; break;
						case 4: {
							if (jieduan[i] == 0)
							{
								score_jingong += 100;
							}
							else if (jieduan[i] == 1)
							{
								score_jingong += 50;
							}
							else if (jieduan[i] == 2)
							{
								score_jingong += 0;
							}
						}; break;
						default:
							break;
						}
					}
				}

				if (vord(x, y, (3 - v)) == 0)
				{

					return x * 100 + y;
				}
				else
				{
					for (i = 0; i < 4; i++)
					{
						if ((lianzizhongduan[i * 2] != 0) || (lianzizhongduan[i * 2] != 0))
						{
							jieduan[i] = 1;
						}
						else if ((lianzizhongduan[i * 2] != 0) && (lianzizhongduan[i * 2] != 0))
						{
							jieduan[i] = 2;
						}
						else
						{
							jieduan[i] = 0;
						}
						switch (lianziqingkuang[i])
						{
						case 2: {
							if (jieduan[i] == 0)
							{
								score_fangshou += 30;
							}
							else if (jieduan[i] == 1)
							{
								score_fangshou += 10;
							}
							else if (jieduan[i] == 2)
							{
								score_fangshou += 0;
							}
						}; break;
						case 3: {
							if (jieduan[i] == 0)
							{
								score_fangshou += 50;
							}
							else if (jieduan[i] == 1)
							{
								score_fangshou += 20;
							}
							else if (jieduan[i] == 2)
							{
								score_fangshou += 0;
							}
						}; break;
						case 4: {
							if (jieduan[i] == 0)
							{
								score_fangshou += 1000;
							}
							else if (jieduan[i] == 1)
							{
								score_fangshou += 50;
							}
							else if (jieduan[i] == 2)
							{
								score_fangshou += 0;
							}
						}; break;
						default:
							break;
						}
					}
				}
				score = score_jingong * 0.5 + score_fangshou * 0.5;
				if (score_max < score)
				{
					score_max = score;
					x_r = x;
					y_r = y;
				}
				score = 0;
				score_jingong = 0;
				score_fangshou = 0;
			}
			//if (wuziqi[x][y].chessman_state == 0)
			//{
			//	if (x < 5) 
			//	{
			//		lx_min = 0;
			//		lx_max = x+5;
			//	}
			//	else if (x > 9)
			//	{
			//		lx_max = 15;
			//		lx_min = x - 5;
			//	}
			//	else
			//	{
			//		lx_min = x - 5;
			//		lx_max = x + 5;
			//	}
			//	if (y < 5)
			//	{
			//		ly_min = 0;
			//		ly_max = x + 5;
			//	}
			//	else if (y > 9)
			//	{
			//		ly_max = 15;
			//		ly_min = x - 5;
			//	}
			//	else
			//	{
			//		ly_min = x - 5;
			//		ly_max = x + 5;
			//	}
			//	for (; lx_min < lx_max; lx_min++)//计算得分
			//	{
			//		for (; ly_min < ly_max; ly_min++)
			//		{

			//		}
			//	}
			//}
		}
	}
	return x_r * 100 + y_r;
}

int vord(int x,int y,int v)//胜负判定 
{
	int i = 0,lianzishu=1,lx=x,ly=y;
	lianzishu = 1;
	int lianzhushumax = 0;
	lx = x;
	ly = y;
	//上下判断
	for (i = 1; i < 5;i++)
	{
		ly++;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{
				
				lianzizhongduan[0]=wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[0] = 3-v;
			}
			break;
		}
	}
	lianzibaxiang[0] = lianzishu;
	lx = x;
	ly = y;
	for (i = 0; i < 5; i++)
	{
		ly--;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[1] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[1] = 3-v;
			}
			break;
		}
	}
	lianziqingkuang[0] = lianzishu;
	lianzibaxiang[1] = lianziqingkuang[0]- lianzibaxiang[1];
	if (lianzishu >= 5)
	{
		return 0;
	}
	else
	{
		if(lianzishu>lianzhushumax)
		{
			lianzhushumax = lianzishu;
		}
	}
	//左右判断
	lianzishu = 1;
	lx = x;
	ly = y;
	for (i = 1; i < 5; i++)
	{
		lx++;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[2] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[2] = 3-v;
			}
			break;
		}
	}
	lianzibaxiang[2] = lianzishu;
	lx = x;
	ly = y;
	for (i = 0; i < 5; i++)
	{
		lx--;
		if ((((lx >= 0) && (lx <= 14))&& ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[3] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[3] = 3-v;
			}
			break;
		}
	}
	lianziqingkuang[1] = lianzishu;
	lianzibaxiang[3] = lianziqingkuang[2] - lianzibaxiang[3];
	if (lianzishu >= 5)
	{
		return 0;
	}
	else
	{
		if (lianzishu > lianzhushumax)
		{
			lianzhushumax = lianzishu;
		}
	}
	//左斜判断
	lianzishu = 1;
	lx = x;
	ly = y;
	for (i = 1; i < 5; i++)
	{
		lx++;
		ly--;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[4] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[4] = 3-v;
			}
			break;
		}
	}
	lianzibaxiang[4] = lianzishu;
	lx = x;
	ly = y;
	for (i = 0; i < 5; i++)
	{
		lx--;
		ly++;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[5] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[5] = 3-v;
			}
			break;
		}
	}
	lianziqingkuang[2] = lianzishu;
	lianzibaxiang[5] = lianziqingkuang[4] - lianzibaxiang[5];
	if (lianzishu >= 5)
	{
		return 0;
	}
	else
	{
		if (lianzishu > lianzhushumax)
		{
			lianzhushumax = lianzishu;
		}
	}
	//右斜判断
	lianzishu = 1;
	lx = x;
	ly = y;
	for (i = 1; i < 5; i++)
	{
		lx++;
		ly++;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[6] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[6] = 3-v;
			}
			break;
		}
	}
	lianzibaxiang[6] = lianzishu;
	lx = x;
	ly = y;
	for (i = 0; i < 5; i++)
	{
		lx--;
		ly--;
		if ((((lx >= 0) && (lx <= 14)) && ((ly >= 0) && (ly <= 14))) && (wuziqi[lx][ly].chessman_state == v))
		{
			lianzishu++;
		}
		else
		{
			if (((lx >= 0) && (lx < 14)) && ((ly >= 0) && (ly < 14)))
			{

				lianzizhongduan[7] = wuziqi[lx][ly].chessman_state;
			}
			else
			{
				lianzizhongduan[7] = 3-v;
			}
			break;
		}
	}
	lianziqingkuang[3] = lianzishu;
	lianzibaxiang[7] = lianziqingkuang[6] - lianzibaxiang[7];
	if (lianzishu >= 5)
	{
		return 0;
	}
	else
	{
		if (lianzishu > lianzhushumax)
		{
			lianzhushumax = lianzishu;
		}
	}
	return lianzhushumax;
}

//uint8_t chess_dorl() {
//	if (turn_black == 1) {
//		for (deal_x = 0, deal_y = 0; deal_x <= 20; deal_x++) {
//			weiqi[deal_x][deal_y].chessman_state = BLACK;
//		}
//		for (deal_x = 0, deal_y = 20; deal_x <= 20; deal_x++) {
//			weiqi[deal_x][deal_y].chessman_state = BLACK;
//		}
//		for (deal_x = 0, deal_y = 0; deal_y <= 20; deal_y++) {
//			weiqi[deal_x][deal_y].chessman_state = BLACK;
//		}
//		for (deal_x = 20, deal_y = 0; deal_y <= 20; deal_y++) {
//			weiqi[deal_x][deal_y].chessman_state = BLACK;
//		}
//		deal_x = AIchessx;
//		deal_y = AIchessy;
//		for (offsetx = -1; offsetx <= 1;offsetx++) {
//			for (offsety = -1; offsety <= 1; offsety++) {
//
//			}
//		}
//	}
//	return 0;
//}
