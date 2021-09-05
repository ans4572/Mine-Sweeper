#include "Game.h"
Game::Game()
{
	//���� ��ġ�� �����ϰ� �����ؼ� ������
	//��, �ߺ��� ��ġ�� �������� �ʵ��� ��
	Point randomMinePosition[MINE_COUNT];
	for(int i = 0 ; i < MINE_COUNT ; i++)
	{
		Point p = Point(rand()%BOARD_SIZE, rand()%BOARD_SIZE);
		bool isFind = false;
		for(int j = 0 ; j < i ; j++)
		{
			if(randomMinePosition[j] == p)
			{
				isFind = true;
				break;
			}
		}
		if(isFind) i--;
		else randomMinePosition[i] = p;
	}

	//���带 0���� �ʱ�ȭ��
	memset(board, 0, sizeof(board));

	//��� ��ġ�� ����� ���� ������ �ʱ�ȭ��
	memset(isOpend, 0, sizeof(isOpend));

	//���� ���忡 ���ڸ� �ź���
	for(int i = 0 ; i < MINE_COUNT ; i++)
	{
		insertMine(randomMinePosition[i]);
	}

}
void Game::insertMine(Point p)
{
	//���ڸ� �������� 8������ Ȯ���ϱ� ���� ��ġ ����
	const int x[] = { -1, -1, -1, 0, 0, 1, 1, 1};
	const int y[] = { -1, 0, 1, -1, 1, -1, 0, 1};

	int _x = p.getX(), _y = p.getY();
	for(int i = 0 ; i < 8 ; i++)
	{
		//8������ Ȯ���ϸ鼭
		//���� ���� �̳��̰� ���ڰ� �ƴϸ� 1�� ����
		Point newP = Point(_x + x[i], _y + y[i]);
		if(newP.checkBoardRange())
		{
			if(board[ newP.getX() ][ newP.getY() ] == -1)
				continue;
			board[ newP.getX() ][ newP.getY() ]++;
		}
	}

	//���ڸ� ������
	board[ _x ][ _y ] = -1;
}
int Game::getBoardInfo(Point p)
{
	//������ ��� ��� 0���� ����
	if(p.checkBoardRange() == false)
		return 0;

	//�� ���� ��� �ش� �� ��ȯ
	return board[p.getX()][p.getY()];
}

bool Game::checkOpend(Point p)
{
	return isOpend[p.getX()][p.getY()];
}

void Game::setOpend(Point p)
{
	isOpend[p.getX()][p.getY()] = true;
}