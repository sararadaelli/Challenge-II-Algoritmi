#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
  
#define NUMERO_BINS 7
#define LENGTH 1000000
 
int main(void) {
    int NUM_THREADS = omp_get_max_threads();
// Generazione stringa di input
char *data = (char *)malloc(LENGTH * sizeof(char));
srand(42); // seme fisso per riproducibilità
for (int i = 0; i < LENGTH; i++) {
    data[i] = 'a' + (rand() % 26);
}
 
double start_time = omp_get_wtime();
 
// Inizializzazione
    int histogram[NUMERO_BINS] = {0};
 

 
// Regione parallela
    #pragma omp parallel
    {
#pragma omp for reduction(+:histogram[0:NUMERO_BINS])
        for (int i = 0; i < LENGTH; ++i) {
            int alphabet_pos = (int)data[i] - 'a';
            if (alphabet_pos >= 0 && alphabet_pos < 26) {
                int bin = alphabet_pos / 4;
                histogram[bin]++;
            }
        }
    }
  
    double run_time = omp_get_wtime() - start_time;
    printf("Tempo: %f secondi con %d thread\n", run_time, NUM_THREADS);
  
    // Stampa istogramma
    // for (int b = 0; b < NUMERO_BINS; b++)
    //     printf("bin[%d]: %d\n", b, histogram[b]);
  
    free(data);
    return 0;
}
 
