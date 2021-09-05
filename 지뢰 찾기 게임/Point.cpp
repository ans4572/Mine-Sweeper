#include "Point.h"
#include "common.h"
Point::Point(){}

//x, y�� �Ű������� �޾Ƽ� �ٷ� �ʱ�ȭ�ϴ� ������
Point::Point(int _x=0,int _y=0):x(_x), y(_y){}

//x�� ���� ��ȯ����
int Point::getX()
{
	return x;
}
//y�� ���� ��ȯ����
int Point::getY()
{
	return y;
}

//PointŬ������ �ν���Ʈ�� �ٷ� ����� �� �ֵ��� �������̵�
ostream& operator << (ostream& os, const Point& p)
{
	os << "[" << p.x << "," << p.y << "]";
	return os;
}

//������ ���ϰ� �ϱ����� =������ �������̵�
Point& Point::operator = (const Point &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

//�񱳸� ���ϰ� �ϱ����� ==������ �������̵�
bool Point::operator == (const Point &p)
{
	return (x==p.x) && (y==p.y);
}

//�񱳸� ���ϰ� �ϱ����� !=������ �������̵�
bool Point::operator != (const Point &p)
{
	return !((x==p.x) && (y==p.y));
}

bool Point::checkBoardRange()
{
	//���� ���� �̳��� ��ǥ�� �ԷµǾ����� Ȯ���Ͽ�
	//���� ���� ��� false, ���� ���� ��� true ����
	if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
		return false;
	return true;
}