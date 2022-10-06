#pragma once

class adjacent
{	
	int vertex;
	int capacity;
	int flow = 0;

	friend class graph;
public:
	static bool compareAdj(const adjacent& first, const adjacent& second); //A method for comparing neighbors for sorting by vertex
	adjacent(int v = 0 , int c = 0) : vertex(v), capacity(c) {}; // c'tor
	int getCapacity() { return capacity; }; //Returns the Capacity
	int getVertex() { return vertex; };//Returns the vertex
	int getFlow() { return flow; }; //Returns the flow
};
