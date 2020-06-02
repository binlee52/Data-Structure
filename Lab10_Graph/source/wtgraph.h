//--------------------------------------------------------------------
//
//  Laboratory 13                                          wtgraph.h
//
//  Class declaration for the adjacency matrix implementation of
//  the Weighted Graph ADT
//
//--------------------------------------------------------------------

#include <climits>    // For INT_MAX
#include <new>
#include <stdexcept>
#include <iostream>

using namespace std;

const int defMaxGraphSize = 10,      // Default number of vertices
          vertexLabelLength = 11,    // Length of a vertex label
          infiniteEdgeWt = INT_MAX;  // "Weight" of a missing edge

//--------------------------------------------------------------------

class Vertex
{
  public:

    char label [vertexLabelLength];   // Vertex label
    // (In-lab2 member variable)
    char color;           // Vertex color ('r' for red and so forth)
};

//--------------------------------------------------------------------

class WtGraph
{
private:

    // Facilitator functions
    int getIndex(char* v);                  // Converts vertex label to an
                                               //   adjacency matrix index

    int getEdge(int row, int col);          // Get edge weight using
                                               //   adjacency matrix indices
    void setEdge(int row, int col, int wt);  // Set edge weight using   // 2차원 배열로 생성
                                               //   adjacency matrix indices
    int& edge(int row, int col);

    // Data members
    int maxSize,          // Maximum number of vertices in the graph
        size;             // Actual number of vertices in the graph
    Vertex* vertexList;   // Vertex list    // 1차원 배열로 구현
    int* adjMatrix;       // Adjacency matrix   // 2차원 배열
    bool* mark;           // visit flag

public:

    // Constructor
    WtGraph ( int maxNumber = defMaxGraphSize )
        throw ( bad_alloc );

    // Destructor
    ~WtGraph ();

    // Graph manipulation operations
    void insertVertex ( Vertex newVertex )            // Insert vertex
        throw ( logic_error );
    void insertEdge ( char *v1, char *v2, int wt )    // Insert edge
        throw ( logic_error );
    bool retrieveVertex ( char *v, Vertex &vData ); // 검색결과 true false 출력, data에 찾은 참조로 저장
                                                      // Get vertex
    bool getEdgeWeight ( char *v1, char *v2, int &wt )  // wt에 결과 true false 대입, 검색결과 삽입
        throw ( logic_error );                        // Get edge wt.
    void removeVertex ( char *v )                     // Remove vertex
        throw ( logic_error );
    void removeEdge ( char *v1, char *v2 )            // Remove edge
        throw ( logic_error );
    void clear ();                                    // Clear graph
    void clearMark();
    // Graph status operations
    bool isEmpty () const;                            // Graph is empty
    bool isFull () const;                             // Graph is full
    bool isIndex(int row) const;
    bool isIndex(int row, int col) const;                             // is Vertex in Graph
    // Output the graph structure -- used in testing/debugging
    void showStructure ();

    // In-lab operation
    bool hasProperColoring();
    bool areAllEven ();
};
