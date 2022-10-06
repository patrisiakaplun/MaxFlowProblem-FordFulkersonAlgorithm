#pragma once
#include "graph.h"

using namespace std;

class fordF
{
	graph gf;
	int* d = nullptr; //An array of the path length/path weight from the start vertex to all vertices
	int* p = nullptr; //An array of the parents of the vertices in the route
	int maxflow = 0; //The maximum flow in the network
	vector<int> s; //The vertices belonging to the group S in the min cut
	vector<int> t; //The vertices belonging to the group T in the min cut
private:	
	void findMinCut();  //Finds the min cut
	void initPath(int* path, int size);//Initializing the path
public:
	fordF(graph g) : gf(g) { d = new int[g.getSize()]; p = new int[g.getSize()];}; //c'tor
	~fordF() { delete[]p; delete[]d; } //d'tor
	void runfordFBFS(graph& g); //BFS Method
	void runfordG(graph& g); //Greedy Method
	void printMaxflowMinCut(); //Prints the max flow and min cut
};

