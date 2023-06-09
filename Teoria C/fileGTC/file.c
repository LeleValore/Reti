/*
prima cosa quando operare su un file dobbiamo verificare se é stato aperto 
con successo attraverso un controllo con fopen()..

dobbiamo anche chiuderlo con fclose() per evitare problemi..

operazioni:

fopen(): 
Questa funzione viene utilizzata per aprire un file specificato dal suo percorso e restituisce un puntatore al file aperto. 
Accetta due argomenti: il percorso del file e la modalità di apertura (come "r" per la lettura, "w" per la scrittura, "a" per l'aggiunta, ecc.).

fprintf(): 
Questa funzione viene utilizzata per scrivere dati su un file aperto utilizzando una sintassi simile a printf(). 
Accetta come primo argomento un puntatore al file aperto e successivamente gli argomenti da scrivere sul file.

fscanf():
Questa funzione viene utilizzata per leggere dati da un file aperto utilizzando una sintassi simile a scanf(). 
Accetta come primo argomento un puntatore al file aperto e successivamente gli argomenti in cui memorizzare i dati letti dal file.

fputc(): 
Questa funzione viene utilizzata per scrivere un singolo carattere su un file aperto. 
Accetta come primo argomento il carattere da scrivere e come secondo argomento un puntatore al file aperto.

fgetc(): 
Questa funzione viene utilizzata per leggere un singolo carattere da un file aperto.
Accetta come argomento un puntatore al file aperto e restituisce il carattere letto.

fseek(): 
Questa funzione viene utilizzata per spostare il puntatore di posizione all'interno di un file aperto. 
Accetta come argomenti un puntatore al file aperto e un valore di offset che specifica la posizione desiderata nel file.

fclose(): 
Questa funzione viene utilizzata per chiudere un file aperto. 
Accetta come argomento un puntatore al file aperto.

ftell(): 
Questa funzione restituisce la posizione corrente del puntatore all'interno di un file aperto. 
Accetta come argomento un puntatore al file aperto.

rewind(): 
Questa funzione reimposta il puntatore di posizione all'inizio del file aperto. 
Accetta come argomento un puntatore al file aperto.

fputs(): 
Questa funzione viene utilizzata per scrivere una stringa su un file aperto.
Accetta come primo argomento un puntatore alla stringa da scrivere e come secondo argomento un puntatore al file aperto.

fgets(): 
Questa funzione viene utilizzata per leggere una riga di testo da un file aperto e la memorizza in una stringa. 
Accetta come primo argomento un puntatore alla stringa in cui memorizzare la riga di testo e come secondo argomento un puntatore al file aperto.

MODALITA DI APERTURA FILE 

r --> lettura 
w --> scrittura 
a --> appending
r+ --> lettura/Scrittura
a+ --> lettura scrittura 
w+ --> lettura scrittura
rb --> Lettura Binaria 
wb --> Scrittura Binaria
ab --> Appending Binario
rb+ --> Lettura/Scrittura B
wb+ --> Lettura/Scrittura B
ab+ --> Lettura/Scrittura B

*/
