//
// Created by Jan Tlaga on 3/21/25.
//

#include "../include/aizo_281198/quickSort.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
// typ wyboru pivota
enum PivotType { LEFT, MIDDLE, RIGHT, RANDOM };

/* partition
 * Podzial na wartosci mniejsze od piwota i wieksze rowne od piwota
 * pivotType - okresla typ woboru pivota
 */
uint32_t partition(int *A, int left, int right, PivotType pivotType) {
    int p_i;
    switch (pivotType) {
        case LEFT:
            p_i = left;
            break;
        case MIDDLE:
            p_i = (left + right) / 2;
            break;
        case RIGHT:
            p_i = right;
            break;
        case RANDOM:
            p_i = left + rand() % (right - left + 1);
            break;
    }
    int pivot = A[p_i];
    std::swap(A[p_i], A[right]);
    int j = left;
    for (int i = left; i < right; i++) {
        if (A[i] < pivot) {
            std::swap(A[i], A[j]);
            j++;
        }
    }
    std::swap(A[j], A[right]);
    return j;
}
uint32_t partition(float *A, int left, int right, PivotType pivotType) {
    int p_i;
    switch (pivotType) {
        case LEFT:
            p_i = left;
            break;
        case MIDDLE:
            p_i = (left + right) / 2;
            break;
        case RIGHT:
            p_i = right;
            break;
        case RANDOM:
            p_i = left + rand() % (right - left + 1);
            break;
    }
    float pivot = A[p_i];
    std::swap(A[p_i], A[right]);
    int j = left;
    for (int i = left; i < right; i++) {
        if (A[i] < pivot) {
            std::swap(A[i], A[j]);
            j++;
        }
    }
    std::swap(A[j], A[right]);
    return j;
}

/* quickSort{
 * sortowanie tablicy za pomoca sortowania szybkiego o okreslonym typie
 * pivotType - typ sortowania
 */
void quickSort(int *A, int left, int right, PivotType pivotType) {
    if (left < right) {
        int p_i = partition(A, left, right, pivotType);
        quickSort(A, left, p_i - 1, pivotType);
        quickSort(A, p_i + 1, right, pivotType);
    }
}

void quickSortLeft(int *A, uint32_t n) {
    quickSort(A, 0, n - 1, LEFT);
}
void quickSortMiddle(int *A, uint32_t n) {
    quickSort(A, 0, n - 1, MIDDLE);
}
void quickSortRight(int *A, uint32_t n) {
    quickSort(A, 0, n - 1, RIGHT);
}
void quickSortRandom(int *A, uint32_t n) {
    quickSort(A, 0, n - 1, RANDOM);
}

void quickSort(float *A, int left, int right, PivotType pivotType) {
    if (left < right) {
        int p_i = partition(A, left, right, pivotType);
        quickSort(A, left, p_i - 1, pivotType);
        quickSort(A, p_i + 1, right, pivotType);
    }
}
/* quickSort{Type}
 * sortowanie tablicy za pomoca sortowania szybkiego o okreslonym typie
 */
void quickSortLeft(float *A, uint32_t n) {
    quickSort(A, 0, n - 1, LEFT);
}
void quickSortMiddle(float *A, uint32_t n) {
    quickSort(A, 0, n - 1, MIDDLE);
}
void quickSortRight(float *A, uint32_t n) {
    quickSort(A, 0, n - 1, RIGHT);
}
void quickSortRandom(float *A, uint32_t n) {
    quickSort(A, 0, n - 1, RANDOM);
}

