#include "maze.h"
#include <tuple>
#include <iomanip>

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
			{
				cout.setf(ios::left);
				cout << setw(4) << "-";
			}
			else if (Point(i, j) == user)
			{
				cout << "S";
				cout.setf(ios::left);
				cout << setw(3) << edge(i, j);
			}
			else if (Point(i, j) == box)
			{
				cout << "B";
				cout.setf(ios::left);
				cout << setw(3) << edge(i, j);
			}
			else if (Point(i, j) == target)
			{
				cout << "T";
				cout.setf(ios::left);
				cout << setw(3) << edge(i, j);
			}
			else
			{
				cout.setf(ios::left);
				cout << setw(4) << edge(i, j);
			}
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
void Maze::bfs(Point start, Point end)
{
	bool found = false;
	Point cur_pos;
	int cur_row, cur_col;
	queue.clear();
	queue.enqueue(start);
	visit(start.row, start.col);
	while (!queue.empty() && !found)
	{ 
		cur_pos = queue.dequeue();
		if (Point(cur_pos.row, cur_pos.col) == end)
		{
			found = true;
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			cur_row = cur_pos.row + direct[i][0];
			cur_col = cur_pos.col + direct[i][1];
			if (check(cur_row, cur_col) && is_path(cur_row, cur_col) && !is_visit(cur_row, cur_col))
			{
				queue.enqueue(Point(cur_row, cur_col));
				edge(cur_row, cur_col) += edge(cur_pos.row, cur_pos.col);
				visit(cur_row, cur_col);
			}
		}
	}
	init_mark();	// initialize visitd
}

// BFS maze box
void Maze::user_bfs(Point start, Point end)
{
	bool found = false;
	Point cur_pos;
	int cur_row, cur_col;
	queue.clear();
	queue.enqueue(start);
	visit(start.row, start.col);
	while (!queue.empty() && !found)
	{
		cur_pos = queue.dequeue();
		if (Point(cur_pos.row, cur_pos.col) == end)
		{
			found = true;
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			cur_row = cur_pos.row + direct[i][0];
			cur_col = cur_pos.col + direct[i][1];
			if (check(cur_row, cur_col) && is_path(cur_row, cur_col) && !is_visit(cur_row, cur_col))
			{
				Point temp = Point(cur_row, cur_col);
				if (temp != box)
				{
					queue.enqueue(temp);
					edge(cur_row, cur_col) += edge(cur_pos.row, cur_pos.col);
					visit(cur_row, cur_col);
				}
			}
		}
	}
	init_mark();	// initialize visitd
}

// backtrace
void Maze::backtrace(Point start, Point end)
{
	Point cur_pos = end;
	int next_row, next_col;
	int cur_weight;
	bool flag;
	stack.push(end);

	while (cur_pos != start)
	{
		cur_weight = edge(cur_pos.row, cur_pos.col);
		flag = false;

		for (int i = 0; (i < 4 && !flag); i++)	// 사방탐색
		{
			next_row = cur_pos.row + direct[i][0];
			next_col = cur_pos.col + direct[i][1];
			if (check(next_row, next_col) && is_path(next_row, next_col)
				&& (cur_weight - 1 == edge(next_row, next_col))) // cur_weight보다 next_weight이 1 작을 때
			{
					cur_pos = Point(next_row, next_col);
					stack.push(cur_pos);
					flag = true;
			}
		}
	}
	init_adjMatrix();
	/**
	// Only for Debugging
	while (!stack.empty())
	{
		Point p = stack.pop();
		cout << "(" << p.row << "," << p.col << ") ";
	}
	**/
}


// user backtrace
void Maze::user_backtrace(Point start, Point end)
{
	Point cur_pos = end;
	int next_row, next_col;
	int cur_weight;
	bool flag;
	edge(box.row, box.col) = INF;
	user_stack.push(end);
	while (cur_pos != start)
	{
		cur_weight = edge(cur_pos.row, cur_pos.col);
		flag = false;

		for (int i = 0; (i < 4 && !flag); i++)	// 사방탐색
		{
			next_row = cur_pos.row + direct[i][0];
			next_col = cur_pos.col + direct[i][1];
			if (check(next_row, next_col) && is_path(next_row, next_col)
				&& (cur_weight - 1 == edge(next_row, next_col))) // cur_weight보다 next_weight이 1 작을 때
			{
				cur_pos = Point(next_row, next_col);
				if (cur_pos != box && cur_pos != start)
				{
					user_stack.push(cur_pos);
					flag = true;
				}
			}
		}
	}
	init_adjMatrix();
	edge(box.row, box.col) = 1;
	/**
	// Only for Debugging
	while (!user_stack.empty())
	{
		Point p = user_stack.pop();
		cout << "(" << p.row << "," << p.col << ") ";
	}
	**/
}

void Maze::move()
{
	
	bfs(box, target);
	backtrace(box, target);

	box = stack.pop();
	Point next_pos;
	Point target_pos;
	Point box_back;

	while (!stack.empty())
	{
		next_pos = stack.pop();
		while ((box * 2 - user == next_pos) && !stack.empty())
		{
			cout << "[" << user.row << "," << user.col << "] ";
			user = box;
			box = next_pos;
			next_pos = stack.pop();
			if (box * 2 - user != next_pos)
				cout << "[" << user.row << "," << user.col << "] ";				
		}
		edge(user.row, user.col) = 0;
		target_pos = box * 2 - next_pos;
		cout << "\n\nBefore BFS" << endl;
		show_maze();
		user_bfs(user, target_pos);
		cout << "After BFS" << endl;
		show_maze();
		user_backtrace(user, target_pos);
		edge(box.row, box.col) = 1;

		// Only for Debugging
		// print user_stack

		target_pos = box * 2 - next_pos;
		if (target_pos != next_pos)
		{
			while (!user_stack.empty())
			{
				Point p = user_stack.pop();
				cout << "(" << p.row << "," << p.col << ") ";
			}
			user = box;
			box = next_pos;
		}
		if (stack.empty())
			cout << "[" << user.row << "," << user.col << "] ";
	}
}

// init mark as false
void Maze::init_mark()
{
	for (int i = 0; i < max_row; i++)
		for (int j = 0; j < max_col; j++)
			visited(i, j) = false;
}

// init adjMatrix as 1;
void Maze::init_adjMatrix()
{
	for (int i = 0; i < max_row; i++)
		for (int j = 0; j < max_col; j++)
			if (edge(i, j) != INF)
				edge(i, j) = 1;
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

