//
// Created by Jan Tlaga on 4/5/25.
//

#ifndef AIZO_281198_CONFIGURATION_H
#define AIZO_281198_CONFIGURATION_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/* Enumy */
enum VarType { INT, FLOAT, VAR_TYPE_COUNT };
enum ArrType { ARR_RAND, ARR_RAND_33, ARR_RAND_66, ARR_SORT, ARR_SORT_DESC, ARR_TYPE_COUNT };
enum SortType {
    INSERT_SORT, HEAP_SORT,
    QUICK_SORT_LEFT, QUICK_SORT_MIDDLE, QUICK_SORT_RIGHT, QUICK_SORT_RANDOM,
    SHELL_SORT_SHELL, SHELL_SORT_KNUTH,
    SORT_TYPE_COUNT
};
enum configType {
    CONF_NONE,
    CONF_ARR_INT, CONF_ARR_FLOAT,
    CONF_ARR_SIZE_INT, CONF_ARR_SIZE_FLOAT,
    CONF_SORT_INT, CONF_SORT_FLOAT,
    CONF_FILE_IN, CONF_FILE_TYPE, CONF_SORT_FILE,
    CONF_FILE_OUT, CONF_CONSOLE_OUT
};

/* EnumEntry
 * struktura pomocnicza: mapa stringów na wartości enum
 */
typedef struct {
    const char* name;
    int value;
} EnumEntry;

/* Config
 * struktura przechowująca wczytaną konfigurację programu
 */
struct Config {
    int* arrayTypeInt = nullptr;
    uint32_t arrayTypeCountInt = 0;
    int* arrayTypeFloat = nullptr;
    uint32_t arrayTypeCountFloat = 0;

    int* arraySizeInt = nullptr;
    uint32_t arraySizeCountInt = 0;

    int* arraySizeFloat = nullptr;
    uint32_t arraySizeCountFloat = 0;

    int* sortTypeInt = nullptr;
    uint32_t sortTypeCountInt = 0;

    int* sortTypeFloat = nullptr;
    uint32_t sortTypeCountFloat = 0;

    int* sortTypeFile = nullptr;
    uint32_t sortTypeCountFile = 0;

    char* fileNameIn = nullptr;
    int fileType = -1;

    char* fileNameOut = nullptr;
    bool consoleOut = true;
};

typedef bool (*ParseFunc)(const char*, Config*);

/* ConfigParserEntry
 * struktura definiująca jedną sekcję parsowania konfiguracji
 */
typedef struct {
    configType section;
    const char* sectionName;
    ParseFunc parseFunc;
} ConfigParserEntry;

/* SortTypeNames
 * tablica nazw typów sortowania
 */
extern const char* SortTypeNames[];

/* GenTypeNames
 * tablica nazw typów generowania tablicy
 */
extern const char* GenTypeNames[];

/* Mapy tekstów z configu do wartości enum */
extern EnumEntry sortTypeMap[];
extern EnumEntry ArrTypeMap[];
extern EnumEntry fileTypeMap[];

/* Tablica parserów do sekcji konfiguracji */
extern ConfigParserEntry configParsers[];

/* Tablice wskaźników do funkcji sortujących
 * Indeksy odpowiadają wartościom z enum SortType
 */
extern void (*funcPointerFloat[])(float*, uint32_t);
extern void (*funcPointerInt[])(int*, uint32_t);

/* mapStringToEnum
 * zamienia tekst z pliku config na enum (identyfikator np. typu sortowania)
 */
int mapStringToEnum(const char* line, const EnumEntry* map, int invalidValue);

/* addToArr
 * dodaje do tablicy w config określony identyfikator
 */
void addToArr(int** arr, uint32_t* size, int value);

/* readConfig
 * czyta aktualną konfigurację
 */
void readConfig(const char* filename, Config* config);

/* printConfig
 * wyświetla aktualną konfigurację (warte sprawdzenia czy poprawnie wpisaliśmy dane)
 */
void printConfig(const Config* cfg);

/* Funkcje parserów poszczególnych sekcji konfiguracji */

bool parseArrInt(const char* line, Config* config);
bool parseSizeInt(const char* line, Config* config);
bool parseSortInt(const char* line, Config* config);

bool parseArrFloat(const char* line, Config* config);
bool parseSizeFloat(const char* line, Config* config);
bool parseSortFloat(const char* line, Config* config);

bool parseFileType(const char* line, Config* config);
bool parseSortFile(const char* line, Config* config);
bool parseFileInName(const char* line, Config* config);
bool parseFileOutName(const char* line, Config* config);
bool parseConsoleOut(const char* line, Config* config);

/* getConfigSection
 * sprawdza czy linia reprezentuje nową sekcję, jeśli tak zwraca jej identyfikator
 * następne dane będą wczytywane jako dane z tej sekcji
 */
configType getConfigSection(const char* line);

#endif // AIZO_281198_CONFIGURATION_H

