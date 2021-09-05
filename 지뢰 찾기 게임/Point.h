#ifndef POINT_H
#define POINT_H

#include "Common.h"

class Point
{
	friend ostream& operator<<(ostream& os, const Point& p);
private:
	int x, y;
public:
	Point();
	Point(int,int);
	int getX();
	int getY();
	Point& operator = (const Point &p);
	bool operator == (const Point &p);	
	bool operator != (const Point &p);
	//���� ���� �̳����� 
	bool checkBoardRange();
};

#endif