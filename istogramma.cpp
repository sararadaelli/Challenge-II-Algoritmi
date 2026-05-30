#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_BINS 7
#define LENGTH 1000000

int main() {
    double start_time = omp_get_wtime();
    int NUM_THREADS = omp_get_max_threads(); // legge la variabile che verrà impostata dall'utente nel terminale (1,2,8,16,...)

    // Generazione stringa di input
    char *stringa = (char *)malloc(LENGTH * sizeof(char));
    srand(42); // seme fisso per riproducibilità
    for (int i = 0; i < LENGTH; i++) {
        stringa[i] = 'a' + (rand() % 26);
    }
    // Inizializzazione
    int histogram[NUMERO_BINS];
    int local_histograms[NUMERO_BINS][NUM_THREADS];

    for (int b = 0; b < NUMERO_BINS; b++) {
        histogram[b] = 0; // histogram[0] = 0, lettere a b c d, etc.
        for (int thr = 0; thr < NUM_THREADS; thr++) // 
            local_histograms[b][thr] = 0; // thread per ogni contatore: local_histograms[0][0] = 0  → bin 0, thread 0, etc.
    }

    // Regione parallela
    #pragma omp parallel
    {
        int tid = omp_get_thread_num(); // ID del thread: 0, 1, 2, ...

        #pragma omp for
        for (int i = 0; i < LENGTH; ++i) { 
            int alphabet_pos = (int)stringa[i] - 'a'; // conversione da carattere a numero
            if (alphabet_pos >= 0 && alphabet_pos < 26) { // check che sia lettera minuscola (esclude altri caratteri)
                int bin = alphabet_pos / 4; // divisione nell'apposito bin
                local_histograms[bin][tid]++; // incrementa il contatore privato del thread (tid identifica)
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
        // printf("bin[%d]: %d\n", b, histogram[b]);

    free(stringa);
    return 0;
}
