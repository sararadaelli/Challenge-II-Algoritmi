#PER L'ESECUZIONE DEL CODICE: questo file è uno script che serve per compilare ed eseguire i codici. 
#Per avviarlo basta eseguire questo file dal terminale.
#NOTA SULLA RIPRODUCIBILITA': invece di fissare il numero di thread direttamente nel codice (ad esempio tramite
#una #define), si è scelto di far scegliere all’utente il numero di threads al momento
#dell’esecuzione, tramite la variabile OMP_NUM_THREADS. Questo garantisce
#maggiore riproducibilità: utenti con numero di core diversi otterranno risultati coerenti
#con la propria macchina.
gcc-15 -fopenmp -o istogramma istogramma.cpp

// IN ENTRAMBI I CASI L'UTENTE PUÒ SCEGLIERE IL NUMERO DI THREADS CON CUI ESEGUIRE IL PROGRAMMA
for t in 1 2 4 8 16; do 
    for i in 1 2 3; do
        OMP_NUM_THREADS=$t ./istogramma
    done
done

gcc-15 -fopenmp -o istogrammafix istogrammafix.cpp

for t in 1 2 4 8 16; do
    for i in 1 2 3; do
        OMP_NUM_THREADS=$t ./istogrammafix
    done
done
