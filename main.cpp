//Operating Instructions:
//To build a graph the user has to insert: n - an integer number of vertices, m - an integer number of arcs, s and t (must be among the existing vertices)
//and arcs where each arc is represented by two vertices and the arc's capacity.
//Running the first method that uses BFS, the method creates the Gf used by the algorithm ,finds the min cut (S and T) and the max flow in the network
//Running the first method that uses Dijksta version, the method creates the Gf used by the algorithm ,finds the min cut (S and T) and the max flow in the network
#include <iostream>
#include "graph.h"
#include"adjacent.h"
#include"fordF.h"

using namespace std;

int main()
{
	graph g;
	g.getGraph();
	
	fordF fordBFS(g);
	fordF fordGreedy(g);

	graph gcopy1(g);
	fordBFS.runfordFBFS(gcopy1);
	cout << "BFS Method:" << endl;
	fordBFS.printMaxflowMinCut();

	graph gcopy2(g);
	fordGreedy.runfordG(gcopy2);
	cout << "Greedy Method:" << endl;
	fordGreedy.printMaxflowMinCut(); 
}