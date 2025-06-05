//
// Created by Jan Tlaga on 3/28/25.
//

#ifndef AIZO_281198_GENERATEARR_H
#define AIZO_281198_GENERATEARR_H

#include "test.h"
#include <iostream>
#include <cstdint>
#include <random>
#include <cstdio>
//typy generowania wartosci i sortowania
enum genSort {
    GEN_RANDOM,
    GEN_RANDOM_33,
    GEN_RANDOM_66,
    GEN_SORTED,
    GEN_SORTED_DESC,
    GEN_SORT_COUNT
};

/* createArray{type}
* tworzy tablice o rozmiarze n okreslonego typu
*/
int * createArrayInt(uint32_t n);
float* createArrayFloat(uint32_t n);


void generateType(int *A, uint32_t n, int min, int max, std::mt19937* rng, genSort genType);

void generateType(float *A, uint32_t n, float min, float max, std::mt19937* rng, genSort genType);

/*generateRandom
 *wstawia do tablicy A, losowe wartosci o okreslonym przedziale
 *n - rozmiar tablicy
 *min - minimalna wartosc
 *max - maksymalna wartosc
 *rng - wskaznik do funkcji generujacej wartosci losowe
*/
void generateRandom(int* A, uint32_t n, int min, int max, std::mt19937* rng);
void generateRandom(float* A, uint32_t n, float min, float max,std::mt19937* rng);

/*generateRandomPartiallySorted
 *partPrecent procent w jakim poczatek tablicy od 0 do floor(n*partPrecent) ma byc posortowany
*/
void generateRandomPartiallySorted(int *A, uint32_t n,
        int min, int max, float partPrecent, std::mt19937 *rng);        
void generateRandomPartiallySorted(float *A, uint32_t n, 
    float min, float max, float partPrecent, std::mt19937 *rng);

void parseInt(const char* str, void* out);
void parseFloat(const char* str, void* out);


/*generateSort
 * generate random and then sort insc
*/
void generateSort(int *A, uint32_t n, int min, int max, std::mt19937* rng);
void generateSort(float *A, uint32_t n, float min, float max, std::mt19937* rng);

/*generateSort
 * generate random and then sort insc
*/
void generateSortDesc(int *A, uint32_t n, int min, int max, std::mt19937* rng);
void generateSortDesc(float *A, uint32_t n, float min, float max, std::mt19937* rng);




/*readArrayFromFile
 * czyta tablice z pliku, gdzie pierwsza liczba oznacza liczbe elementow
 */
void *readArrayFromFile(const char*fileName, uint32_t* outSize, 
        uint32_t typeSize, void (*parseFunc)(const char*, void*));


#endif //AIZO_281198_GENERATEARR_H

