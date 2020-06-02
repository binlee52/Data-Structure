#include "wtgraph.h"

using namespace std;

WtGraph::WtGraph(int maxNumber) throw (bad_alloc)
	: maxSize(maxNumber)
{
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize*maxSize];
	mark = new bool[maxSize];
}

WtGraph::~WtGraph()
{
	delete[] vertexList;
	delete[] adjMatrix;
	delete[] mark;
}

// Insert vertex
void WtGraph::insertVertex(Vertex newVertex) throw (logic_error)
{
	if (!isFull())
	{
		vertexList[size] = newVertex;		// insert into vertex List
		for (int i = 0; i <= size; i++)		// set edge as default value(not connected)
		{
			edge(size, i) = infiniteEdgeWt;
			edge(i, size) = infiniteEdgeWt;
		}
		size++;
	}
	else
		cout << "Graph is Full." << endl;
}

// Insert edge
void WtGraph::insertEdge(char* v1, char* v2, int wt) throw (logic_error)
{
	int row = getIndex(v1);	// get v1's index if v1 is in Vertex List, if not, return -1
	int col = getIndex(v2); // get v2's index if v1 is in Vertex List, if not, return -1
	if (isIndex(row, col))
		setEdge(row, col, wt);
	else
		cout << v1 << " or " << v2 << " is not in Graph." << endl;
}

// return true or false if v is in vertextList. store data in vData
bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
	if (!isEmpty())
	{
		for (int i = 0; i < size; i++)
			if (!strcmp(vertexList[i].label, v))
			{
				vData = vertexList[i];	// store as reference
				return true;
			}
	}
	return false;
}

// Remove vertex
void WtGraph::removeVertex(char* v) throw (logic_error)
{
	int row = getIndex(v);
	if (!isEmpty() && isIndex(row))
	{
		// delete vertex in vertex list
		for (int i = row; i < size - 1; i++)
			vertexList[i] = vertexList[i + 1];

		// vertex가 포함된 모든 edge 삭제
		for (int i = row; i < size - 1; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					edge(i, j) = edge(i + 1, j + 1);
				else
				{
					edge(i, j) = edge(i + 1, j);
					edge(j, i) = edge(j, i + 1);
				}
			}
		}
		size--;
	}
	else
		cout << v << " is not in Graph." << endl;
}

// Remove Edge
void WtGraph::removeEdge(char* v1, char* v2) throw (logic_error)
{
	int temp = 0;
	int row = getIndex(v1);
	int col = getIndex(v2);
	if (isIndex(row, col))
	{
		temp = getEdge(row, col);
		setEdge(row, col, infiniteEdgeWt); // delete edge between v1, v2
	}
	if (temp == infiniteEdgeWt) // if no edge between v1, v2
		cout << "No edge between " << v1 << " and " << v2 << endl;
}

// Get edge wt
bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt) throw (logic_error)
{
	int row = getIndex(v1);
	int col = getIndex(v2);
	if (isIndex(row, col))
	{
		wt = getEdge(row, col);
		return true;
	}
	return false;
}

// Converts vertex label to and adjacency matrix index
int WtGraph::getIndex(char* v)
{
	if (!isEmpty())
	{
		for (int i = 0; i < size; i++)
			if (!strcmp(vertexList[i].label, v))
				return i;
	}
	return -1;	// if v is not in Graph
}

// Get dege weight using
int WtGraph::getEdge(int row, int col)
{
	return edge(row, col);
}

// Set edge weight using
void WtGraph::setEdge(int row, int col, int wt)
{
	edge(row, col) = wt;
	edge(col, row) = wt;
}

// clear Graph
void WtGraph::clear()
{
	size = 0;
}

void WtGraph::clearMark()
{
	for (int i = 0; i < maxSize; i++)
		mark[i] = false;
}

// Graph status operations
bool WtGraph::isEmpty() const                            // Graph is empty
{
	return size == 0;
}

bool WtGraph::isFull() const                             // Graph is full
{
	return size == maxSize;
}

bool WtGraph::isIndex(int row) const
{
	return row != -1;
}

bool WtGraph::isIndex(int row, int col) const
{
	return (isIndex(row) && isIndex(col));
}

int& WtGraph::edge(int row, int col) {    // access to edge like 2D array
	return adjMatrix[maxSize * row + col];
}

bool WtGraph::hasProperColoring()
{
	if (!isEmpty())
	{
		char color1, color2;
		for (int i = 0; i < size; i++)
		{
			color1 = vertexList[i].color;
			for (int j = i; j < size; j++)
			{
				if (getEdge(i, j) != infiniteEdgeWt)	// 간선이 존재할 때
				{
					color2 = vertexList[j].color;	// 인접 vertex color
					if (color1 == color2)
						return false;
				}
			}
		}
	}
	return true;
}

bool WtGraph::areAllEven()
{
	if (!isEmpty())
	{
		int cnt;
		for (int i = 0; i < size; i++)
		{
			cnt = 0;
			for (int j = 0; j < size; j++)
			{
				if (edge(i, j) != infiniteEdgeWt)	// 간선이 존재할 때
					cnt++;
			}
			if (cnt % 2 != 0)	// 간선이 홀수일 때
				return false;
		}
	}
	return true;
}