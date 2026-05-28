# Parallel Histogram with OpenMP

Un istogramma può essere usato per identificare pattern in un dataset.

Nella versione più semplice, un istogramma viene costruito analizzando il valore di ciascun elemento del dataset e incrementando il contatore corrispondente.

Possiamo dividere i dati di input in sezioni indipendenti, che quindi possono essere gestite in parallelo.

Ecco uno snippet di codice che utilizza OpenMP per generare un istogramma che conta il numero di occorrenze di ogni lettera in una stringa di caratteri, raggruppandole in sette bin da quattro lettere:

* a-d
* e-h
* i-l
* m-p
* q-t
* u-x
* y-z

---

# DOMANDE

## 1. Completamento del programma

Cosa manca per poter eseguire il programma?

* Completare il codice
* Inizializzare correttamente le variabili
* Aggiungere la misurazione del tempo totale di esecuzione

---

## 2. Analisi delle performance

Il tempo di esecuzione diminuisce all’aumentare del numero di thread utilizzati?

Eseguire test con diversi numeri di thread ed elencare:

* sistema operativo
* numero di core
* versione di OpenMP

Riportare i risultati in:

* una tabella
* oppure un grafico

---

## 3. Analisi dello speedup

Come mai la diminuzione del tempo di esecuzione non è lineare?

Formulare ipotesi in base alle conoscenze dell’architettura del calcolatore.

---

## 4. Ottimizzazione

Si può rendere il codice più efficiente?

In base alla risposta trovata per il punto 3:

* modificare il programma
* ripetere gli esperimenti del punto 2
* dimostrare il miglioramento nel tempo di esecuzione
