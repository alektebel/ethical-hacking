/*
 * Simple Echo Server - TCP Socket Programming
 * 
 * This is a basic TCP server that accepts connections and echoes back
 * whatever the client sends. Great for learning socket fundamentals.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 1024

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    
    printf("Client connected. Handling requests...\n");
    
    while (1) {
        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);
        
        // Read from client
        bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_read < 0) {
            perror("recv failed");
            break;
        }
        
        if (bytes_read == 0) {
            printf("Client disconnected\n");
            break;
        }
        
        // Echo back to client
        printf("Received %ld bytes: %s", bytes_read, buffer);
        
        ssize_t bytes_sent = send(client_fd, buffer, bytes_read, 0);
        if (bytes_sent < 0) {
            perror("send failed");
            break;
        }
        
        // Check for exit command
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exit command received\n");
            break;
        }
    }
    
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int opt = 1;
    
    printf("=== Simple Echo Server ===\n");
    
    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("✓ Socket created\n");
    
    // 2. Set socket options (allow address reuse)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("✓ Socket options set\n");
    
    // 3. Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    server_addr.sin_port = htons(PORT);        // Convert to network byte order
    
    // 4. Bind socket to address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("✓ Socket bound to port %d\n", PORT);
    
    // 5. Listen for connections
    if (listen(server_fd, BACKLOG) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("✓ Listening for connections (backlog: %d)\n", BACKLOG);
    printf("\nServer ready! Waiting for clients...\n");
    printf("Test with: nc localhost %d\n\n", PORT);
    
    // 6. Accept loop
    while (1) {
        client_len = sizeof(client_addr);
        
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        
        // Print client information
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("\n=== New Connection ===\n");
        printf("Client IP: %s\n", client_ip);
        printf("Client Port: %d\n", ntohs(client_addr.sin_port));
        
        // Handle client (in this simple version, blocks for each client)
        handle_client(client_fd);
        
        printf("\nWaiting for next client...\n");
    }
    
    // Cleanup (unreachable in this version)
    close(server_fd);
    return 0;
}
