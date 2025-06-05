# Algorytmy sortujące
porównanie wydajności różnych algorytmów sortowania w zależności od:

	•	typu danych (int / float),
 
	•	początkowego uporządkowania tablicy (np. rosnąco, malejąco, losowo, częsciowo uporządkowanie),
 
	•	rozmiaru danych wejściowych
# kompilacja i uruchomienie
```
make
./zadanie_1
```
# Konfiguracja
plik konfiguracyjny jest w "config.txt", konfiguruje się następująco:

 "#" oznacza komentarz
 
.{section} - oznaczenie sekcji

 elementy pod ostatnią sekcją są jej elementami

------------------------------
 OPIS SEKCJI:
------------------------------
 1. .ARR_INT, .ARR_FLOAT

   ARR_RAND -> tablica calkowicie wygenerowana
   
   ARR_RAND_33 -> losowa, ale 33% posortowanych
   
   ARR_RAND_66 -> losowa, ale 66% posortowanych
   
   ARR_SORT -> posortowana
   
   ARR_SORT_DESC -> posortowana malejaco

 3. .CONF_ARR_SIZE_INT, .CONF_ARR_SIZE_FLOAT
    
   opis: argumentami sa liczby naturalne wyczytywane linia po lini
     ktore oznaczaja rozmiar generowanych tablic
     
   np.:
   
   10000
   
   100000

 5. .SORT_INT, .SORT_FLOAT
    
   opis: argumentami sa metody sortowania

   INSERT_SORT
   HEAP_SORT
   QUICK_SORT_LEFT
   QUICK_SORT_MIDDLE
   QUICK_SORT_RIGHT
   QUICK_SORT_RANDOM
   SHELL_SORT_SHELL
   SHELL_SORT_KNUTH 

 6. .FILE_IN
    
   opis: arguementem jest nazwa pliku z ktorego dane sa tablica

 8. .FILE_TYPE
    
   opis: zmienne okreslajaca typ danych
   INT
   FLOAT

