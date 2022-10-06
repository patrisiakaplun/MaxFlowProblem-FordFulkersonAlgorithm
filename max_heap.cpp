#include "max_heap.h"

void max_heap::fixHeap(int node)
{
    int max;
    int left = getLeft(node);
    int right = getRight(node);

    if (left < heapSize && data[left].d > data[node].d)
        max = left;

    else
        max = node;


    if (right < heapSize && data[right].d > data[max].d)
        max = right;

    if (max != node)
    {
        swap(data[node], data[max]);
        swap(vertexIndex[data[node].getV() - 1], vertexIndex[data[max].getV() - 1]);
        fixHeap(max);
    }
}

void max_heap::moveUp(int index)
{
    int i = index;
    heapNode temp;

    while ((i > 0) && (data[parent(i)].d < data[i].d))
    {
        swap(data[parent(i)], data[i]);
        swap(vertexIndex[data[parent(i)].getV() - 1], vertexIndex[data[i].getV() - 1]);
        i = parent(i);
    }
}

max_heap::max_heap(heapNode a[], int size)
{
    heapSize = size;
    copy(a, a + size, data.begin());

    for (int i = size / 2 - 1; i >= 0; i--)
        fixHeap(i);
}

heapNode max_heap::deleteMax()
{
    if (heapSize < 1)
        cout << " eror" << endl;

    heapNode max = data[0];
    heapSize--;
    data[0] = data[heapSize];
    swap(vertexIndex[data[heapSize].getV() - 1], vertexIndex[data[0].getV()- 1]);
    fixHeap(0);
    return max;
}

void max_heap::insert(heapNode item)
{
    int i = heapSize;
    heapSize++;

    while ((i > 0) && (data[parent(i)].d < item.d))
    {
        data[i] = data[parent(i)];
        swap(vertexIndex[data[parent(i)].getV() - 1], vertexIndex[data[i].getV() - 1]);
        i = parent(i);
    }

    data[i] = item;
}

void max_heap::build(int size,int* arr)
{
    for (int i = 0; i < size; i++)
    {
        data.push_back(heapNode(i + 1, arr[i]));
        heapSize++;
        vertexIndex.push_back(i);
    }

    for (int i = heapSize / 2 - 1; i >= 0; i--)
        fixHeap(i);    
}

void max_heap::increaseKey(int vertex, int d)
{
    int index = vertexIndex[vertex - 1];
    data[index].d = d;
    moveUp(index);

}
