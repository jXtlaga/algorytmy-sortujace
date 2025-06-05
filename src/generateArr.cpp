//
// Created by Jan Tlaga on 3/21/25.
//
#include <cstdio>
#include <functional>
#include <iostream>
#include <cstdint>
#include <random>
#include <algorithm>
#include "../include/aizo_281198/generateArr.h"
#include "../include/aizo_281198/parseRead.h"


/*generateType
* wpisuje wartosci do tablicy w okreslony sposob (genType)
*/
void generateType(int *A, uint32_t n, int min, int max, std::mt19937* rng, genSort genType) {
    switch(genType){
        case GEN_RANDOM:
            generateRandom(A, n, min, max, rng);
            break;
        case GEN_RANDOM_33:
            generateRandomPartiallySorted(A, n, min, max, 0.33f, rng);
            break;
        case GEN_RANDOM_66:
            generateRandomPartiallySorted(A, n, min, max, 0.66f, rng);
            break;
        case GEN_SORTED:
            generateSort(A, n, min, max, rng);
            break;
        case GEN_SORTED_DESC:
            generateSortDesc(A, n, min, max, rng);
            break;
        default:
            std::cerr << "Nieznany typ generacji" << std::endl;
            break;
    }
}

void generateType(float *A, uint32_t n, float min, float max, std::mt19937* rng, genSort genType) {
    switch(genType){
        case GEN_RANDOM:
            generateRandom(A, n, min, max, rng);
            break;
        case GEN_RANDOM_33:
            generateRandomPartiallySorted(A, n, min, max, 0.33f, rng);
            break;
        case GEN_RANDOM_66:
            generateRandomPartiallySorted(A, n, min, max, 0.66f, rng);
            break;
        case GEN_SORTED:
            generateSort(A, n, min, max, rng);
            break;
        case GEN_SORTED_DESC:
            generateSortDesc(A, n, min, max, rng);
            break;
        default:
            std::cerr << "Nieznany typ generacji" << std::endl;
            break;
    }
}

/* createArray{type}
* tworzy tablice o rozmiarze n okreslonego typu
*/
int * createArrayInt(uint32_t n){
    int *A = (int *)malloc(n * sizeof(int));
    return A;
}
float* createArrayFloat(uint32_t n){
    float *A = (float *)malloc(n * sizeof(float ));
    return A;
}
/*generateRandom
 *wstawia do tablicy A, losowe wartosci o okreslonym przedziale
 *n - rozmiar tablicy
 *min - minimalna wartosc
 *max - maksymalna wartosc
 *rng - wskaznik do funkcji generujacej wartosci losowe
*/
void generateRandom(int* A, uint32_t n, int min, int max, std::mt19937* rng) {

    if(!rng) {
        std::cout<<"not generated random, because rng is null"<<std::endl;
        return;
    }
	std::uniform_int_distribution<int> dist(min, max);
	for (size_t i = 0; i < n; ++i) {
		A[i] = dist(*rng);
	}
}
void generateRandom(float* A, uint32_t n, float min, float max, std::mt19937* rng) {
    if(!rng) {
        std::cout<<"not generated random, because rng is null"<<std::endl;
        return;
    }

    std::uniform_real_distribution<float> dist(min, max);

    for (size_t i = 0; i < n; ++i) {
        A[i] = dist(*rng);
    }

}

/*generateRandomPartiallySorted
 *partPrecent procent w jakim poczatek tablicy od 0 do floor(n*partPrecent) ma byc posortowany
*/
void generateRandomPartiallySorted(int *A, uint32_t n, 
    int min, int max, float partPrecent, 
    std::mt19937 *rng){
	generateRandom(A, n, min, max, rng);
    uint32_t part = n * partPrecent;
    if(part > 0 && part < n){
        std::sort(A, A + part);
    }
}
void generateRandomPartiallySorted(float *A, uint32_t n, 
    float min, float max, float partPrecent, 
    std::mt19937 *rng){
	generateRandom(A, n, min, max, rng);
    uint32_t part = n * partPrecent;
    if(part > 0 && part < n){
        std::sort(A, A + part);
    }
}
void parseInt(const char* str, void* out) {
    *(int*)out = atoi(str);
}

void parseFloat(const char* str, void* out) {
    *(float*)out = strtof(str, nullptr);
}
/*generateSort
 * generate random and then sort insc
*/
void generateSort(int *A, uint32_t n, int min, int max, std::mt19937* rng){
    generateRandom(A, n, min, max, rng);
    std::sort(A, A+n);
}
void generateSort(float *A, uint32_t n, float min, float max, std::mt19937* rng){
    generateRandom(A, n, min, max, rng);
    std::sort(A, A+n);
}
/*generateSort
 * generate random and then sort insc
*/
void generateSortDesc(int *A, uint32_t n, int min, int max, std::mt19937* rng){
    generateRandom(A, n, min, max, rng);
    std::sort(A, A+n, std::greater<int>());
}
void generateSortDesc(float *A, uint32_t n, float min, float max, std::mt19937* rng){
    generateRandom(A, n, min, max, rng);
    std::sort(A, A+n, std::greater<float>());
}
  
/*readArrayFromFile
 * czyta tablice z pliku, gdzie pierwsza liczba oznacza liczbe elementow
 */
void* readArrayFromFile(const char*fileName, uint32_t* outSize, 
        uint32_t typeSize, void (*parseFunc)(const char*, void*)){
    FILE* file = fopen(fileName, "r");
    if (!file){
        std::cout<<"cannot open the file\n";
        return nullptr;
    }
    size_t size;
    if (fscanf(file, "%zu", &size) != 1) {
        std::cout<<"Cannot read array size\n";
        fclose(file);
        return nullptr;
    }
    void* array = malloc(size * typeSize);
    if (!array) {
        std::cout<<"Cannot alocate memory\n";
        fclose(file);
        return nullptr;
    }
    char buffer[100];
    for (uint32_t i = 0; i < size; ++i) {
        if (fscanf(file, "%s", buffer) != 1) {
            std::cout<<"Cannot read element\n";
            free(array);
            fclose(file);
            return nullptr;
        }
        parseFunc(buffer, (char*)array + i * typeSize);
    }

    fclose(file);
    *outSize = size;
    return array;
}

