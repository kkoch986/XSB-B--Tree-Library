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

const unsigned int OP_HANDSHAKE_INIT = 1;
char* build_op_hsinit(char *mname, int sockfd);

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

	char *message = build_op_hsinit("kens computer", sockfd);

	// printf("sending %s", message+4);
	// n = send(sockfd, message, strlen(message + 4) + 4, 0);
	// printf("sent %s", message+4);

	// if(n < 0)
	// 	printf("Error writing to socket\n");

	// bzero(buffer, 256);

	// n = read(sockfd, buffer, 255);

	// printf("RECV: %s\n", buffer);

	close(sockfd);

	return 0;
}

// OP_QUERY Packet:
// ----------------- [excluded] 4 Bytes Total Message Length (unsigned int) (message[0 - 3])
// 1 Byte OP_CODE (unsigned int) (message[4 - 7])
// 4 Byte Machine Name Length
// <Machine Name Length> Bytes Machine Name
//
// Returned value is allocated using malloc
// so it should be freed when done
const int op_hdinit_packet_length = 6;
char* build_op_hsinit(char *mname, int sockfd)
{
	// the query returned will be the op code
	unsigned int content_length = strlen(mname);

	// set aside some space for the message
	char *message = malloc(sizeof(char) * (content_length + 8));
	bzero(message, (content_length + op_hdinit_packet_length));
	
	// now the op code
	unsigned int opcode = htons(OP_HANDSHAKE_INIT);
	memcpy((void *) message, (void *) &opcode, 2); 
	// strncpy(message+4, itoa(OP_QUERY), 2); 

	// now the query length
	unsigned int cls = htonl(content_length);
	memcpy((void *) message+2, (void *) &cls, 4); 
	// strncpy(message+6, itoa(query_length), 2); 

	// now the query string
	strcpy(message+op_hdinit_packet_length, mname);

	int n = send(sockfd, message, content_length + op_hdinit_packet_length, 0);

	if(n < 0)
		printf("Error writing to socket\n");


	return message;
}