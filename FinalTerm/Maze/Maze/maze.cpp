#include "maze.h"

MazeVertex::MazeVertex(Point _box, Point _user, string _path, int _push, int _walk)
/**
	Constructor of MazeVertex Class
**/
	: box(_box), user(_user), path(_path), push_cnt(_push), walk_cnt(_walk)
{}

MazeVertex::MazeVertex(const MazeVertex& ref)
/**
	Copy Constructor of MazeVertex Class
**/
{
	box = ref.box;
	user = ref.user;
	path = ref.path;
	push_cnt = ref.push_cnt;
	walk_cnt = ref.walk_cnt;
}

int MazeVertex::pty()
/**
	Return push_cnt. 
	To give priority according to the number of push in the priority
**/
{
	// maxheap을 사용하므로 minheap처럼 사용하기 위해 -1
	return (-1) * push_cnt;
}

int MazeVertex::pty2()
/**
	Return walk_cnt. 
	To compare priorities when pty() is the same in the priority queue.
**/
{
	// maxheap을 사용하므로 minheap처럼 사용하기 위해 -1
	return (-1) * walk_cnt;
}

Maze::Maze(int row, int col)
/**
	Constructor of Maze class
**/
{
	max_row = row;
	max_col = col;

	// init adjMatrix
	adjMatrix = new char*[max_row];
	for (int i = 0; i < max_row; i++)
		adjMatrix[i] = new char[max_col];
	create_maze();

	// init mark
	mark = new bool***[max_row];
	for (int i = 0; i < max_row; i++)
	{
		mark[i] = new bool**[max_col];
		for (int j = 0; j < max_col; j++)
		{
			mark[i][j] = new bool*[max_row];
			for (int k = 0; k < max_row; k++)
			{
				mark[i][j][k] = new bool[max_col];
			}
		}
	}
	init_mark();

	// Space is wasted if not worst case, because it is implemented in an array.
	q = new PtyQueue<MazeVertex>(3 * max_row * max_col);		// Queue for BFS
}

void Maze::create_maze()
/**
	Create maze based on user input
**/
{
	char input;
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_col; j++)
		{
			cin >> input;
			if (input == '#')
				adjMatrix[i][j] = '#';
			else if (input == '.')
				adjMatrix[i][j] = '.';
			else if (input == 's' || input == 'S')
			{
				adjMatrix[i][j] = 'S';
				user.set(i, j);
			}
			else if (input == 'T' || input == 't')
			{
				adjMatrix[i][j] = 'T';
				target.set(i, j);
			}
			else if (input == 'b' || input == 'B')
			{
				adjMatrix[i][j] = 'B';
				box.set(i, j);
			}
			else
				// exception
			{
				cout << "Wrong Input \'" << input << "\'" << endl;
				cout << "Game OFF" << endl;
				exit(1);
				system("pause");
			}
		}
	}
}

void Maze::init_mark()
/**
	Initializing visit status(mark).
**/
{
	for (int i = 0; i < max_row; i++)
		for (int j = 0; j < max_col; j++)
			for (int k = 0; k < max_row; k++)
				for (int l = 0; l < max_col; l++)
					mark[i][j][k][l] = false;
}

Maze::~Maze()
/**
	Destructor of Maze class.
**/
{
	// deallocate adjMatrix(maze structure)
	for (int i = 0; i < max_row; i++)
		delete[] adjMatrix[i];
	delete[] adjMatrix;

	// deallocate mark(visited history)
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_col; j++)
		{
			for (int k = 0; k < max_row; k++)
			{
				delete[] mark[i][j][k];
			}
			delete[] mark[i][j];
		}
		delete[] mark[i];
	}
	delete[] mark;
}

// Only for debugging
void Maze::show_maze()
{
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_col; j++)
		{
			cout << adjMatrix[i][j];
		}
		cout << endl;
	}
}

bool Maze::check(Point pt) const
/** 
	Verify that the point is in range of matrix.
	return true if in, or false.
**/
{
	if (pt.row >= 0 && pt.row < max_row && pt.col >= 0 && pt.col < max_col)
		return true;
	return false;
}

bool Maze::is_path(Point pt) const
/**
	check path.
	return false if wall(#) else true
**/
{
	if (adjMatrix[pt.row][pt.col] == '#')
		return false;
	return true;
}

bool Maze::is_visit(Point _box, Point _user) const
{
	return mark[_box.row][_box.col][_user.row][_user.col];
}

void Maze::visit(Point _box, Point _user)
/**
	Visit according to the relative location of the box and user
**/
{
	mark[_box.row][_box.col][_user.row][_user.col] = true;
}

bool Maze::can_push(Point _box, Point _user_next) const
/** 
	Returns true if the following location of the user matches the box position.
	If user is far from box, return false. 
**/
{
	return _box == _user_next;
}

void Maze::bfs()
/**
	Calculate the shortest path using the BFS algorithm. 
	If path is found, the path is printed out. 
	If path is not found, the output is "impossible".
**/
{
	MazeVertex cur_loc;
	MazeVertex next_loc;
	Point box_next;
	Point user_next;
	string path_next;
	bool flag = true;

	q->enqueue(MazeVertex(box, user));	// start

	while (!q->isEmpty())
	{
		cur_loc = q->dequeue();

		// When the box arrived at the target,
		if (cur_loc.box == target)
		{
			cout << cur_loc.path << endl;;
			return;
		}

		// Exploring all directions(East, West, North, South)
		for (int i = 0; i < 4; i++)
		{
			user_next = cur_loc.user + direct[i];
			box_next = cur_loc.box + direct[i];

			if (check(user_next) && is_path(user_next) && !is_visit(cur_loc.box, user_next))
			{
				// When the next position of the user is the box(if user can push the box)
				if (can_push(cur_loc.box, user_next))
				{
					if (check(box_next) && is_path(box_next))
					{
						path_next = cur_loc.path + push_path[i];	// update path
						next_loc = MazeVertex(box_next, user_next, path_next, cur_loc.push_cnt + 1, cur_loc.walk_cnt);
						q->enqueue(next_loc);
						visit(box_next, user_next);
					}
					// When the next position of the box is out of range or is a rock,
					// do nothing.
				}
				// if user can not push the box
				else
				{
					path_next = cur_loc.path + walk_path[i];	// update path
					next_loc = MazeVertex(cur_loc.box, user_next, path_next, cur_loc.push_cnt, cur_loc.walk_cnt + 1);
					q->enqueue(next_loc);
					visit(cur_loc.box, user_next);
				}
			}
		}
	}
	cout << "Impossible!" << endl;
}