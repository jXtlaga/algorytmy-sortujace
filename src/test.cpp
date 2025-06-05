//
// Created by Jan Tlaga on 3/28/25.
//
#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>
#include "../include/aizo_281198/test.h"
#include "../include/aizo_281198/generateArr.h"
#include "../include/aizo_281198/configuration.h"
#include "../include/aizo_281198/parseRead.h"

/* testFunction
 * generuje losowa tablice
 * sprawdza poprawnosc posortowania
 * wyswietla 10 elementow przed sortowaniem i po sortowaniu
*/
void testFunction(uint32_t n, void (*sortFunc)(int *, uint32_t), int min, int max, std::mt19937* rng) {
    printf("#############################################################\n");
    int *A = createArrayInt(n);
    generateRandom(A, n, min, max, rng);
    printf("przed sortowaniem pierwsze %d elementow\n\t", 10);
    printArrayTo(A, n, 10);
    sortFunc(A, n);
    printf("po sortowaniu pierwsze %d elementow\n\t", 10);
    printArrayTo(A, n, 10);
    checkSort(A, n);
    free(A);
    printf("#############################################################\n");
}


/* testFunction
 * generuje losowa tablice
 * sprawdza poprawnosc posortowania
 * wyswietla 10 elementow przed sortowaniem i po sortowaniu
*/
void testFunction(uint32_t n, void (*sortFunc)(float *, uint32_t), float min, float max, std::mt19937* rng) {
    printf("#############################################################\n");
    float *A = createArrayFloat(n);
    generateRandom(A, n, min, max, rng);
    printf("przed sortowaniem pierwsze %d elementow\n\t", 10);
    printArrayTo(A, n, 10);
    sortFunc(A, n);
    printf("po sortowaniu pierwsze %d elementow\n\t", 10);
    printArrayTo(A, n, 10);
    checkSort(A, n);
    free(A);
    printf("#############################################################\n");
}

/*time Test
 * dla okreslonego sortowania(argument) zwraca czas tego sortowania*/
