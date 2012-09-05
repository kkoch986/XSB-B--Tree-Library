#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main()
{
	char *msg_body;
	unsigned int msg_body_len, network_encoded_len;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];

	portno = 99;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		printf("Error");
	
	server = gethostbyname("localhost");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		printf("ERROR 2");

	msg_body = "Hello";
	msg_body_len = strlen(msg_body); 

	char message[msg_body_len + 5];
	
	network_encoded_len = (unsigned int) htonl((unsigned long int) msg_body_len); 

	memcpy((void *) message, (void *) &network_encoded_len, 4); 
	strncpy(message+4, msg_body, msg_body_len);

	n = send(sockfd, message, strlen(message + 4), 0);
	printf("sent %s", message+4);

	if(n < 0)
		printf("Error writing to socket\n");

	bzero(buffer, 256);

	n = read(sockfd, buffer, 255);

	printf("RECV: %s\n", buffer);


	close(sockfd);

	return 0;
}