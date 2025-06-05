//
// Created by Jan Tlaga on 3/21/25.
//

#ifndef AIZO_281198_SHELLSORT_H
#define AIZO_281198_SHELLSORT_H
#include <iostream>
#include <cstdint>

/*shellSortTypeShell
 * Sortowanie shella z podstawowym ciagiem, opisanym w pierwszym artykule 
 * dot. tego sortowania przez Shella
 */
void shellSortTypeShell(int *A, uint32_t n);
void shellSortTypeShell(float *A, uint32_t n);


/*shellSortTypeKnuth
 * Sortowanie shella z ciagiem Knutha 
 */
void shellSortTypeKnuth(int *A, uint32_t n);
void shellSortTypeKnuth(float *A, uint32_t n);
#endif //AIZO_281198_SHELLSORT_H
