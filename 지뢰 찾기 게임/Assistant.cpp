#include "common.h"
#include "student.h"
Assistant::Assistant()
{
}

Point Assistant::input()
{
	//������ġ�� Ȯ���ϱ� ����
	//p�� �����Ͽ� ��ȯ
	Point p(rand() % BOARD_SIZE, rand() % BOARD_SIZE);
	return p;
}

void Assistant::checkMineInfo(Point p)
{
}

void Assistant::checkBoardInfo(Point p, int value)
{
}