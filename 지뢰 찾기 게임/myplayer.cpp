#include "Common.h"
#include "Point.h"
#include "myplayer.h"

//My_Borad,isOpend,탐색에 필요한 fixed_x와fixed_y값을 초기화하는 생성자
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
<변수>
-x , y => 탐색 할 x,y
-max => 열린 것들 중 가장 큰 값을 저장할 변수
-max_x , max_y => 열린것들 중 가장 큰 좌표를 저장 할 변수
-order => 순서대로 탐색을 해야할지 말아야할지 판단 할 변수
1. 탐색하고 있는 것이 있는지 없는지 판별
  1-1. 탐색하고 있는 것이 없다면
  (1)반복문을 통해 (0,0)부터 순서대로 보면서 열린곳 중 1이상(주변 지뢰 존재)인 곳 찾는데,
	 이 중 가장 큰 값을 찾아서 고정값으로 설정하고 탐색.
  (2)만약 1이상인 곳이 없다면 (1,1)부터 x와 y값을 이중반복문을 통해 순서대로 +3씩 증가시키면서 안 열린곳 열기.
	 이 때, 만약 열려있으나 그게 지뢰라면 그 주변 다 탐색하기(범위 주의).
	 => (1,1)->(4,1)->(7,1)->...(196,199)>(199,199)순서대로 판별. 보드판에서 주변 지뢰 존재 여부를 다 판별 할 수 있는 가장 빠른 방법이라 생각함.
  1-2. 탐색하고 있는 것이 있다면
  (1)x,y 값들을 각각 고정 값으로 설정
2. 탐색 시작
  2-1. 모서리 및 사이드인지 판별
  =>모서리와 사이드는 일반적인 탐색과 다르다고 생각하여 따로 분리하여 탐색 진행
  (1)4개의 모서리 부분 판별
  (2)그 후 사이드 부분인지 판별
  2-2. 무조건 지뢰가 있는 곳 판별
  =>주변에 지뢰가 있는 곳을 발견 했을 때 이 주변에 열린 것들을 이용해서 무조건 지뢰 위치를 찾을 수 있는 조건을 따져본다.
  (1)4개의 대각선 위치 중에 열린곳이 3개 이상이고 이 3개가 0이하라면 남은 대각선 위치에 무조건 지뢰 존재
  (2)위,아래,왼쪽,오른쪽 중 시계반향으로 연속 2개가 0이하일 경우 반대 대각선에 무조건 지뢰 존재
  2-3. 위의 경우들을 제외한 일반적인 경우
  =>기본적으로 위,아래를 열고 판별 시작함
  (1)위가 안열려있을 경우 -> 위 오픈
  (2)아래가 안열려있을 경우 -> 아래 오픈
  (3)위가 0이고 아래는 1이상일 경우 -> 왼쪽 밑 대각선, 오른쪽 밑 대각선 판별
  (4)위가 1이상이고 아래가 0일 경우 -> 왼쪽 위 대각선, 오른쪽 위 대각선 판별
  (5)위 아래 둘 다 1이상일 경우 -> 왼쪽, 오른쪽 판별 후
  오른쪽이 0일 경우 왼쪽 위 대각선,왼쪽 아래 대각선 판별
  왼쪽이 0일 경우 오른쪽 위 대각선,오른쪽 아래 대각선 판별
  만약 왼쪽,오른쪽이 둘 다 1이상이거나 둘 중 하나 이상이 지뢰였다면 대각선 다 판별
  (6)위 아래 둘 중 하나가 지뢰라면
  위가 0이라면 왼쪽 아래 대각선,오른쪽 아래 대각선 판별
  아래가 0이라면 왼쪽 위 대각선,아래쪽 위 대각선 판별
  그 외라면 왼쪽,오른쪽,대각선들 순서대로 판별
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
확인한 위치에 지뢰가 있을 경우 호출될 메소드(지뢰 위치 p)
1.만약 오픈된 곳이 아니라면 오픈 표시.
2.My_Board에 지뢰라는 -1표시.
3.지뢰 주변 값들 -1씩 하기(이때, 사이드 주의하기).
4.만약 발견된 지뢰가 고정 탐색하던 곳 주변이고 주변 지뢰가 다 발견되었다면 finish를 true로 바꿔줌으로써 고정 탐색하던것을 끝낸다.
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
확인한 위치에 지뢰가 없을 경우 호출될 메소드.
1.My_Board판에 값을 넣어야하는데 이 값은 만약 발견된 지뢰 근처라면 그 전에 숫자를 빼줬으니
 그 빼준 숫자를 반영하기 위해 20 - My_Board[p.getX()][p.getY()]을 발견값(value)에서 빼준다.
2.열렸으니 My_isOpend값을 true로 변경.
3.만약 고정탐색이 끝나지 않았는데 발견 값이 고정탐색 값보다 크다면 고정탐색 좌표를 발견한 좌표로 변경
4.고정탐색이 없고 발견값이 1~10사이의 값이라면 고정 좌표 설정하고 finish를 false로 설정.
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
My_Board[x][y]의 값 확인 함수
0이하라면 반환값은 1    => 오픈되어있고 근처에 지뢰 X or 지뢰
1~10사이라면 반환값은 2 => 오픈되어있고 근처에 지뢰 존재
10~20이라면 반환값은 3  => 아직 오픈 X
*/
int myplayer::openRange(int x, int y) {
	if (My_Board[x][y] <= 0)
		return 1;
	else if (My_Board[x][y] > 0 && My_Board[x][y] < 10)
		return 2;
	else if (My_Board[x][y] > 10 && My_Board[x][y] <= 20)
		return 3;
}
