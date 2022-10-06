#pragma once
#include <iostream>
#include <vector>
#include "heapNode.h"

using namespace std;

//updatable Max Heap implemented by vector
class max_heap{
    vector<heapNode> data;
    int heapSize = 0;
    vector<int> vertexIndex;
private:
    void fixHeap(int node); //Fixes the heap that has node as root
    void moveUp(int index); //swaps upeards after increasing the value
    int getLeft(int node) { return (2 * node + 1); }
    int getRight(int node) { return (2 * node + 2); }
    int parent(int node) { return (node - 1) / 2; }
public:
    max_heap(){} //Make Empty heap
    max_heap(heapNode a[], int size); // Turn A into heap
    heapNode max() { return data[0];} // Returns maximum value
    heapNode deleteMax(); // Returns and deletes the maximum value
    void insert(heapNode item); // Insert new node and swap upwards
    void build(int size, int* arr); //build heap from int d[n] , Intended to be used for the Dijksta algorithm
    void increaseKey(int vertex, int d); //Updates the old value of the node to the larger new value
    int getHeapSize() { return heapSize; } //Get heap size
};

