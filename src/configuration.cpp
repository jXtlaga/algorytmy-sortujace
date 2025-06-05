#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <cstdio>
#include "../include/aizo_281198/heapSort.h"
#include "../include/aizo_281198/quickSort.h"
#include "../include/aizo_281198/shellSort.h"
#include "../include/aizo_281198/insertSort.h"
#include <string.h>
#include "../include/aizo_281198/parseRead.h"
/* SortTypeNames
 * tablica nazw typów sortowania, używana do wypisywania wyników
 */
const char* SortTypeNames[] = {
    "Insert Sort",
    "Heap Sort",
    "Quick Sort (left)",
    "Quick Sort (middle)",
    "Quick Sort (right)",
    "Quick Sort (random)",
    "Shell Sort (Shell)",
    "Shell Sort (Knuth)"
};

/* GenTypeNames
 * tablica nazw typów generowania tablic
 */
const char* GenTypeNames[] = {
    "gen Random",
    "gen Random 33",
    "gen Random 66",
    "gen Sorted",
    "gen sorted desc"
};

/* funcPointerFloat
 * tablica wskaźników na funkcje sortujące float
 */
void (*funcPointerFloat[])(float *, uint32_t)= {
    &insertSort, &heapSort, &quickSortLeft, &quickSortMiddle, &quickSortRight,
    &quickSortRandom, &shellSortTypeShell, &shellSortTypeKnuth
};

/* funcPointerInt
 * tablica wskaźników na funkcje sortujące int
 */
void (*funcPointerInt[])(int *, uint32_t)= {
    &insertSort, &heapSort, &quickSortLeft, &quickSortMiddle, &quickSortRight,
    &quickSortRandom, &shellSortTypeShell, &shellSortTypeKnuth
};

/* sortTypeMap
 * mapowanie tekstu na enum SortType
 */
EnumEntry sortTypeMap[] = {
    {"INSERT_SORT", INSERT_SORT},
    {"HEAP_SORT", HEAP_SORT},
    {"QUICK_SORT_LEFT", QUICK_SORT_LEFT},
    {"QUICK_SORT_MIDDLE", QUICK_SORT_MIDDLE},
    {"QUICK_SORT_RIGHT", QUICK_SORT_RIGHT},
    {"QUICK_SORT_RANDOM", QUICK_SORT_RANDOM},
    {"SHELL_SORT_SHELL", SHELL_SORT_SHELL},
    {"SHELL_SORT_KNUTH", SHELL_SORT_KNUTH},
    {nullptr, SORT_TYPE_COUNT}
};

/* ArrTypeMap
 * mapowanie tekstu na enum ArrType
 */
EnumEntry ArrTypeMap[] = {
    {"ARR_RAND", ARR_RAND},
    {"ARR_RAND_33", ARR_RAND_33},
    {"ARR_RAND_66", ARR_RAND_66},
    {"ARR_SORT", ARR_SORT},
    {"ARR_SORT_DESC", ARR_SORT_DESC},
    {nullptr, ARR_TYPE_COUNT}
};

/* fileTypeMap
 * mapowanie typu pliku na enum VarType
 */
EnumEntry fileTypeMap[] = {
    {"INT", INT},
    {"FLOAT", FLOAT},
    {nullptr, VAR_TYPE_COUNT}
};

/* addToArr
 * dodaje nowy element do dynamicznej tablicy (realloc co 8 elementów)
 */
void addToArr(int** arr, uint32_t* size, int value) {
    int current_capacity = ((*size / 8) + 1) * 8;

    if (*size == 0) {
        *arr = (int*) malloc(current_capacity * sizeof(int));
        if (!*arr) {
            perror("malloc");
            exit(1);
        }
    } else if (*size % 8 == 0) {
        int* temp = (int*) realloc(*arr, current_capacity * sizeof(int));
        if (!temp) {
            perror("realloc");
            free(*arr);
            exit(1);
        }
        *arr = temp;
    }

    (*arr)[(*size)++] = value;
}

