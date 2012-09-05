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

const unsigned int OP_QUERY = 0;
char* build_op_query(char *query);

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

	msg_body = "a(b,c)";
	char *message = build_op_query(msg_body);

	printf("sending %s", message+4);
	n = send(sockfd, message, strlen(message), 0);
	printf("sent %s", message+4);

	if(n < 0)
		printf("Error writing to socket\n");

	// bzero(buffer, 256);

	// n = read(sockfd, buffer, 255);

	// printf("RECV: %s\n", buffer);

	close(sockfd);

	return 0;
}

// OP_QUERY Packet:
// 4 Bytes Total Message Length (unsigned int) (message[0 - 3])
// 4 Byte OP_CODE (unsigned int) (message[4 - 7])
// 4 Bytes Query String Length (unsigned int) (message[8 - 11])
// <Query String Length> Bytes Query String
//
// Returned value is allocated using malloc
// so it should be freed when done
char* build_op_query(char *query)
{
	// the query returned will be the op code
	unsigned int query_length = strlen(query);

	// set aside some space for the message
	char *message = malloc(sizeof(char) * query_length + 16);

	// start with the network encoded length
	unsigned int network_encoded_len = (unsigned int) htonl((unsigned long int) (4 + query_length)); 
	memcpy((void *) message, (void *) &network_encoded_len, 4); 
	
	// now the op code
	// memcpy((void *) message+4, (void *) &OP_QUERY, 2); 
	strncpy(message+4, itoa(OP_QUERY), 2); 

	// now the query length
	// memcpy((void *) message+6, (void *) &query_length, 2); 
	strncpy(message+6, itoa(query_length), 2); 

	// now the query string
	strcpy(message+8, query);

	printf("message: %s\n", message + 4);

	return message;
}