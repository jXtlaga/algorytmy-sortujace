 //
// Created by Jan Tlaga on 3/27/25.
//

#ifndef AIZO_281198_PARSEREAD_H
#define AIZO_281198_PARSEREAD_H
#include <iostream>
#include <cstdint>
bool parsePositiveInt(const char* str, int* out);
bool parsePositiveFloat(const char* str, float* out);
void stripNewline(char* str);
FILE* openFile(const char* fileName, const char* mode = "r"); 
#endif //AIZO_281198_
