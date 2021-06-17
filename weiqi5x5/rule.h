#pragma once
#include "stdint.h"
#include <graphics.h>

#define CHESSBOARD_WIDTH 15
#define CHESSBOARD_HEIGHT 15
#define BLACK_WIN_NUM 185
#define WHITE_WIN_NUM 176
#define CHESS_BOARD_COLOR 0x5BD6F9
#define FREE_MODE 0
#define AI_MODE_BLACK 1
#define AI_MODE_WHITE 2
#define AI_MODE 3
#define TRAIN_MODE 1
#define GAME_MODE 2
typedef enum{
	CHESS_WHITE,
	CHESS_BLACK,
	NONE,

}CHESSMAN_STATE;

typedef enum {
	SINGLE,
	ZERO,
	MUCH,
}RETURN_STATE;

typedef struct {
	uint8_t chessman_state;//棋子状态
	uint8_t sidenum;//周围棋子数
}CHESSMAN_CLASS;

void chessboard_init();




void chessboard_init() {//棋盘初始化
	IMAGE img_background;
	int chess_x, chess_y;
	initgraph(1080, 720);
	setorigin(0, 0);
	loadimage(&img_background, _T("../background.jpg"));
	putimage(0, 0, &img_background);
	setfillcolor(CHESS_BOARD_COLOR);
	fillrectangle(360, 0, 1080, 720);
	setlinecolor(BLACK);
	for (chess_x = 454; chess_x <= 986; chess_x += 38) {
		line(chess_x, 94, chess_x, 626);
	}
	for (chess_y = 94; chess_y <= 626; chess_y += 38) {
		line(454,chess_y,986,chess_y);
	}
	setfillcolor(BLACK);
	solidcircle(454 + 7 * 38, chess_y = 94 + 7 * 38,8);
}
