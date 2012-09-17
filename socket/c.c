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

// Main Connection OP Codes
const unsigned int OP_HANDSHAKE_INIT 	= 1;
const unsigned int OP_HANDSHAKE_ACK 	= 2;
const unsigned int OP_DISCONNECT 		= 3;

// Prolog Controlling Op Codes
const unsigned int OP_CONSULT 			= 4;
const unsigned int OP_QUERY 			= 5;
const unsigned int OP_GET_RESULT		= 6;

// Packet and/or header lengths:            
const int op_hsinit_packet_header_length    = 6;
const int op_hsack_packet_length            = 2;
const int op_disconnect_packet_length       = 2;
const int op_consult_packet_header_length   = 6;
const int op_query_packet_header_length     = 6;
const int op_get_result_length              = 2;


int send_op_hsinit(char *mname, int sockfd);
int recv_op_hsack(int sockfd);
int send_op_disconnect(int sockfd);
int send_op_consult(char *fname, int sockfd);
int send_op_query(char *query, int sockfd);
int send_op_get_result(int sockfd);

// Structure to hold query results
struct query_result 
{
	// a bool to represent whether or not this object
	// is actually holding a result. Value should be either
	// 0 or 1, 0 being a failure.
	char fail;
};

// Helper function to convert OP codes to strings
char *optos(unsigned int opcode)
{
	switch(opcode)
	{
		case 1:
			return "OP_HANDSHAKE_INIT";
		case 2:
			return "OP_HANDSHAKE_ACK";
		case 4:
			return "OP_CONSULT";
		case 5:
			return "OP_QUERY";
		case 6:
			return "OP_GET_RESULT";
		default:
			return "UNKNOWN";
	}
}

int main()
{
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;

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

	// perform the handshake
	send_op_hsinit("kens computer", sockfd);
	recv_op_hsack(sockfd);

	// send consult queries to load the btree library
	send_op_consult("../qdbm/bt", sockfd);
	send_op_consult("../qdbm/bt_p", sockfd);

	// now the fun part, send some queries
	send_op_query("assert(a(b,c)), assert(a(c,d)", sockfd);
	//sleep(5);
	send_op_query("a(X,Y), writeln(X)", sockfd);
	//send_op_query("btinit(quad/4,1,_X), btgetall(_X, Y)", sockfd);

	// send packets to get some results
	send_op_get_result(sockfd);
	send_op_get_result(sockfd);

	// send a disconnect query and close the connection
	send_op_disconnect(sockfd);
	printf("Closing...\n");
	close(sockfd);

	return 0;
}

// OP_HS_INIT Packet:
// 2 Byte OP_CODE (unsigned int)
// 4 Byte Machine Name Length
// <Machine Name Length> Bytes Machine Name
int send_op_hsinit(char *mname, int sockfd)
{
	// the query returned will be the op code
	unsigned int content_length = strlen(mname);

	// set aside some space for the message
	char *message = malloc(sizeof(char) * (content_length + op_hsinit_packet_header_length));
	bzero(message, (content_length + op_hsinit_packet_header_length));
	
	// now the op code
	unsigned int opcode = htons(OP_HANDSHAKE_INIT);
	memcpy((void *) message, (void *) &opcode, 2); 

	// now the query length
	unsigned int cls = htonl(content_length);
	memcpy((void *) message+2, (void *) &cls, 4); 

	// now the query string
	strcpy(message+op_hsinit_packet_header_length, mname);

	int n = send(sockfd, message, content_length + op_hsinit_packet_header_length, 0);

	return n;
}


// OP_HS_ACK Packet:
// 2 Byte OP_CODE (unsigned int, OP_HANDSHAKE_ACK)
int recv_op_hsack(int sockfd)
{
	int n;
	unsigned int opcode;

	// read 2 bytes for the opcode
	n = read(sockfd, &opcode, 2);

	opcode = ntohs(opcode);

	if(opcode == OP_HANDSHAKE_ACK)
	{
		printf("Recieved HS ACK.\n");
		return 1;
	}
	else 
	{
		printf("ERROR: WRONG OP CODE RECIEVED (expected %s, got %s)\n", optos(OP_HANDSHAKE_INIT), optos(opcode));
		return 0;
	}
}

// OP_DISCONNECT packet:
// 2 byte opcode (unsigned int, OP_DISCONNECT)
int send_op_disconnect(int sockfd)
{
	// set aside some space for the message
	char *message = malloc(sizeof(char) * (op_disconnect_packet_length));
	bzero(message, op_disconnect_packet_length);
	
	// now the op code
	unsigned int opcode = htons(OP_DISCONNECT);
	memcpy((void *) message, (void *) &opcode, 2); 

	int n = send(sockfd, message, op_disconnect_packet_length, 0);

	return n;
}

// OP_CONSULT Packet:
// 2 Byte OP_CODE (unsigned int, OP_CONSULT)
// 4 Byte File name length (fnamelength)
// <fnamelength> Bytes File name
int send_op_consult(char *fname, int sockfd)
{
	// the query returned will be the op code
	unsigned int content_length = strlen(fname);

	// set aside some space for the message
	char *message = malloc(sizeof(char) * (content_length + op_consult_packet_header_length));
	bzero(message, (content_length + op_consult_packet_header_length));
	
	// now the op code
	unsigned int opcode = htons(OP_CONSULT);
	memcpy((void *) message, (void *) &opcode, 2); 

	// now the query length
	unsigned int cls = htonl(content_length);
	memcpy((void *) message+2, (void *) &cls, 4); 

	// now the query string
	strcpy(message+op_consult_packet_header_length, fname);

	int n = send(sockfd, message, content_length + op_consult_packet_header_length, 0);

	return n;
}

// OP_QUERY Packet:
// 2 Byte OP_CODE (unsigned int, OP_QUERY)
// 4 Byte Query string length (querylength)
// <querylength> Bytes query string
int send_op_query(char *query, int sockfd)
{
	// the query returned will be the op code
	unsigned int content_length = strlen(query);

	// set aside some space for the message
	char *message = malloc(sizeof(char) * (content_length + op_query_packet_header_length));
	bzero(message, (content_length + op_query_packet_header_length));
	
	// now the op code
	unsigned int opcode = htons(OP_QUERY);
	memcpy((void *) message, (void *) &opcode, 2); 

	// now the query length
	unsigned int cls = htonl(content_length);
	memcpy((void *) message+2, (void *) &cls, 4); 

	// now the query string
	strcpy(message+op_query_packet_header_length, query);

	int n = send(sockfd, message, content_length + op_query_packet_header_length, 0);

	return n;
}

// OP_GET_RESULT packet:
// 2 byte opcode (unsigned int, OP_GET_RESULT)
int send_op_get_result(int sockfd)
{
	// set aside some space for the message
	char *message = malloc(sizeof(char) * (op_get_result_length));
	bzero(message, op_get_result_length);
	
	// now the op code
	unsigned int opcode = htons(OP_GET_RESULT);
	memcpy((void *) message, (void *) &opcode, 2); 

	int n = send(sockfd, message, op_get_result_length, 0);

	return n;
}