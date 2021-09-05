#include "Common.h"
#include "Point.h"
#include "myplayer.h"

//My_Borad,isOpend,Ž���� �ʿ��� fixed_x��fixed_y���� �ʱ�ȭ�ϴ� ������
myplayer::myplayer()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			My_Board[i][j] = 20;
			My_isOpend[i][j] = false;
		}
	}
	finish = true;
	fixed_x = 0, fixed_y = 0;
}

/*
<����>
-x , y => Ž�� �� x,y
-max => ���� �͵� �� ���� ū ���� ������ ����
-max_x , max_y => �����͵� �� ���� ū ��ǥ�� ���� �� ����
-order => ������� Ž���� �ؾ����� ���ƾ����� �Ǵ� �� ����
1. Ž���ϰ� �ִ� ���� �ִ��� ������ �Ǻ�
  1-1. Ž���ϰ� �ִ� ���� ���ٸ�
  (1)�ݺ����� ���� (0,0)���� ������� ���鼭 ������ �� 1�̻�(�ֺ� ���� ����)�� �� ã�µ�,
	 �� �� ���� ū ���� ã�Ƽ� ���������� �����ϰ� Ž��.
  (2)���� 1�̻��� ���� ���ٸ� (1,1)���� x�� y���� ���߹ݺ����� ���� ������� +3�� ������Ű�鼭 �� ������ ����.
	 �� ��, ���� ���������� �װ� ���ڶ�� �� �ֺ� �� Ž���ϱ�(���� ����).
	 => (1,1)->(4,1)->(7,1)->...(196,199)>(199,199)������� �Ǻ�. �����ǿ��� �ֺ� ���� ���� ���θ� �� �Ǻ� �� �� �ִ� ���� ���� ����̶� ������.
  1-2. Ž���ϰ� �ִ� ���� �ִٸ�
  (1)x,y ������ ���� ���� ������ ����
2. Ž�� ����
  2-1. �𼭸� �� ���̵����� �Ǻ�
  =>�𼭸��� ���̵�� �Ϲ����� Ž���� �ٸ��ٰ� �����Ͽ� ���� �и��Ͽ� Ž�� ����
  (1)4���� �𼭸� �κ� �Ǻ�
  (2)�� �� ���̵� �κ����� �Ǻ�
  2-2. ������ ���ڰ� �ִ� �� �Ǻ�
  =>�ֺ��� ���ڰ� �ִ� ���� �߰� ���� �� �� �ֺ��� ���� �͵��� �̿��ؼ� ������ ���� ��ġ�� ã�� �� �ִ� ������ ��������.
  (1)4���� �밢�� ��ġ �߿� �������� 3�� �̻��̰� �� 3���� 0���϶�� ���� �밢�� ��ġ�� ������ ���� ����
  (2)��,�Ʒ�,����,������ �� �ð�������� ���� 2���� 0������ ��� �ݴ� �밢���� ������ ���� ����
  2-3. ���� ������ ������ �Ϲ����� ���
  =>�⺻������ ��,�Ʒ��� ���� �Ǻ� ������
  (1)���� �ȿ������� ��� -> �� ����
  (2)�Ʒ��� �ȿ������� ��� -> �Ʒ� ����
  (3)���� 0�̰� �Ʒ��� 1�̻��� ��� -> ���� �� �밢��, ������ �� �밢�� �Ǻ�
  (4)���� 1�̻��̰� �Ʒ��� 0�� ��� -> ���� �� �밢��, ������ �� �밢�� �Ǻ�
  (5)�� �Ʒ� �� �� 1�̻��� ��� -> ����, ������ �Ǻ� ��
  �������� 0�� ��� ���� �� �밢��,���� �Ʒ� �밢�� �Ǻ�
  ������ 0�� ��� ������ �� �밢��,������ �Ʒ� �밢�� �Ǻ�
  ���� ����,�������� �� �� 1�̻��̰ų� �� �� �ϳ� �̻��� ���ڿ��ٸ� �밢�� �� �Ǻ�
  (6)�� �Ʒ� �� �� �ϳ��� ���ڶ��
  ���� 0�̶�� ���� �Ʒ� �밢��,������ �Ʒ� �밢�� �Ǻ�
  �Ʒ��� 0�̶�� ���� �� �밢��,�Ʒ��� �� �밢�� �Ǻ�
  �� �ܶ�� ����,������,�밢���� ������� �Ǻ�
*/
Point myplayer::input()
{
	int x, y;
	int max = 0;
	int max_x = 0, max_y = 0;
	bool order = true;

	if (finish == true) {
		for (y = 0; y < BOARD_SIZE; y++) {
			for (x = 0; x < BOARD_SIZE; x++) {
				if ((openRange(x, y) == 2) && (max < My_Board[x][y])) {
					max = My_Board[x][y];
					max_x = x;
					max_y = y;
					finish = false;
					order = false;
				}
			}
		}
		if (finish == false) {
			x = max_x;
			y = max_y;
			fixed_x = x;
			fixed_y = y;
		}
		if (order == true) {
			for (y = 1; y < BOARD_SIZE; y += 3) {
				for (x = 1; x < BOARD_SIZE; x += 3) {
					if (My_isOpend[x][y] == false && x < BOARD_SIZE && y < BOARD_SIZE) {
						Point p(x, y);
						return p;
					}
					if (My_Board[x][y] < 0) {
						const int x_[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
						const int y_[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
						for (int i = 0; i < 8; i++) {
							if (My_isOpend[x + x_[i]][y + y_[i]] == false && (x + x_[i]) >= 0 && (x + x_[i]) < BOARD_SIZE && (y + y_[i]) >= 0 && (y + y_[i]) < BOARD_SIZE) {
								Point p(x + x_[i], y + y_[i]);
								return p;
							}
						}
					}
				}
			}
		}
	}
	else {
		x = fixed_x;
		y = fixed_y;
	}
	if (x == 0 && y == 0) {
		if (My_isOpend[x + 1][y] == false) {
			Point p(x + 1, y);
			return p;
		}
		else if (My_isOpend[x + 1][y + 1] == false) {
			Point p(x + 1, y + 1);
			return p;
		}
		else if (My_isOpend[x][y + 1] == false) {
			Point p(x, y + 1);
			return p;
		}
	}
	else if ((x == BOARD_SIZE - 1) && (y == 0)) {
		if (My_isOpend[x - 1][y] == false) {
			Point p(x - 1, y);
			return p;
		}
		else if (My_isOpend[x - 1][y + 1] == false) {
			Point p(x - 1, y + 1);
			return p;
		}
		else if (My_isOpend[x][y + 1]) {
			Point p(x, y + 1);
			return p;
		}
	}
	else if ((x == BOARD_SIZE - 1) && (y == BOARD_SIZE - 1)) {
		if (My_isOpend[x][y - 1] == false) {
			Point p(x, y - 1);
			return p;
		}
		else if (My_isOpend[x - 1][y - 1] == false) {
			Point p(x - 1, y - 1);
			return p;
		}
		else if (My_isOpend[x - 1][y] == false) {
			Point p(x - 1, y);
			return p;
		}
	}
	else if ((x == 0) && (y == BOARD_SIZE - 1)) {
		if (My_isOpend[x][y - 1] == false) {
			Point p(x, y - 1);
			return p;
		}
		else if (My_isOpend[x + 1][y - 1] == false) {
			Point p(x + 1, y - 1);
			return p;
		}
		else if (My_isOpend[x + 1][y] == false) {
			Point p(x + 1, y);
			return p;
		}
	}
	else if (x == 0) {
		if ((My_isOpend[x][y - 1] == false)) {
			Point p(x, y - 1);
			return p;
		}
		else if ((My_isOpend[x][y - 1] == true) && (My_isOpend[x][y + 1] == false)) {
			Point p(x, y + 1);
			return p;
		}
		else if (My_Board[x][y - 1] == 0) {
			Point p(x + 1, y + 1);
			return p;
		}
		else if (My_Board[x][y + 1] == 0) {
			Point p(x + 1, y - 1);
			return p;
		}
		else if ((openRange(x, y - 1) == 2 && openRange(x, y + 1) == 2) || My_Board[x][y - 1] < 0 || My_Board[x][y + 1] < 0) {
			if (My_isOpend[x + 1][y] == false) {
				Point p(x + 1, y);
				return p;
			}
			else if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
	}
	else if (x == BOARD_SIZE - 1) {
		if ((My_isOpend[x][y - 1] == false)) {
			Point p(x, y - 1);
			return p;
		}
		else if ((My_isOpend[x][y - 1] == true) && (My_isOpend[x][y + 1] == false)) {
			Point p(x, y + 1);
			return p;
		}
		else if (My_Board[x][y - 1] == 0) {
			Point p(x - 1, y + 1);
			return p;
		}
		else if (My_Board[x][y + 1] == 0) {
			Point p(x - 1, y - 1);
			return p;
		}
		else if ((openRange(x, y - 1) == 2 && openRange(x, y + 1) == 2) || My_Board[x][y - 1] < 0 || My_Board[x][y + 1] < 0) {
			if (My_isOpend[x - 1][y] == false) {
				Point p(x - 1, y);
				return p;
			}
			else if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
		}
	}
	else if (y == 0) {
		if ((My_isOpend[x - 1][y] == false)) {
			Point p(x - 1, y);
			return p;
		}
		else if ((My_isOpend[x - 1][y] == true) && (My_isOpend[x + 1][y] == false)) {
			Point p(x + 1, y);
			return p;
		}
		else if (My_Board[x - 1][y] == 0) {
			Point p(x + 1, y + 1);
			return p;
		}
		else if (My_Board[x + 1][y] == 0) {
			Point p(x - 1, y + 1);
			return p;
		}
		else if ((openRange(x - 1, y) == 2 && openRange(x + 1, y) == 2) || My_Board[x - 1][y] < 0 || My_Board[x + 1][y] < 0) {
			if (My_isOpend[x][y + 1] == false) {
				Point p(x, y + 1);
				return p;
			}
			else if (My_isOpend[x - 1][y + 1] == false) {
				Point p(x - 1, y + 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
	}
	else if (y == BOARD_SIZE - 1) {
		if ((My_isOpend[x - 1][y] == false)) {
			Point p(x - 1, y);
			return p;
		}
		else if ((My_isOpend[x - 1][y] == true) && (My_isOpend[x + 1][y] == false)) {
			Point p(x + 1, y);
			return p;
		}
		else if (My_Board[x - 1][y] == 0) {
			Point p(x + 1, y - 1);
			return p;
		}
		else if (My_Board[x + 1][y] == 0) {
			Point p(x - 1, y - 1);
			return p;
		}
		else if ((openRange(x - 1, y) == 2 && openRange(x + 1, y) == 2) || My_Board[x - 1][y] < 0 || My_Board[x + 1][y] < 0) {
			if (My_isOpend[x][y - 1] == false) {
				Point p(x, y - 1);
				return p;
			}
			else if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
		}
	}

	if (My_isOpend[x - 1][y + 1] == false && My_Board[x + 1][y + 1] == 0 && My_Board[x - 1][y - 1] == 0 && My_Board[x + 1][y - 1] == 0) {
		Point p(x - 1, y + 1);
		return p;
	}
	else if (My_Board[x - 1][y + 1] == 0 && My_isOpend[x + 1][y + 1] == false && My_Board[x - 1][y - 1] == 0 && My_Board[x + 1][y - 1] == 0) {
		Point p(x + 1, y + 1);
		return p;
	}
	else if (My_Board[x - 1][y + 1] == 0 && My_Board[x + 1][y + 1] == 0 && My_isOpend[x - 1][y - 1] == false && My_Board[x + 1][y - 1] == 0) {
		Point p(x - 1, y - 1);
		return p;
	}
	else if (My_Board[x - 1][y + 1] == 0 && My_Board[x + 1][y + 1] == 0 && My_Board[x - 1][y - 1] == 0 && My_isOpend[x + 1][y - 1] == false) {
		Point p(x + 1, y - 1);
		return p;
	}

	if (My_Board[x - 1][y] == 0 && My_Board[x][y - 1] == 0 && My_isOpend[x + 1][y + 1] == false) {
		Point p(x + 1, y + 1);
		return p;
	}
	else if (My_Board[x][y - 1] == 0 && My_Board[x + 1][y] == 0 && My_isOpend[x - 1][y + 1] == false) {
		Point p(x - 1, y + 1);
		return p;
	}
	else if (My_Board[x + 1][y] == 0 && My_Board[x][y + 1] == 0 && My_isOpend[x - 1][y - 1] == false) {
		Point p(x - 1, y - 1);
		return p;
	}
	else if (My_Board[x][y + 1] == 0 && My_Board[x - 1][y] == 0 && My_isOpend[x + 1][y - 1] == false) {
		Point p(x + 1, y - 1);
		return p;
	}

	if ((My_isOpend[x][y - 1] == false)) {
		Point p(x, y - 1);
		return p;
	}
	else if ((My_isOpend[x][y - 1] == true) && (My_isOpend[x][y + 1] == false)) {
		Point p(x, y + 1);
		return p;
	}
	else if (My_Board[x][y - 1] == 0 && openRange(x, y + 1) == 2) {
		if (My_isOpend[x - 1][y + 1] == false) {
			Point p(x - 1, y + 1);
			return p;
		}
		else if (My_isOpend[x + 1][y + 1] == false) {
			Point p(x + 1, y + 1);
			return p;
		}
	}
	else if (openRange(x, y - 1) == 2 && My_Board[x][y + 1] == 0) {
		if (My_isOpend[x - 1][y - 1] == false) {
			Point p(x - 1, y - 1);
			return p;
		}
		else if (My_isOpend[x + 1][y - 1] == false) {
			Point p(x + 1, y - 1);
			return p;
		}
	}
	else if (openRange(x, y - 1) == 2 && openRange(x, y + 1) == 2) {
		if (My_isOpend[x - 1][y] == false) {
			Point p(x - 1, y);
			return p;
		}
		else if (My_isOpend[x + 1][y] == false) {
			Point p(x + 1, y);
			return p;
		}
		else if (My_Board[x + 1][y] == 0) {
			if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x - 1][y + 1] == false) {
				Point p(x - 1, y + 1);
				return p;
			}
		}
		else if (My_Board[x - 1][y] == 0) {
			if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
		else if ((openRange(x - 1, y) == 2 && openRange(x + 1, y) == 2) || My_Board[x - 1][y] < 0 || My_Board[x + 1][y] < 0) {
			if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
			else if (My_isOpend[x - 1][y + 1] == false) {
				Point p(x - 1, y + 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
	}
	else if (My_Board[x][y - 1] < 0 || My_Board[x][y + 1] < 0) {
		if (My_Board[x][y - 1] == 0) {
			if (My_isOpend[x - 1][y + 1] == false) {
				Point p(x - 1, y + 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
		else if (My_Board[x][y + 1] == 0) {
			if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
		}
		else {
			if (My_isOpend[x - 1][y] == false) {
				Point p(x - 1, y);
				return p;
			}
			else if (My_isOpend[x + 1][y] == false) {
				Point p(x + 1, y);
				return p;
			}
			else if (My_isOpend[x - 1][y - 1] == false) {
				Point p(x - 1, y - 1);
				return p;
			}
			else if (My_isOpend[x + 1][y - 1] == false) {
				Point p(x + 1, y - 1);
				return p;
			}
			else if (My_isOpend[x - 1][y + 1] == false) {
				Point p(x - 1, y + 1);
				return p;
			}
			else if (My_isOpend[x + 1][y + 1] == false) {
				Point p(x + 1, y + 1);
				return p;
			}
		}
	}
}

/*
Ȯ���� ��ġ�� ���ڰ� ���� ��� ȣ��� �޼ҵ�(���� ��ġ p)
1.���� ���µ� ���� �ƴ϶�� ���� ǥ��.
2.My_Board�� ���ڶ�� -1ǥ��.
3.���� �ֺ� ���� -1�� �ϱ�(�̶�, ���̵� �����ϱ�).
4.���� �߰ߵ� ���ڰ� ���� Ž���ϴ� �� �ֺ��̰� �ֺ� ���ڰ� �� �߰ߵǾ��ٸ� finish�� true�� �ٲ������ν� ���� Ž���ϴ����� ������.
*/
void myplayer::checkMineInfo(Point p)
{
	if (My_isOpend[p.getX()][p.getY()] == false) {
		My_isOpend[p.getX()][p.getY()] = true;
		My_Board[p.getX()][p.getY()] = -1;
		const int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
		const int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
		for (int i = 0; i < 8; i++) {
			if ((p.getX() + x[i]) >= 0 && (p.getX() + x[i]) < BOARD_SIZE && (p.getY() + y[i]) >= 0 && (p.getY() + y[i]) < BOARD_SIZE)
				My_Board[p.getX() + x[i]][p.getY() + y[i]]--;
		}
		if (My_Board[fixed_x][fixed_y] <= 0 && finish == false) {
			finish = true;
		}
	}
}

/*
Ȯ���� ��ġ�� ���ڰ� ���� ��� ȣ��� �޼ҵ�.
1.My_Board�ǿ� ���� �־���ϴµ� �� ���� ���� �߰ߵ� ���� ��ó��� �� ���� ���ڸ� ��������
 �� ���� ���ڸ� �ݿ��ϱ� ���� 20 - My_Board[p.getX()][p.getY()]�� �߰߰�(value)���� ���ش�.
2.�������� My_isOpend���� true�� ����.
3.���� ����Ž���� ������ �ʾҴµ� �߰� ���� ����Ž�� ������ ũ�ٸ� ����Ž�� ��ǥ�� �߰��� ��ǥ�� ����
4.����Ž���� ���� �߰߰��� 1~10������ ���̶�� ���� ��ǥ �����ϰ� finish�� false�� ����.
*/
void myplayer::checkBoardInfo(Point p, int value)
{
	if (My_isOpend[p.getX()][p.getY()] == false) {
		My_Board[p.getX()][p.getY()] = value - (20 - My_Board[p.getX()][p.getY()]);
		My_isOpend[p.getX()][p.getY()] = true;

		if ((finish == false) && (My_Board[p.getX()][p.getY()] > My_Board[fixed_x][fixed_y])) {
			fixed_x = p.getX();
			fixed_y = p.getY();
		}
		if ((finish == true) && (openRange(p.getX(), p.getY()) == 2)) {
			fixed_x = p.getX();
			fixed_y = p.getY();
			finish = false;
		}
	}
}

/*
My_Board[x][y]�� �� Ȯ�� �Լ�
0���϶�� ��ȯ���� 1    => ���µǾ��ְ� ��ó�� ���� X or ����
1~10���̶�� ��ȯ���� 2 => ���µǾ��ְ� ��ó�� ���� ����
10~20�̶�� ��ȯ���� 3  => ���� ���� X
*/
int myplayer::openRange(int x, int y) {
	if (My_Board[x][y] <= 0)
		return 1;
	else if (My_Board[x][y] > 0 && My_Board[x][y] < 10)
		return 2;
	else if (My_Board[x][y] > 10 && My_Board[x][y] <= 20)
		return 3;
}
