#ifndef myplayer_H
#define myplayer_H
#include "Common.h"
#include "Player.h"
/*
<����>
-My_Board
:Ŭ�������� ����� ������
< 0 : ����
= 0 : �����ְ� ��ó�� ���� ���� X
0~10 : ��ó�� ����ŭ ���� ����
10~20 : ���� ���µ��� ����
-My_isOpend
:���� �Ǿ��ִ��� �ȉ���� �Ǻ� ������
=>My_Board�����ε� �Ǻ��� �����ϳ� �ڵ忡�� ���� ���ϱ� ���� ����Ͽ���.
-finish
:�ֺ��� ���ڰ� �־� ���� Ž�� �������� �ִ��� �Ǻ� ����
false : Ž�� �������� ����
true : Ž�� �������� ����
-fixed_x,fixed_y
:Ž�� ������ ��ǥ

<�߰� �Լ�>
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