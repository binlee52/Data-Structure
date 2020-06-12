#pragma once
#define INF 1000000000
#define BOX -1
#define USER 0

#include <iostream>

using namespace std;

class Point
{
private:
	int row;
	int col;
public:
	// set row & col
	void set(int x, int y)
	{
		row = x;
		col = y;
	}
	// get row
	int getR()
	{
		return row;
	}
	// get col
	int getC()
	{
		return col;
	}
};

class Maze
{
public:
	// Constructor
	Maze(int row, int col);

	// Destructor
	~Maze();

	// access to edge like 2D array
	int& edge(int row, int col);
	void showMaze();
	void makeMaze();
private:
	int* adjMatrix;
	int max_row, max_col;

	// special index
	Point user;
	Point target;
	Point box;
};