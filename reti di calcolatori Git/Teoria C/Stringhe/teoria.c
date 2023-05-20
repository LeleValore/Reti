/*

la stringa é un insieme di char in C non ci sono oggetti stringa...
In c un carattere é un numero che combacia con una lettera nella tabella ascii
Una stringa deve finire con \n che é il carattere terminatore che ne definisce lo stop 
puo essere anche il \0

facciamo un esempio 

char automatica[] = "GTC";

printf("%s", automatica);


funzioni piu utilizzate per le stringhr 

strlen()-->ritorna la lunghezza della stringa

if(strcmp("delete", automatica)== 0 ){
    PRINTF("Deleted");
} 

strcmp()--> compara le due stringhe e ritorna 0 se sono identiche senno torna l'offset cioe il delta tra i due valori ASCII come differenza 

strcpy() --> copia in memoria una stringa da una locazione all'altra carattere per carattere


strstr()--> verifica se la stringa passata come parametro é contenuta in un altra stringa 

strchr()--> cerca uin carattere in una stringa e ritorna il suo puntatore senno no

strtok()-->serve per prendere una stringa grande gli passiamo un delimitatore e ci spezza la stringa fino al delimitatore messo come parametro.




*/