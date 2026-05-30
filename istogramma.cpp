#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_BINS 7
#define NUMERO_THREADS 16
#define LENGTH 1000000

int main() {
    omp_set_num_threads(NUMERO_THREADS);
    double start_time = omp_get_wtime();

    char *stringa = (char *)malloc(LENGTH * sizeof(char));
    for (int i = 0; i < LENGTH; i++) { // Ripete le lettere da a a z per tutta la lunghezza stabilita
        data[i] = 'a' + (i % 26);
    }
    // Inizializzazione
    int histogram[NUM_BINS]; 
    int local_histograms[NUM_BINS][NUM_THREADS]; // histogram[0][4] 

    for (int b = 0; b < NUM_BINS; b++) {
        histogram[b] = 0; // histogram[0] = 0, lettere a b c d, etc.
        for (int thr = 0; thr < NUM_THREADS; t++)
            local_histograms[b][thr] = 0; // thread per ogni contatore: local_histograms[0][0] = 0  → bin 0, thread 0, etc.
    }
    // REGIONE PARALLELA
    #pragma omp parallel 
    {
        int tid = omp_get_thread_num(); // ID del thread: 0, 1, 2, ...

        #pragma omp for // divisione lavoro tra i thread
        for (int i=0;i<length;++i) {
            int alphabet_pos = (int)data[i]-'a'; // conversione da carattere a numero
            if(alphabet_pos >= 0 && alphabet_pos < 26) { // check che sia lettera minuscola (esclude altri caratteri)
                int bin = alphabet_pos / 4; // divisione nell'apposito bin
                local_histograms[bin][tid]++; // incrementa il contatore privato del thread (tid identifica)
            }
        } 
    }
    // Somma dei contributi di ogni thread nel risultato finale
    for (int b=0; b<7; ++b) {
        for (int t=0; t<total_threads;++t) {
            histogram[b] += local_histograms[b][t];
        }
    }

    // Tempo tot = finale - iniziale
    double run_time = omp_get_wtime() - start_time;
    printf("Tempo: %f secondi con %d thread\n", run_time, NUM_THREADS);

    for (int b = 0; b < NUM_BINS; b++) {
        printf("bin[%d]: %d\n", b, histogram[b]);
    }
    free(stringa);
    return 0;
}