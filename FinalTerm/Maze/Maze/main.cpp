#include <iostream>
#include "maze.h"
using namespace std;

int main(void)
{
	int game = 1;
	int x, y;
	while (1)
	{
		cin >> x >> y;
		if (x <= 0 || y <= 0)
			break;
		Maze maze(x, y);

		cout << "\nMaze #" << game << endl;
		maze.bfs();
		cout << endl;
		game++;
	}
	system("pause");
}
