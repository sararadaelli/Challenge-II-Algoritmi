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
