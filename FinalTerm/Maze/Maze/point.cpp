#include "point.h"

// Point Constructor
Point::Point(int _row, int _col)
	: row(_row), col(_col)
{}

// Copy Constructor
Point::Point(const Point& ref)
{
	row = ref.row;
	col = ref.col;
}

// set row & col
void Point::set(int x, int y)
{
	row = x;
	col = y;
}

bool Point::operator==(Point& ref)
{
	if (row == ref.row && col == ref.col)
		return true;
	return false;
}

bool Point::operator!=(Point& ref)
{
	if (row == ref.row && col == ref.col)
		return false;
	return true;
}

Point Point::operator+(const Point& ref)
{
	Point temp(row + ref.row, col + ref.col);
	return temp;
}

Point Point::operator-(const Point& ref)
{
	Point temp(row - ref.row, col - ref.col);
	return temp;
}

Point Point::operator*(const int num)
{
	Point temp(row * num, col * num);
	return temp;
}
