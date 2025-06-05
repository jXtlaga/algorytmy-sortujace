//
// Created by Jan Tlaga on 3/21/25.
//

#ifndef AIZO_281198_TEST_H
#define AIZO_281198_TEST_H
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>
#include "configuration.h"
/* testFunction
 * generuje losowa tablice
 * sprawdza poprawnosc posortowania
 * wyswietla 10 elementow przed sortowaniem i po sortowaniu
*/
void testFunction(uint32_t n, void (*sortFunc)(int *, uint32_t), int min, int max, std::mt19937* rng);
void testFunction(uint32_t n, void (*sortFunc)(float *, uint32_t), float min, float max, std::mt19937* rng);

/*timeTest
 * zlicza czas wykonania algorytmu sortowania za pomoca chrono::highresolution_clock
 * zwraca (double) czas wykonania w ms
 */
double timeTest(int *A, uint32_t n, void (*sortFunc)(int *, uint32_t));
double timeTest(float *A, uint32_t n, void (*sortFunc)(float*, uint32_t));


int fullTestInt(const Config* cfg);
int fullTestFloat(const Config* cfg);
int fullTestFileInt(const Config* cfg);
int fullTestFileFloat(const Config* cfg);




/*printArray
 * wyswietla tablice
 */
template <typename T>
void printArray(T *A, uint32_t n){
    for(int i = 0; i < n; i++){
        std::cout << A[i] << " ";
    }
    std::cout<<std::endl;
}


/*printArrayTo
 * wyswietla tablice do okreslonego indeksu
 */
template <typename T>
void printArrayTo(T *A, uint32_t n, uint32_t to){
    for(int i = 0; i < n; i++){
        if(i == to) break;
        std::cout << A[i] << " ";
    }
    std::cout<<std::endl;
}

/* checkSort
 * sprawdza poprawnosc posortowanej tablicy uzywajac zaimportowanej biblioteki z sortowaniem
 * jesli tablica jest posortowana nie poprawnie wyswietla komunikat i zwraca false
 * jestli jest posortowana poprawnie nie wyswietla komunikatu i zwraca true
 */
template <typename T>
bool checkSort(T *A, uint32_t n) {
    T *A_copy = new T[n];
    std::copy(A, A + n, A_copy);
    std::sort(A_copy, A_copy + n);

    bool isSorted = std::equal(A, A + n, A_copy);
    delete[] A_copy;
    if (isSorted) {
 	   //std::cout << "Tablica jest poprawnie posortowana." << std::endl;
    } else {
        std::cout << "Tablica NIE jest poprawnie posortowana." << std::endl;
    }
    return isSorted;
}
#endif //AIZO_281198_TEST_H
