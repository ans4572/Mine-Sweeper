#ifndef myplayer_H
#define myplayer_H
#include "Common.h"
#include "Player.h"
/*
<변수>
-My_Board
:클래스에서 사용할 보드판
< 0 : 지뢰
= 0 : 열려있고 근처에 지뢰 존재 X
0~10 : 근처에 수만큼 지뢰 존재
10~20 : 아직 오픈되지 않음
-My_isOpend
:오픈 되어있는지 안됬는지 판별 보드판
=>My_Board만으로도 판별이 가능하나 코드에서 보기 편하기 위해 사용하였음.
-finish
:주변에 지뢰가 있어 현재 탐색 고정값이 있는지 판별 변수
false : 탐색 고정값이 있음
true : 탐색 고정값이 없음
-fixed_x,fixed_y
:탐색 고정값 좌표

<추가 함수>
openRange(int x,int y)
*/
class myplayer : public Player
{
	int My_Board[BOARD_SIZE][BOARD_SIZE];
	bool My_isOpend[BOARD_SIZE][BOARD_SIZE]; 
	bool finish;
	int fixed_x, fixed_y;
public :
	myplayer();
	Point input();
	void checkMineInfo(Point p);
	void checkBoardInfo(Point p, int value);
	int openRange(int x, int y);
};
#endif