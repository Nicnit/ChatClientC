#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

//  This heavily follows the tutorial on https://www.geeksforgeeks.org/c/socket-programming-cc/
//  It is meant for brushing up on C. Also for practicing neovim


int main(int argc, char const* argv[])
{

	int server_fd, new_socket;
	ssize_t valread;

	struct sockaddr_in address;;
	int opt = 1;

	// Add more code here
	
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char *hello = "\nhello world from this neovim written server.c\n";

	// Create socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Force the socket to the port PORT
	if (setsockopt(server_fd, SOL_SOCKET,
			SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt))) {
		perror("setsockoptfail");
		exit(EXIT_FAILURE);		
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*) &address,
			sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen fail");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
		perror("accept failure");
		exit(EXIT_FAILURE);	
	}

	printf("\n reached point 1 in server.c \n");

	//subtracitng 1 for the null terminator at the end, which isn't included
	valread = read(new_socket, buffer, 1024-1);
	printf("\n %s \n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("\nHello message from server sent\n");

	close(new_socket);
	close(server_fd);

	return 0;
}




// Misc helpers written as excercise.


int ReturnError(char message[], int returnNum)
{
    perror(message);
    return returnNum;
}

char* NewlineString(char str[])
{
    int oldSize = strlen(str);
    char *newString = malloc (oldSize + 1 + 1); // newline and null terminator are each 1 character
    
    strncpy(newString, str, strlen(str));

    newString[oldSize + 1] = '\0';
    newString[oldSize] = '\n';
    
    return newString;
}
