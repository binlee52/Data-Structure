#pragma once
#define INF 1000000000
#define BOX 0
#define USER 1 // TODO

#include <iostream>
#include <utility>
#include <string>
#include <utility>

#include "stackLnk.cpp"
#include "queueLnk.cpp"

using namespace std;

class Point
{
private:
	int row;
	int col;
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

	bool operator!=(Point& ref)
	{
		if (row == ref.row && col == ref.col)
			return false;
		return true;

	}

	Point operator-(Point& ref)
	{
		return Point(row - ref.row, col - ref.col);
	}

	Point operator*(const int num)
	{
		return Point(num * row, num * col);
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


	// special index
	Point user;
	Point target;
	Point box;


	void init_mark();	// init mark as false
	void init_adjMatrix();
	void make_maze();	// construct maze with user input
	void bfs(Point start, Point end);		// breath first search
	void user_bfs(Point start, Point end);		// breath first search
	void backtrace(Point start, Point end);		// search shortest path
	void user_backtrace(Point start, Point end);
	void move();
	void show_maze();	// show maze structure
private:
	int* adjMatrix;
	bool* mark;
	int max_row, max_col;

	Queue<Point> queue;
	Stack<Point> user_queue;
	Stack<Point> stack;
	Stack<Point> user_stack;
	Queue<Point> final_path;

	int direct[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	// check condition
	bool check(int row, int col) const;		// matrix range check
	bool is_path(int row, int col) const;	// path check
	bool is_visit(int row, int col) const;	// confirmation of visit


	void visit(int row, int col);		// visit vertex
	bool& visited(int row, int col);	// access to mark like 2D array
	int& edge(int row, int col);	// access to adj matrix like 2D array

};

