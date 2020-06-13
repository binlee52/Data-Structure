#include <iostream>
#include "maze.h"
using namespace std;

int main(void)
{
	int x, y;
	cout << "ROW/COL : ";
	cin >> x >> y;
	Maze maze(x, y);
	maze.show_maze();

	maze.bfs();
	maze.show_maze();
}