/* mapStringToEnum
 * zamienia tekst (np. z pliku konfiguracyjnego) na wartość enuma
 */
int mapStringToEnum(const char* line, const EnumEntry* map, int invalidValue) {
    char cleanLine[128];
    strncpy(cleanLine, line, sizeof(cleanLine));
    cleanLine[sizeof(cleanLine)-1] = '\0';
    char* newline = strchr(cleanLine, '\n');
    if (newline) *newline = '\0';

    for (int i = 0; map[i].name != nullptr; i++) {
        if (strcmp(cleanLine, map[i].name) == 0) {
            return map[i].value;
        }
    }

    return invalidValue;
}

/* Funkcje parserów odpowiednich sekcji konfiguracyjnych */

bool parseArrInt(const char* line, Config* config) {
    int val = mapStringToEnum(line, ArrTypeMap, ARR_TYPE_COUNT);
    if (val != ARR_TYPE_COUNT) {
        addToArr(&config->arrayTypeInt, &config->arrayTypeCountInt, val);
        return true;
    }
    return false;
}

bool parseSizeInt(const char* line, Config* config) {
    int val;
    bool correct = parsePositiveInt(line, &val);
    if (correct) {
        addToArr(&config->arraySizeInt, &config->arraySizeCountInt, val);
        return true;
    }
    return false;
}

bool parseSortInt(const char* line, Config* config) {
    int val = mapStringToEnum(line, sortTypeMap, SORT_TYPE_COUNT);
    if (val != SORT_TYPE_COUNT) {
        addToArr(&config->sortTypeInt, &config->sortTypeCountInt, val);
        return true;
    }
    return false;
}

bool parseArrFloat(const char* line, Config* config) {
    int val = mapStringToEnum(line, ArrTypeMap, ARR_TYPE_COUNT);
    if (val != ARR_TYPE_COUNT) {
        addToArr(&config->arrayTypeFloat, &config->arrayTypeCountFloat, val);
        return true;
    }
    return false;
}

bool parseSizeFloat(const char* line, Config* config) {
    int val;
    bool correct = parsePositiveInt(line, &val);
    if (correct) {
        addToArr(&config->arraySizeFloat, &config->arraySizeCountFloat, val);
        return true;
    }
    return false;
}

bool parseSortFloat(const char* line, Config* config) {
    int val = mapStringToEnum(line, sortTypeMap, SORT_TYPE_COUNT);
    if (val != SORT_TYPE_COUNT) {
        addToArr(&config->sortTypeFloat, &config->sortTypeCountFloat, val);
        return true;
    }
    return false;
}

bool parseFileType(const char* line, Config* config) {
    int val = mapStringToEnum(line, fileTypeMap, VAR_TYPE_COUNT);
    if (val != VAR_TYPE_COUNT) {
        config->fileType = val;
        return true;
    }
    return false;
}

bool parseSortFile(const char* line, Config* config) {
    int val = mapStringToEnum(line, sortTypeMap, SORT_TYPE_COUNT);
    if (val != SORT_TYPE_COUNT) {
        addToArr(&config->sortTypeFile, &config->sortTypeCountFile, val);
        return true;
    }
    return false;
}

bool parseFileInName(const char* line, Config* config) {
    config->fileNameIn = strdup(line);
    return config->fileNameIn != nullptr;
}

bool parseFileOutName(const char* line, Config* config) {
    config->fileNameOut = strdup(line);
    return config->fileNameOut != nullptr;
}

bool parseConsoleOut(const char* line, Config* config) {
    char* ifOut = strdup(line);
    if (strcmp(ifOut, "FALSE") == 0) {
        config->consoleOut = false;
    }
    free(ifOut);
    return true;
}

/* configParsers
 * tablica parserów przypisanych do sekcji pliku konfiguracyjnego
 */
