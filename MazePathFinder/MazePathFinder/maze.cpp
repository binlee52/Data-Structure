#include "maze.h"

// Constructor
Maze::Maze(int row, int col)
{
	max_row = row;
	max_col = col;
	adjMatrix = new int[max_row * max_col];
	makeMaze();
}

// Destructor
Maze::~Maze()
{
	delete[] adjMatrix;
}

// access to dege like 2D array
int& Maze::edge(int row, int col)
{
	return adjMatrix[row * max_row + col];
}

// show Maze
void Maze::showMaze()
{
	cout << endl;
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_row; j++)
		{
			if (edge(i, j) == INF)
				cout << "бс ";
			else if (edge(i, j) == USER)
				cout << "S ";
			else if (edge(i, j) == BOX)
				cout << "B ";
			else
				cout << edge(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// make Maze with user's input
void Maze::makeMaze()
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