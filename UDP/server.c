#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

/*
    socket()
	bind()
    recvfrom()
    close()
*/

#define IP "127.0.0.1"
#define PORT 8080

int main(int argc, char* argv[])
{	
    int sockfd;
    struct sockaddr_in addr;
    char buffer[100];

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //UDP
    {
		perror("[-]Server socket error\n");
		exit(1);
	}
	printf("[+]Server socket created\n\n");

	memset(&addr, 0, sizeof(addr));  //Questa funzione viene utilizzata per azzerare l'intera struttura inizialmente.
    addr.sin_family = AF_INET;  //FAMIGLIA IPV4

	inet_pton(AF_INET, IP, &(addr.sin_addr)); 
	//"inet_pton()" per convertire un indirizzo IP testuale in un formato binario compatibile con la famiglia di protocolli di Internet.
	// Gli argomenti della funzione sono 
	//"AF_INET" (la famiglia di protocolli utilizzata), 
	//"IP" (l'indirizzo IP testuale da convertire) e 
	//"&(addr.sin_addr)" (l'indirizzo del campo "sin_addr" della struttura "addr" in cui viene memorizzato l'indirizzo IP convertito).
    
	addr.sin_port = htons(PORT);
	//htons()" viene utilizzata per convertire il valore "PORT" 
	//(in formato host byte order) in un valore compatibile con la rete (in formato network byte order).

	int n = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)); 
	//viene dichiarata una variabile intera "n" che viene utilizzata per memorizzare
	// il valore restituito dalla funzione "bind()" che ha come parametri il socket file descriptor "sockfd", 
	//l'indirizzo del socket "addr" (di tipo "struct sockaddr") e la dimensione dell'indirizzo del socket "sizeof(addr)".
	if(n < 0)
	{
		perror("[-]Binding socket server error\n");
		exit(1);
	}
	printf("[+]Binding socket\n");
	
	listen(sockfd, 5);
	/*
	La funzione "listen()" prende come argomenti 
	il socket file descriptor "sockfd" e il numero massimo di connessioni in attesa di essere accettate, in questo caso 5.
	*/
	puts("Listening...\n"); //stampo.

	for(;;)
	{
		socklen_t size = sizeof(addr);
		ssize_t nread = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &addr, &size);

		char client[INET_ADDRSTRLEN];	//16
		inet_ntop(AF_INET, &(addr.sin_addr), client, INET_ADDRSTRLEN);

		printf("Request from client %s:\t%s\n\n", client, buffer);

		// Elabora la richiesta del client
		// ...
		// Invia la risposta al client

		char* response = "OK";
		ssize_t nwrite = sendto(sockfd, response, strlen(response), 0, (struct sockaddr*) &addr, size);
	}

	close(sockfd);

	return 0;
}
