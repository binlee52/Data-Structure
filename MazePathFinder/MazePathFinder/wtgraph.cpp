#include "wtgraph.h"

using namespace std;

WtGraph::WtGraph(int maxNumber) throw (bad_alloc)
	: maxSize(maxNumber)
{
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize * maxSize];
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
void WtGraph::insertEdge(int row, int col, int wt) throw (logic_error)
{
	if (isIndex(row, col))
		setEdge(row, col, wt);
	else
		cout << row << " or " << col << " is not in Graph." << endl;
}

// Remove vertex
void WtGraph::removeVertex(int row, int col) throw (logic_error)
{
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
		cout << row << " is not in Graph." << endl;
}

// Remove Edge
void WtGraph::removeEdge(int row, int col) throw (logic_error)
{
	int temp = 0;
	if (isIndex(row, col))
	{
		temp = getEdge(row, col);
		setEdge(row, col, infiniteEdgeWt); // delete edge between v1, v2
	}
	if (temp == infiniteEdgeWt) // if no edge between v1, v2
		cout << "No edge between " << row << " and " << col << endl;
}

// Get edge wt
bool WtGraph::getEdgeWeight(int row, int col, int& wt) throw (logic_error)
{
	if (isIndex(row, col))
	{
		wt = getEdge(row, col);
		return true;
	}
	return false;
}

// Get edge weight using
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