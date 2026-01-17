#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080


// This was made for the same reasons and with the same resources as states at the top of server.c

int main (int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "\n hello from the client \n";
	char buffer[1024] = { 0 }; 
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// converting ipv4 and ipv6 adresse to binary from text
	
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof (serv_addr))) < 0) {
		printf("\nConnection failed \n");
		return -1;
	}

	//subtracting 1 for the null terminator
	send(client_fd, hello, strlen(hello), 0);
	printf("\n hello message sent \n");
	valread = read(client_fd, buffer, 1024 - 1);
	printf("\n %s \n", buffer);

	// closing the connected socket
	close(client_fd);
	return 0;
}
