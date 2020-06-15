#pragma once

class Point
{
private:
	int row;
	int col;
public:

	// constructor
	Point(int _row = -1, int _col = -1);

	// copy constructor
	Point(const Point& ref);

	// set row & col
	void set(int x, int y);

	/**Operator overloading**/
	bool operator==(Point& ref);

	bool operator!=(Point& ref);

	Point operator+(const Point& ref);

	Point operator-(const Point& ref);

	Point operator*(const int num);


	// friend class
	friend class Maze;
	friend class MazeVertex;
};