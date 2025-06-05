 //
// Created by Jan Tlaga on 3/27/25.
//

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <cstdio>
#include "../include/aizo_281198/parseRead.h"
/*funkcje pomocnicze w parsowaniu tekstu lub edycji tekstu*/
void stripNewline(char* str) {
    char* p = strchr(str, '\n');
    if (p) *p = '\0';
}

bool parsePositiveInt(const char* str, int* out) {
    char* endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val <= 0 || val > INT32_MAX) return false;
    *out = (int)val;
    return true;
}

bool parsePositiveFloat(const char* str, float* out) {
    char* endptr;
    errno = 0;
    float val = strtof(str, &endptr);
    if (errno != 0 || *endptr != '\0' || val <= 0.0f) return false;
    *out = val;
    return true;
}
FILE* openFile(const char* fileName, const char* mode) {
    FILE* file = fopen(fileName, mode);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << fileName << std::endl;
        return nullptr;
    }
    return file;
}