double timeTest(int *A, uint32_t n, void (*sortFunc)(int *, uint32_t)){
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(A, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    return time.count();
}
double timeTest(float *A, uint32_t n, void (*sortFunc)(float*, uint32_t)){
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(A, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    return time.count();
}


/*funckje testujace posortowanie tablvy
 * uruchamiaja sortowanie z okreslonych argumentow konfiguracji
 * oblicza sredni czas wykonania sortowania dla 100 powtorzen
 * dodatkowo jesli w konfiguracji sa okresloe argumenty:
 * wyswietla informacje o sortowaniu
 * zapisuje do pliku
 */
int fullTestInt(const Config* cfg){
    std::random_device rd;
    uint32_t seed = rd();
    std::mt19937 rng(seed);
    FILE *file; 
    if(cfg->fileNameOut != nullptr){
        file = openFile(cfg->fileNameOut, "a");
    }
    for(int sortTypeCfgInd = 0; sortTypeCfgInd < cfg->sortTypeCountInt; sortTypeCfgInd++)
    {
        rng.seed(seed);
        for (int sizeCfgInd = 0; sizeCfgInd < cfg->arraySizeCountInt; sizeCfgInd ++){
            for (int genCfgInd = 0; genCfgInd < cfg->arrayTypeCountInt; genCfgInd ++){
                
                double sumTime = 0;
                int size = cfg->arraySizeInt[sizeCfgInd];
                uint32_t sortType = cfg->sortTypeInt[sortTypeCfgInd];
                uint32_t genType = cfg->arrayTypeInt[genCfgInd];

                for(int j = 0; j < 100; j++){
                    int *A = createArrayInt(size);
                    generateType(A, size, INT32_MIN, INT32_MAX, &rng, static_cast<genSort>(genType));
                    sumTime += timeTest(A, size, funcPointerInt[sortType]);
                
                    checkSort(A, size);
                    free(A);
                    }
                
                double mean = sumTime/100.;
                if(cfg->consoleOut){
                    printf("--------------\n");
                    printf("%s\n", SortTypeNames[sortType]);
                    printf("%s\n", GenTypeNames[genType]);
                    printf("size: %d\n", size);
                    printf("type: INT\n");
                    printf("mean time: %.6f\n\n", mean);
                } 
                if(file != nullptr) {
                    fprintf(file, "%s,%s,%d,%e,INT\n",SortTypeNames[sortType], GenTypeNames[genType], size, mean);
                }
            }
        }
    }
    if(file) fclose(file);
    return 0;
}
int fullTestFloat(const Config* cfg) {
    std::random_device rd;
    uint32_t seed = rd();
    std::mt19937 rng(seed);
    FILE *file; 
    if(cfg->fileNameOut != nullptr){
        file = openFile(cfg->fileNameOut, "a");
    }
    for (int sortTypeCfgInd = 0; sortTypeCfgInd < cfg->sortTypeCountFloat; sortTypeCfgInd++) {
        rng.seed(seed);
        for (int sizeCfgInd = 0; sizeCfgInd < cfg->arraySizeCountFloat; sizeCfgInd++) {
            for (int genCfgInd = 0; genCfgInd < cfg->arrayTypeCountFloat; genCfgInd++) {
                double sumTime = 0.0;
                int size = cfg->arraySizeFloat[sizeCfgInd];
                uint32_t sortType = cfg->sortTypeFloat[sortTypeCfgInd];
                uint32_t genType = cfg->arrayTypeFloat[genCfgInd];
                for (int j = 0; j < 100; j++) {
                    float* A = createArrayFloat(size);
                    
                    generateType(A, size, -10000, 10000, &rng, static_cast<genSort>(genType));
                    sumTime += timeTest(A, size, funcPointerFloat[sortType]);
                     
                    checkSort(A, size);
                    free(A);
                }
                double mean = sumTime / 100.0;
                if(cfg->consoleOut == true){
                    printf("-------------------\n");
                    printf("%s\n", SortTypeNames[sortType]);
                    printf("%s\n", GenTypeNames[genType]);
                    printf("size: %d\n", size);
                    printf("type: FLOAT\n");
                    printf("mean time: %.6f\n\n", mean);
                }
                if(file != nullptr) {
                    fprintf(file, "%s,%s,%d,%e,FLOAT\n",SortTypeNames[sortType], GenTypeNames[genType], size, mean);
                } 
            }
        }
    }
    if(file != nullptr) fclose(file);
    return 0;
}
int fullTestFileInt(const Config* cfg) {


    FILE* fileOut = nullptr;
    

    uint32_t sizeArr = 0;
    int* dataOrig = (int*)readArrayFromFile(cfg->fileNameIn, &sizeArr, sizeof(int), parseInt);
    if (!dataOrig) {
        return 0;
    }
    
    for (int sortTypeInd = 0; sortTypeInd < cfg->sortTypeCountFile; sortTypeInd++) {
        double sumTime = 0.0;
        int* data = (int*)malloc(sizeArr * sizeof(int));

        memcpy(data, dataOrig, sizeArr * sizeof(int));
        uint32_t sortType = cfg->sortTypeFile[sortTypeInd];
        funcPointerInt[sortType](data,sizeArr);
        checkSort(data, sizeArr);
         
        if (cfg->consoleOut) {
            printf("--------------\n");
            printf("PRZED SORTOWANIEM:\n");
            printArrayTo(dataOrig, sizeArr, 20);
            printf("%s\n", SortTypeNames[sortType]);
            printf("size: %u\n", sizeArr);
            printf("type: INT\n");
            printf("tablica po sortowaniu:\n");
            printArrayTo(data, sizeArr,20);
        }
       free(data);

    }

    free(dataOrig);
    if (fileOut) fclose(fileOut);
    return 0;
}

int fullTestFileFloat(const Config* cfg) {
    FILE* fileOut = nullptr;

    uint32_t sizeArr = 0;
    float* dataOrig = (float*)readArrayFromFile(cfg->fileNameIn, &sizeArr, sizeof(float), parseFloat);
    if (!dataOrig) {
        return 0;
    }

        for (int sortTypeInd = 0; sortTypeInd < cfg->sortTypeCountFile; sortTypeInd++) {
        double sumTime = 0.0;
        float* data = (float*)malloc(sizeArr * sizeof(float));
        if (!data) continue;

        memcpy(data, dataOrig, sizeArr * sizeof(float));

        uint32_t sortType = cfg->sortTypeFile[sortTypeInd];
        funcPointerFloat[sortType](data, sizeArr);
        checkSort(data, sizeArr);

        if (cfg->consoleOut) {
            printf("--------------\n");
            printf("PRZED SORTOWANIEM:\n");
            printArrayTo(dataOrig, sizeArr, 20);

            printf("%s\n", SortTypeNames[sortType]);
            printf("size: %u\n", sizeArr);
            printf("type: FLOAT\n");
            printf("tablica po sortowaniu:\n");
            printArrayTo(data, sizeArr, 20); 
        }

      
        free(data);
    }

    free(dataOrig);
    if (fileOut) fclose(fileOut);
    return 0;
}



