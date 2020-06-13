#pragma once
#define INF 1000000000
#define BOX 0
#define USER 1 // TODO

#include <iostream>
#include <utility>
#include <string>

#include "queueLnk.cpp"

using namespace std;

class Point
{
private:
	int row;
	int col;
	string obj;
public:
	// constructor
	Point(int _row = INF, int _col = INF)
		: row(_row), col(_col)
	{}

	// set row & col
	void set(int x, int y)
	{
		row = x;
		col = y;
	}

	bool operator==(Point& ref)
	{
		if (row == ref.row && col == ref.col)
			return true;
		return false;
	}

	friend class Maze;
};

class Maze
{
public:
	// Constructor
	Maze(int row, int col);

	// Destructor
	~Maze();

	void init_mark();	// init mark as false
	void make_maze();	// construct maze with user input
	void bfs();		// breath first search

	void show_maze();	// show maze structure
private:
	int* adjMatrix;
	bool* mark;
	int max_row, max_col;

	Queue<Point> q;

	// special index
	Point user;
	Point target;
	Point box;

	int direct[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	// check condition
	bool check(int row, int col) const;		// matrix range check
	bool is_path(int row, int col) const;	// path check
	bool is_visit(int row, int col) const;	// confirmation of visit


	void visit(int row, int col);		// visit vertex
	bool& visited(int row, int col);	// access to mark like 2D array
	int& edge(int row, int col);	// access to adj matrix like 2D array

};

