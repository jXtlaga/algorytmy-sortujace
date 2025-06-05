//
// Created by Jan Tlaga on 3/27/25.
//

#include "../include/aizo_281198/insertSort.h"
#include <utility>
/*inserSort
 * sortowanie przez wstawianie
 */
void insertSort(int *A, u_int32_t n){
    for(int i = 1; i < n; i++){
        int j = i - 1;
        int temp = A[i];
        while(j > 0 && A[j] > temp){
            std::swap(A[j], A[j+1]);
            j--;
        }
        A[j] = temp;
    }
}
void insertSort(float *A, u_int32_t n){
    for(int i = 1; i < n; i++){
        int j = i - 1;
        float temp = A[i];
        while(j > 0 && A[j] > temp){
            std::swap(A[j], A[j+1]);
            j--;
        }
        A[j] = temp;

    }
}
