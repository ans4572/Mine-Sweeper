#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "Common.h"
class Game
{
private:
	//�÷����� ������
	int board[BOARD_SIZE][BOARD_SIZE];
	//���µ� ��ġ�� ǥ��
	bool isOpend[BOARD_SIZE][BOARD_SIZE];

	//���ڸ� �ź���Ű�� �޼ҵ�
	//Game Ŭ���� �ܺο��� ������� �ʵ��� private
	void insertMine(Point p);
public:
	Game();
	//Ư�� ��ġ�� �ִ� ���� ��ȯ
	int getBoardInfo(Point p);

	//Ư�� ��ġ�� Ȯ�ε� �������� üũ
	bool checkOpend(Point p);

	//Ư�� ��ġ�� ���ȴٰ� ǥ��
	void setOpend(Point p);
};

#endif