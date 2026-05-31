#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_BINS 7
#define LENGTH 1000000

int main() {
    int NUM_THREADS = omp_get_max_threads();

    // Generazione stringa di input
    char *data = (char *)malloc(LENGTH * sizeof(char));
    srand(42); // seme fisso per riproducibilità
    for (int i = 0; i < LENGTH; i++) {
        data[i] = 'a' + (rand() % 26);
    }
    
    double start_time = omp_get_wtime();
    
    // Inizializzazione
    int histogram[NUMERO_BINS];
    int local_histograms[NUMERO_BINS][NUM_THREADS];

    for (int b = 0; b < NUMERO_BINS; b++) {
        histogram[b] = 0;
        for (int thr = 0; thr < NUM_THREADS; thr++)
            local_histograms[b][thr] = 0;
    }

    // Regione parallela
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < LENGTH; ++i) { 
            int alphabet_pos = (int)data[i] - 'a';
            if (alphabet_pos >= 0 && alphabet_pos < 26) {
                int bin = alphabet_pos / 4;
                local_histograms[bin][tid]++;
            }
        }
    }

    // Somma contributi di ogni thread
    for (int b = 0; b < NUMERO_BINS; b++)
        for (int t = 0; t < NUM_THREADS; t++)
            histogram[b] += local_histograms[b][t];

    double run_time = omp_get_wtime() - start_time;
    printf("Tempo: %f secondi con %d thread\n", run_time, NUM_THREADS);

    // Stampa istogramma
    // for (int b = 0; b < NUMERO_BINS; b++)
    //     printf("bin[%d]: %d\n", b, histogram[b]);

    free(data);
    return 0;
}
