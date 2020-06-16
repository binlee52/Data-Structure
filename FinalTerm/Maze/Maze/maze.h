#pragma once

#include <iostream>
#include <string>

#include "point.h"
#include "ptyqueue.cpp"

class MazeVertex
{
private:
	Point box;			// position of box
	Point user;			// position of user
	int push_cnt;		// number of times the box has pushed
	int walk_cnt;		// number of times user has walked
	string path;		// cumulative path

public:
	// constructor
	MazeVertex(Point _box = Point(-1, -1), Point _user = Point(-1, -1), string _path = "", 
		int _push = 0, int _walk = 0);
	// copy constructor
	MazeVertex(const MazeVertex& ref);

	int pty();		// use in heapup, heapdown
	int pty2();		// use in heapup, heapdown. 
					// to compare the number of times a user walked when the box was pushed the same.

	// friend class
	friend class Maze;
};

class Maze
{
public:
	// Constructor
	Maze(int row, int col);

	// Destructor
	~Maze();

	void create_maze();			// create maze with user input
	void init_mark();			// init mark as false

	void bfs();					// find the shortest path and print

	// only for debugging
	void show_maze();			// show maze structure
private:
	char** adjMatrix;			// Maze structure
	bool**** mark;				// Visited history. 
	int max_row, max_col;		// size of maze
	PtyQueue<MazeVertex>* q;	// priority queue

	// special index
	Point user;		// position of user
	Point box;		// position of box
	Point target;	// not change after init

	// 방향 주의
	Point direct[4] = { Point(0, 1), Point(0, -1), Point(-1, 0), Point(1, 0)};	// 사방탐색
	string push_path = "EWNS";	// direction of pushing box
	string walk_path = "ewns";	// direction of user walks

	void visit(Point _box, Point _user);			// visit vertex

	// check condition
	bool check(Point pt) const;						// matrix range check
	bool is_path(Point pt) const;					// path check
	bool is_visit(Point _box, Point _user) const;	// confirmation of visit
	bool can_push(Point _box, Point _user_next) const;	// return if user can push the box
};

