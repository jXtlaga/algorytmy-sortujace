#include <cstdint>
#include <random>
#include <stdio.h>
#include <cstdio>
#include "include/aizo_281198/test.h"
#include "./include/aizo_281198/configuration.h"

//uruchomienie konfiguracji
void runConfig(const Config* cfg){
    printf("\n=== RUN CONFIG ===\n");
    if(cfg->arraySizeCountInt != 0 && cfg->arrayTypeCountInt != 0 && cfg->sortTypeCountInt != 0){
        fullTestInt(cfg);
    }
    if(cfg->arraySizeCountFloat != 0 && cfg->arrayTypeCountFloat != 0 && cfg->sortTypeCountFloat != 0){
        fullTestFloat(cfg);
    }
    if(cfg->fileNameIn && cfg->fileType == INT){
        fullTestFileInt(cfg);
    }
    if(cfg->fileNameIn && cfg->fileType == FLOAT){
        fullTestFileFloat(cfg);
    }
}
int main() {
    //ustawienie ziarna
    std::random_device rd;
    uint32_t seed = rd();
    std::mt19937 rng(seed);
    //wczytanie konfiguracji
    Config config;
    readConfig("./config.txt", &config);
    printConfig(&config);
    //uruchomienie konfiguracji
    runConfig(&config);
    return 0;
}
