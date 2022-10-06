#pragma once

//Heap node
class heapNode {
    int d; //priority
    int vertex; //value

    friend class max_heap;
public:
    heapNode(int vertex = 0, int d = 0) : vertex(vertex), d(d) {}; //c'tor
    heapNode& operator=(heapNode other) { vertex = other.vertex; d = other.d; return *this; }; //Copy assignment operator
    int getV() { return vertex; } //Returns the vertex
};
