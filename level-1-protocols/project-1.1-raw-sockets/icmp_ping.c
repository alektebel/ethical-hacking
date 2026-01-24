/*
 * ICMP Ping - Custom Ping Implementation using Raw Sockets
 * 
 * This program sends ICMP Echo Request packets and waits for replies,
 * just like the standard ping utility.
 * 
 * Compile: gcc -o icmp_ping icmp_ping.c
 * Run:     sudo ./icmp_ping <target_ip>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>

#define PACKET_SIZE 64
#define ICMP_ECHO_REQUEST 8

// Calculate Internet Checksum
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;
    
    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    
    if (len == 1) {
        sum += *(unsigned char *)buf;
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    
    return result;
}

// Send ICMP Echo Request
int send_ping(int sock, struct sockaddr_in *addr, int seq) {
    char packet[PACKET_SIZE];
    struct icmp *icmp_hdr;
    struct timeval *timestamp;
    
    memset(packet, 0, PACKET_SIZE);
    
    // Set up ICMP header
    icmp_hdr = (struct icmp *)packet;
    icmp_hdr->icmp_type = ICMP_ECHO;
    icmp_hdr->icmp_code = 0;
    icmp_hdr->icmp_id = getpid() & 0xFFFF;
    icmp_hdr->icmp_seq = seq;
    
    // Add timestamp in data portion
    timestamp = (struct timeval *)(packet + sizeof(struct icmp));
    gettimeofday(timestamp, NULL);
    
    // Calculate checksum
    icmp_hdr->icmp_cksum = 0;
    icmp_hdr->icmp_cksum = checksum(packet, PACKET_SIZE);
    
    // Send packet
    if (sendto(sock, packet, PACKET_SIZE, 0, 
               (struct sockaddr *)addr, sizeof(*addr)) <= 0) {
        perror("sendto failed");
        return -1;
    }
    
    return 0;
}

// Receive ICMP Echo Reply
int receive_ping(int sock) {
    char buffer[1024];
    struct sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    struct timeval tv_recv;
    struct ip *ip_hdr;
    struct icmp *icmp_hdr;
    struct timeval *tv_sent;
    double rtt;
    
    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    
    // Receive packet
    int n = recvfrom(sock, buffer, sizeof(buffer), 0,
                     (struct sockaddr *)&from, &fromlen);
    
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("Request timeout\n");
        } else {
            perror("recvfrom failed");
        }
        return -1;
    }
    
    gettimeofday(&tv_recv, NULL);
    
    // Parse IP header
    ip_hdr = (struct ip *)buffer;
    int ip_hdr_len = ip_hdr->ip_hl * 4;
    
    // Parse ICMP header
    icmp_hdr = (struct icmp *)(buffer + ip_hdr_len);
    
    if (icmp_hdr->icmp_type == ICMP_ECHOREPLY) {
        // Get timestamp from data
        tv_sent = (struct timeval *)(buffer + ip_hdr_len + sizeof(struct icmp));
        
        // Calculate RTT in milliseconds
        rtt = (tv_recv.tv_sec - tv_sent->tv_sec) * 1000.0;
        rtt += (tv_recv.tv_usec - tv_sent->tv_usec) / 1000.0;
        
        printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
               n - ip_hdr_len,
               inet_ntoa(from.sin_addr),
               icmp_hdr->icmp_seq,
               ip_hdr->ip_ttl,
               rtt);
        
        return 0;
    }
    
    return -1;
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in addr;
    int seq = 0;
    
    printf("=== Custom ICMP Ping Tool ===\n");
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_ip>\n", argv[0]);
        return 1;
    }
    
    // Check if running as root
    if (geteuid() != 0) {
        fprintf(stderr, "Error: This program requires root privileges\n");
        fprintf(stderr, "Run with: sudo %s <target_ip>\n", argv[0]);
        return 1;
    }
    
    // Create raw socket
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }
    printf("✓ Raw socket created\n");
    
    // Setup destination address
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address: %s\n", argv[1]);
        close(sock);
        return 1;
    }
    
    printf("PING %s (%s): %d data bytes\n", 
           argv[1], argv[1], PACKET_SIZE - 8);
    
    // Send pings
    while (1) {
        if (send_ping(sock, &addr, seq) < 0) {
            break;
        }
        
        receive_ping(sock);
        
        seq++;
        sleep(1);
    }
    
    close(sock);
    return 0;
}
