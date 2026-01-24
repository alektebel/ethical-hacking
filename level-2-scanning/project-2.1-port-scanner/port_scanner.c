/*
 * Simple Port Scanner - TCP Connect Scan
 * 
 * This program implements a basic port scanner that attempts to connect
 * to ports on a target host to determine which ones are open.
 * 
 * Compile: gcc -pthread -o port_scanner port_scanner.c
 * Run:     ./port_scanner <target_ip> <start_port> <end_port>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define MAX_THREADS 100
#define TIMEOUT_SEC 1

// Structure to pass data to threads
typedef struct {
    char *target_ip;
    int port;
} scan_args_t;

// Common service names
const char* get_service_name(int port) {
    switch(port) {
        case 20: return "FTP-DATA";
        case 21: return "FTP";
        case 22: return "SSH";
        case 23: return "Telnet";
        case 25: return "SMTP";
        case 53: return "DNS";
        case 80: return "HTTP";
        case 110: return "POP3";
        case 143: return "IMAP";
        case 443: return "HTTPS";
        case 445: return "SMB";
        case 3306: return "MySQL";
        case 3389: return "RDP";
        case 5432: return "PostgreSQL";
        case 6379: return "Redis";
        case 8080: return "HTTP-Proxy";
        default: return "Unknown";
    }
}

// Scan a single port
int scan_port(const char *ip, int port) {
    int sock;
    struct sockaddr_in target;
    struct timeval timeout;
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }
    
    // Set timeout
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    
    // Setup target address
    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip, &target.sin_addr) <= 0) {
        close(sock);
        return -1;
    }
    
    // Try to connect
    int result = connect(sock, (struct sockaddr *)&target, sizeof(target));
    
    close(sock);
    
    return result == 0 ? 1 : 0;  // 1 = open, 0 = closed
}

// Thread function for scanning
void* scan_thread(void *args) {
    scan_args_t *scan_args = (scan_args_t *)args;
    
    int result = scan_port(scan_args->target_ip, scan_args->port);
    
    if (result == 1) {
        printf("[+] Port %d is OPEN (%s)\n", 
               scan_args->port, 
               get_service_name(scan_args->port));
    }
    
    free(scan_args);
    return NULL;
}

int main(int argc, char *argv[]) {
    char *target_ip;
    int start_port, end_port;
    int open_count = 0;
    time_t start_time, end_time;
    
    printf("=== Simple Port Scanner ===\n");
    printf("WARNING: Only scan hosts you own or have permission to test!\n\n");
    
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <target_ip> <start_port> <end_port>\n", argv[0]);
        fprintf(stderr, "Example: %s 192.168.1.1 1 1000\n", argv[0]);
        return 1;
    }
    
    target_ip = argv[1];
    start_port = atoi(argv[2]);
    end_port = atoi(argv[3]);
    
    // Validate port range
    if (start_port < 1 || end_port > 65535 || start_port > end_port) {
        fprintf(stderr, "Invalid port range. Ports must be 1-65535.\n");
        return 1;
    }
    
    printf("Target: %s\n", target_ip);
    printf("Port range: %d-%d\n", start_port, end_port);
    printf("Scanning...\n\n");
    
    start_time = time(NULL);
    
    // Simple approach: sequential scanning
    // For better performance, we could use threads
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;
    
    for (int port = start_port; port <= end_port; port++) {
        // Create scan arguments
        scan_args_t *args = malloc(sizeof(scan_args_t));
        args->target_ip = target_ip;
        args->port = port;
        
        // Create thread
        if (pthread_create(&threads[thread_count], NULL, scan_thread, args) == 0) {
            thread_count++;
            
            // Wait for threads if we hit the max
            if (thread_count >= MAX_THREADS) {
                for (int i = 0; i < thread_count; i++) {
                    pthread_join(threads[i], NULL);
                }
                thread_count = 0;
            }
        } else {
            free(args);
        }
    }
    
    // Wait for remaining threads
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    
    end_time = time(NULL);
    
    printf("\n=== Scan Complete ===\n");
    printf("Time elapsed: %ld seconds\n", end_time - start_time);
    printf("Scanned %d ports\n", end_port - start_port + 1);
    
    return 0;
}
