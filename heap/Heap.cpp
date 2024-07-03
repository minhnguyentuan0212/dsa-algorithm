#include <iostream>
using namespace std;

template <class T>
void headUp(T *pD, size_t idx){
    while (idx){
        size_t pIdx = (idx - 1) / 2;
        if (pD[pIdx] > pD[idx]) return;
        T temp(move(pD[idx]))
        pD[idx] = move(pD[pIdx]);
        pD[pIdx] = move(temp);
        idx = pIdx;
    }
}

template <class T>
void headDown(T *pD, size_t N, size_t idx = 0){
    while(idx < N){
        size_t lIdx = idx * 2 + 1;
        if (lIdx >= N) return;
        if (lIdx + 1 < N){
            if (pD[lIdx] < pD[lIdx+1]) lIdx++;
        }
        if (pD[idx] >= pD[lIdx]) return;
        T temp(move(pD[idx]));
        pD[idx] = move(pD[lIdx]);
        pD[lIdx] = move(temp);
        idx = lIdx;
    }
}

template <class T>
void buildHeap_trivial(T *pD, int N){ // O(Nlog2(N))
    for (int i = 1; i < N; i++) headUp(pD, i);
}

template <class T>
void buildHeap(T *pD, int N){ // O(N)
    for (int i = N / 2; i > -1; i--) heapDown(pD, N, i);
}

template <class T>
void heapSort(T *pD, int N){
    buildHeap_trivial(pD, N); //buildHeap(pD, N);
    for (int i = N - 1; i > 0; i--){
        T temp(move(*pD));
        *pD = move(pD[i])
        pD[i] = move(temp)
        heapDown(pD, i, 0);
    }
}

