#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    //Helping functions go here
    static void reheapDown(T *maxHeap, int numberOfElements, int index)
{
    while (index < numberOfElements) {
        int child = index*2 + 1;
        if (child >= numberOfElements) return;
        if (child + 1 < numberOfElements) 
            if (maxHeap[child] < maxHeap[child + 1]) child++;
        if (maxHeap[child] <= maxHeap[index]) return;
        T temp = maxHeap[index];
        maxHeap[index] = maxHeap[child];
        maxHeap[child] = temp;
        index = child;
}
}

static void reheapUp(T *maxHeap, int numberOfElements, int index)
{
    while (index) {
        int par = (index - 1) / 2;
        if (maxHeap[index] < maxHeap[par]) return;
        T temp = maxHeap[index];
        maxHeap[index] = maxHeap[par];
        maxHeap[par] = temp;
        index = par;
    }
}
static void buildHeap(T* p, int N) {
    for (int i = 1; i <N; i++) reheapUp(p, N, i);
}
static void heapSort(T* start, T* end){
    //TODO
    if (start < end - 1) {
        int N = end - start;
        buildHeap(start, N);
        for (int i = N - 1; i > 0; i--) {
            T temp = start[0];
            start[0] = start[i];
            start[i] = temp;
            reheapDown(start, i, 0);
    }
    }
    Sorting<T>::printArray(start,end);
}
    
};
#endif /* SORTING_H */
int main() {
    priority_queue<int> pq;
    pq

}