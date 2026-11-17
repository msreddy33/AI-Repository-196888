#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_socket, client_socket;

    struct sockaddr_in server_addr;

    char buffer[1024];

    // Step 1: Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Step 2: Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Bind socket with IP and port
    bind(server_socket, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    // Step 4: Listen for client requests
    listen(server_socket, 5);

    printf("Server waiting for client...\n");

    // Step 5: Accept client connection
    client_socket = accept(server_socket, NULL, NULL);

    // Step 6: Receive message from client
    recv(client_socket, buffer, sizeof(buffer), 0);

    printf("Client says: %s\n", buffer);

    // Step 7: Send response to client
    send(client_socket, "Hello Client", 13, 0);

    // Step 8: Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}