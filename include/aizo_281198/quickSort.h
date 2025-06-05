//
// Created by Jan Tlaga on 3/21/25.
//

#ifndef AIZO_281198_QUICKSORT_H
#define AIZO_281198_QUICKSORT_H
#include <iostream>
#include <cstdint>

/* quickSort{Type}
 * sortowanie tablicy za pomoca sortowania szybkiego o okreslonym typie
 */
void quickSortLeft(int *A, uint32_t n);
void quickSortLeft(float *A, uint32_t n);

void quickSortMiddle(int *A, uint32_t n);
void quickSortMiddle(float *A, uint32_t n);

void quickSortRight(int *A, uint32_t n);
void quickSortRight(float *A, uint32_t n);

void quickSortRandom(int *A, uint32_t n);
void quickSortRandom(float *A, uint32_t n);


#endif //AIZO_281198_QUICKSORT_H
