#pragma once
#include "adjacent.h"
#include "max_heap.h"
#include <iostream>
#include<list>
#include <vector>
#include <queue>
#include <tuple>

enum { INF = 2147483647 , MINUS_INF = -2147483647 , NULL_PTR = 0};

using namespace std;

class graph
{
	vector<list<adjacent>> verticas;
	int size = 0;
	int s = 0;
	int t = 0;
public:
	graph() {}; //default c'tor
	graph(graph& g); //copy c'tor
	int getSize() { return size; };//Returns the num of verticas
	int getS() { return s; };//Returns s
	int getT() { return t; };//Returns t
	void getGraph();//Get graph from user
	void makeEmptyGraph(int n);//Make empty graph
	list<adjacent> getAdjList(int u); //Return sort adj list
	void addEdge(int u, int v, int c);//Adds a new edge to the graph
	void removeEdge(int u, int v); //Removes edge from the graph

	void dijksta(int* p, int* d); //An Version of Dijkstra's algorithm
	void CapacityUpdate(int* path, graph& g); // Updates the capacity of the edges along the path
	void findPath(int* p,int v, int* arr, int size); //Finds the path by the parent array
	int findMin(int* path); //Finds the min capacity in the path
	void increaseFlow(int* path, int cf); //Increase the flow of the edges along the path
	void bfs(int* p, int* d); //BFS
	int findMaxFlow(); //finds the max flow 
};
	