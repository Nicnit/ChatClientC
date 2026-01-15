#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);


    // IPv4, TCP type, let OS decide protocol.
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) ReturnError("Network socket failed", -1);


    if (
        connect(network_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0
    )   ReturnError("Connection failed", -1);

    //Now connected. send() and recv() work


    






    return 0;
}



int ReturnError(char message[], int returnNum)
{
    perror(message);
    return returnNum;
}

char* NewlineString(char str[])
{
    int oldSize = strlen(str);
    char *newString = malloc (oldSize + 1 + 1); // newline and null terminator are each 1 character
    strcpy(newString, str);

    newString[oldSize + 1] = '\0';
    newString[oldSize] = '\n';
    
    return newString;
}