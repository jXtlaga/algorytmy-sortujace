//
// Created by Jan Tlaga on 3/21/25.
//

#include "../include/aizo_281198/shellSort.h"

/*sortowanie shella roznego typu: Shella lub Knutha*/
void shellSortTypeShell(int *A, uint32_t n){
    uint32_t h = n;
    while(h != 1){
        h = h >> 1;
        for (uint32_t i = h; i < n; i++){
            int temp = A[i];
            uint32_t j = i;
            while(j >= h && temp < A[j-h]){
                std::swap(A[j], A[j-h]);
                j -= h;

            }
            A[j] = temp;
        }
    }
}
void shellSortTypeKnuth(int *A, uint32_t n){
    uint32_t h = 1;
    while (h < n / 3) {
        h = h * 3 + 1;
    }

    while (h >= 1) {
        for (uint32_t i = h; i < n; i++) {
            int temp = A[i];
            uint32_t j = i;
            while (j >= h && temp < A[j - h]) {
                A[j] = A[j - h];
                j -= h;
            }
            A[j] = temp;
        }
        h = h/3;
    }
}

void shellSortTypeShell(float *A, uint32_t n) {
    uint32_t h = n;
    while(h != 1){
        h = h >> 1;
        for (uint32_t i = h; i < n; i++){
            float temp = A[i];
            uint32_t j = i;
            while(j >= h && temp < A[j-h]){
                std::swap(A[j], A[j-h]);
                j -= h;
            }
            A[j] = temp;
        }
    }
}


void shellSortTypeKnuth(float *A, uint32_t n) {
    uint32_t h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while(h >= 1){
        for (uint32_t i = h; i < n; i++){
            float temp = A[i];
            uint32_t j = i;
            while(j >= (int)h && temp < A[j-h]){
                std::swap(A[j], A[j-h]);
                j -= h;
            }
            A[j] = temp;
        }
        h = (h - 1) / 3;
    }
}
