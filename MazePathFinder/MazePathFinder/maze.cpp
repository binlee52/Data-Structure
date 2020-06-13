#include "maze.h"

// Constructor
Maze::Maze(int row, int col)
{
	max_row = row;
	max_col = col;
	adjMatrix = new int[max_row * max_col];
	mark = new bool[max_row * max_col];	// TODO __int32()
	make_maze();
	init_mark();
}

// Destructor
Maze::~Maze()
{
	delete[] adjMatrix;
	delete[] mark;
}

// show Maze
void Maze::show_maze()
{
	cout << endl;
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_col; j++)
		{
			if (edge(i, j) == INF)
				cout << "бс  ";
			else if (Point(i, j) == user)
				cout << "S" << edge(i, j) <<" ";
			else if (Point(i, j) == box)
				cout << "B" << edge(i, j) << " ";
			else if (Point(i, j) == target)
				cout << "T" << edge(i, j) << " ";
			else
				cout << edge(i, j) << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

// make Maze with user's input
void Maze::make_maze()
{
	char input;
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_col; j++)
		{
			cin >> input;
			if (input == '#')
				edge(i, j) = INF;
			else if (input == '.')
				edge(i, j) = 1;
			else if (input == 's' || input == 'S')
			{
				edge(i, j) = USER;	// starting point
				user.set(i, j);
			}
			else if (input == 'T' || input == 't')
			{
				edge(i, j) = 1;
				target.set(i, j);
			}
			else if (input == 'b' || input == 'B')
			{
				edge(i, j) = BOX; // box point
				box.set(i, j);
			}
			else
				// exception
			{
				cout << "Wrong Input \'" << input << "\'"<< endl;
				cout << "Game OFF" << endl;
				exit(1);
				system("pause");
			}
		}
	}
}

// BFS maze box
void Maze::bfs()
{
	Point cur_pos;
	int cur_row, cur_col;
	q.enqueue(box);
	visit(box.row, box.col);
	while (!q.empty())
	{ 
		cur_pos = q.dequeue();
		/**
		if (Point(cur_pos.row, cur_pos.col) == target)
			break;
		**/
		for (int i = 0; i < 4; i++)
		{
			cur_row = cur_pos.row + direct[i][0];
			cur_col = cur_pos.col + direct[i][1];
			if (check(cur_row, cur_col) && is_path(cur_row, cur_col) && !is_visit(cur_row, cur_col))
			{
				q.enqueue(Point(cur_row, cur_col));
				edge(cur_row, cur_col) += edge(cur_pos.row, cur_pos.col);
				visit(cur_row, cur_col);
			}
		}
	}
}

// init mark as false
void Maze::init_mark()
{
	for (int i = 0; i < max_row; i++)
		for (int j = 0; j < max_col; j++)
			visited(i, j) = false;
}

// access to edge like 2D array
int& Maze::edge(int row, int col)
{
	return adjMatrix[row * max_col + col];
}

// access to mark like 2D array
bool& Maze::visited(int row, int col)
{
	return mark[row * max_col + col];
}


/*** check condition ***/
// matrix range check
bool Maze::check(int row, int col) const
{
	if (row >= 0 && row < max_row && col >= 0 && col < max_col)
		return true;
	return false;
}

// path check
bool Maze::is_path(int row, int col) const
{
	if (adjMatrix[row * max_col + col] == INF)
		return false;
	return true;
}

// confirmation of visit
bool Maze::is_visit(int row, int col) const
{
	if (check(row, col))
		return mark[row * max_col + col];
	else
	{
		cout << "Func is_visit error (" << row << "," << col << ")" << endl;
		exit(1);
	}
}

void Maze::visit(int row, int col)
{
	if (check(row, col))
		visited(row, col) = true;
}