ConfigParserEntry configParsers[] = {
    { CONF_ARR_INT,        ".ARR_INT",        parseArrInt },
    { CONF_ARR_SIZE_INT,   ".ARR_SIZE_INT",   parseSizeInt },
    { CONF_SORT_INT,       ".SORT_INT",       parseSortInt },
    { CONF_ARR_FLOAT,      ".ARR_FLOAT",      parseArrFloat },
    { CONF_ARR_SIZE_FLOAT, ".ARR_SIZE_FLOAT", parseSizeFloat },
    { CONF_SORT_FLOAT,     ".SORT_FLOAT",     parseSortFloat },
    { CONF_FILE_IN,        ".FILE_IN",        parseFileInName },
    { CONF_FILE_TYPE,      ".FILE_TYPE",      parseFileType },
    { CONF_SORT_FILE,      ".SORT_FILE",      parseSortFile },
    { CONF_FILE_OUT,       ".FILE_OUT",       parseFileOutName },
    { CONF_CONSOLE_OUT,    ".CONSOLE_OUT",    parseConsoleOut },
    { CONF_NONE,           nullptr,           nullptr }
};

/* getConfigSection
 * sprawdza czy linia rozpoczyna nową sekcję konfiguracyjną
 */
configType getConfigSection(const char* line) {
    configType currentSection = CONF_NONE;
    for (int i = 0; configParsers[i].sectionName != nullptr; i++) {
        if (strcmp(line, configParsers[i].sectionName) == 0) {
            return configParsers[i].section;
        }
    }
    return CONF_NONE;
}

/* readConfig
 * czyta plik konfiguracyjny i uzupełnia strukturę Config
 */
void readConfig(const char* filename, Config* config) {
    FILE* file = openFile(filename);
    if (!file) {
        std::cerr << "Cannot open config file\n" << std::endl;
        exit(1);
    }
    char buffor[1024];
    configType actConf = CONF_NONE;

    while (fgets(buffor, sizeof(buffor), file)) {
        stripNewline(buffor);
        if (buffor[0] == '\0') continue;
        if (buffor[0] == '.' || buffor[0] == '#') {
            actConf = getConfigSection(buffor);
        } else if (actConf != CONF_NONE) {
            for (int i = 0; configParsers[i].sectionName != nullptr; i++) {
                if (configParsers[i].section == actConf) {
                    configParsers[i].parseFunc(buffor, config);
                    break;
                }
            }
        }
    }
    fclose(file);
}

/* printArray
 * wypisuje zawartość tablicy liczb całkowitych
 */
void printArray(const int* arr, uint32_t count, const char* label) {
    std::cout << label << " (" << count << "): ";
    for (uint32_t i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

/* printConfig
 * wypisuje aktualną konfigurację wczytaną do programu
 */
void printConfig(const Config* cfg) {
    printf("=== CONFIG ===\n");

    printArray(cfg->arrayTypeInt, cfg->arrayTypeCountInt, "ArrayTypeInt");
    printArray(cfg->arrayTypeFloat, cfg->arrayTypeCountFloat, "ArrayTypeFloat");

    printArray(cfg->arraySizeInt, cfg->arraySizeCountInt, "ArraySizeInt");
    printArray(cfg->arraySizeFloat, cfg->arraySizeCountFloat, "ArraySizeFloat");

    printArray(cfg->sortTypeInt, cfg->sortTypeCountInt, "SortTypeInt");
    printArray(cfg->sortTypeFloat, cfg->sortTypeCountFloat, "SortTypeFloat");
    printArray(cfg->sortTypeFile, cfg->sortTypeCountFile, "SortTypeFile");

    printf("FileNameIn: %s\n", cfg->fileNameIn ? cfg->fileNameIn : "(null)");

    printf("FileType: ");
    if (cfg->fileType == INT) printf("int\n");
    else if (cfg->fileType == FLOAT) printf("float\n");
    else printf("none\n");

    printf("FileNameOut: %s\n", cfg->fileNameOut ? cfg->fileNameOut : "(null)");
    printf("ConsoleOut: %s\n", cfg->consoleOut ? "true" : "false");
}

