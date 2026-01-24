/*
 * Simple Echo Client - TCP Socket Programming
 * 
 * This client connects to the echo server and sends messages,
 * displaying the echoed responses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];
    char *hostname;
    
    printf("=== Simple Echo Client ===\n");
    
    // Get hostname from command line or use localhost
    if (argc < 2) {
        hostname = "localhost";
        printf("No hostname provided, using localhost\n");
    } else {
        hostname = argv[1];
    }
    
    // 1. Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("✓ Socket created\n");
    
    // 2. Resolve hostname
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "Error: No such host '%s'\n", hostname);
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("✓ Resolved %s\n", hostname);
    
    // 3. Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    server_addr.sin_port = htons(PORT);
    
    // 4. Connect to server
    printf("Connecting to %s:%d...\n", hostname, PORT);
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("✓ Connected to server!\n\n");
    
    printf("Type messages to send (type 'exit' to quit):\n");
    
    // 5. Communication loop
    while (1) {
        printf("> ");
        fflush(stdout);
        
        // Read user input
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        // Send to server
        ssize_t bytes_sent = send(sock_fd, buffer, strlen(buffer), 0);
        if (bytes_sent < 0) {
            perror("send failed");
            break;
        }
        
        // Check for exit
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }
        
        // Receive echo from server
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(sock_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received < 0) {
            perror("recv failed");
            break;
        }
        
        if (bytes_received == 0) {
            printf("Server disconnected\n");
            break;
        }
        
        printf("Echo: %s", buffer);
    }
    
    // 6. Cleanup
    close(sock_fd);
    printf("Connection closed\n");
    
    return 0;
}
