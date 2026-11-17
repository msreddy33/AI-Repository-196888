#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_socket;

    struct sockaddr_in server_addr;

    char buffer[1024] = "Hello Server";

    // Step 1: Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Step 2: Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    // Step 3: Connect to server
    connect(client_socket, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    // Step 4: Send message to server
    send(client_socket, buffer, strlen(buffer) + 1, 0);

    // Step 5: Receive server response
    recv(client_socket, buffer, sizeof(buffer), 0);

    printf("Server says: %s\n", buffer);

    // Step 6: Close socket
    close(client_socket);

    return 0;
}