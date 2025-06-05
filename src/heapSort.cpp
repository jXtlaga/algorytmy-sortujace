//
// Created by Jan Tlaga on 3/21/25.
//
#include <cstdint>

#include "../include/aizo_281198/heapSort.h"
uint32_t getParent(uint32_t i){
    return ((i +1) >> 1) - 1;
}
uint32_t getLeft(uint32_t i){
    return ((i + 1) << 1) - 1;
}
uint32_t getRight(uint32_t i){
    return (i+1) << 1;
}
/* przywracanie wlasnoci kopca typu max typu Int lub typu float*/
void maxHeapifyInt(int *A, uint32_t i, uint32_t n){
    uint32_t largest = i;
    uint32_t left = getLeft(i);
    uint32_t right = getRight(i);

    if (left < n && A[left] > A[i]) largest = left;
    if (right < n && A[right] > A[largest]) largest = right;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapifyInt(A, largest, n);
    }
}

void maxHeapifyFloat(float *A, uint32_t i, uint32_t n){
    uint32_t largest = i;
    uint32_t left = getLeft(i);
    uint32_t right = getRight(i);

    if (left < n && A[left] > A[i]) largest = left;
    if (right < n && A[right] > A[largest]) largest = right;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapifyFloat(A, largest, n);
    }
}
/*budowanie kopca typu max typu int lub float*/
void buildMaxHeapInt(int *A, uint32_t n){
    uint32_t heapSize = n;
    for (int i = (int)((n+1)>>1)-1; i >= 0; i--){
        maxHeapifyInt(A, i, n);
    }
}
void buildMaxHeapFloat(float *A, uint32_t n){
    uint32_t heapSize = n;
    for (int i = (int)((n+1)>>1)-1; i >= 0; i--){
        maxHeapifyFloat(A, i, n);
    }
}
/*sortowanie przez kopcowanie*/
void heapSort(int *A, uint32_t n){
    int from = (n >> 1) - 1;
    for (int i = from; i >= 0; i--){
        maxHeapifyInt(A, i, n);
    }
    for (int i = (int)n - 1; i > 0; i--){
        std::swap(A[0], A[n - 1]);
        n--;
        maxHeapifyInt(A, 0, n);
    }
}

void heapSort(float *A, uint32_t n){
    int from = (n >> 1) - 1;
    for (int i = from; i >= 0; i--){
        maxHeapifyFloat(A, i, n);
    }
    for (int i = (int)n - 1; i > 0; i--){
        std::swap(A[0], A[n - 1]);
        n--;
        maxHeapifyFloat(A, 0, n);
    }
}
