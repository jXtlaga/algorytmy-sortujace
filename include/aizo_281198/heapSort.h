//
// Created by Jan Tlaga on 3/21/25.
//

#ifndef AIZO_281198_HEAPSORT_H
#define AIZO_281198_HEAPSORT_H
#include "test.h"
#include <iostream>
#include <cstdint>
/*maxHeapify
 *przywracanie wlasnosci kopca
 */
void maxHeapify(int *A, uint32_t i, uint32_t n);
void buildMaxHeap(float *A, uint32_t n);
/*buildMaxHeap
 * tworzenie kopca typu max
 */
void buildMaxHeap(int *A, uint32_t n);
void maxHeapify(float *A, uint32_t i, uint32_t n);

/* heapSort
 * sortowanie tablicy, czescia sortowania jest uzycie metody buildMaxHeap
 */
void heapSort(int *A, uint32_t n);
void heapSort(float *A, uint32_t n);

#endif //AIZO_281198_HEAPSORT_H
