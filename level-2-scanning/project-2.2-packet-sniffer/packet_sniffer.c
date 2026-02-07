/*
 * Network Packet Sniffer
 * 
 * A packet sniffer that captures and analyzes network traffic using raw sockets.
 * This implementation demonstrates how packet capture works at a low level.
 * 
 * IMPORTANT: This tool is for educational purposes only. Only use on networks
 * you own or have explicit permission to monitor.
 * 
 * Compile: gcc -o packet_sniffer packet_sniffer.c
 * Run:     sudo ./packet_sniffer [interface] [count]
 * Example: sudo ./packet_sniffer eth0 100
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFFER_SIZE 65536

// Statistics
typedef struct {
    int total;
    int tcp;
    int udp;
    int icmp;
    int other;
} packet_stats_t;

packet_stats_t stats = {0, 0, 0, 0, 0};
int running = 1;

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    (void)sig;  // Suppress unused parameter warning
    running = 0;
}

// Print MAC address
void print_mac(unsigned char *mac) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

// Print Ethernet header
void print_ethernet(unsigned char *buffer) {
    struct ethhdr *eth = (struct ethhdr *)buffer;
    
    printf("Ethernet: ");
    print_mac(eth->h_source);
    printf(" -> ");
    print_mac(eth->h_dest);
    printf("\n");
    printf("Protocol: ");
    
    switch (ntohs(eth->h_proto)) {
        case ETH_P_IP:
            printf("IP (0x%04x)\n", ntohs(eth->h_proto));
            break;
        case ETH_P_ARP:
            printf("ARP (0x%04x)\n", ntohs(eth->h_proto));
            break;
        case ETH_P_IPV6:
            printf("IPv6 (0x%04x)\n", ntohs(eth->h_proto));
            break;
        default:
            printf("Other (0x%04x)\n", ntohs(eth->h_proto));
            break;
    }
}

// Print IP header
void print_ip(unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    struct sockaddr_in source, dest;
    
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;
    
    printf("IP: %s -> %s", 
           inet_ntoa(source.sin_addr),
           inet_ntoa(dest.sin_addr));
    
    switch (ip->protocol) {
        case IPPROTO_TCP:
            printf(" (TCP)\n");
            break;
        case IPPROTO_UDP:
            printf(" (UDP)\n");
            break;
        case IPPROTO_ICMP:
            printf(" (ICMP)\n");
            break;
        default:
            printf(" (Protocol: %d)\n", ip->protocol);
            break;
    }
    
    printf("  TTL: %d, Length: %d\n", ip->ttl, ntohs(ip->tot_len));
}

// Print TCP header
void print_tcp(unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned int ip_header_len = ip->ihl * 4;
    struct tcphdr *tcp = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + ip_header_len);
    
    printf("TCP: %u -> %u\n", ntohs(tcp->source), ntohs(tcp->dest));
    printf("  Flags: [");
    
    if (tcp->syn) printf("SYN ");
    if (tcp->ack) printf("ACK ");
    if (tcp->fin) printf("FIN ");
    if (tcp->rst) printf("RST ");
    if (tcp->psh) printf("PSH ");
    if (tcp->urg) printf("URG ");
    
    printf("]\n");
    printf("  Seq: %u", ntohl(tcp->seq));
    if (tcp->ack) printf(", Ack: %u", ntohl(tcp->ack_seq));
    printf("\n");
    
    stats.tcp++;
}

// Print UDP header
void print_udp(unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned int ip_header_len = ip->ihl * 4;
    struct udphdr *udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + ip_header_len);
    
    printf("UDP: %u -> %u\n", ntohs(udp->source), ntohs(udp->dest));
    printf("  Length: %d\n", ntohs(udp->len));
    
    stats.udp++;
}

// Print ICMP header
void print_icmp(unsigned char *buffer) {
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned int ip_header_len = ip->ihl * 4;
    struct icmphdr *icmp = (struct icmphdr *)(buffer + sizeof(struct ethhdr) + ip_header_len);
    
    printf("ICMP: Type %d, Code %d\n", icmp->type, icmp->code);
    
    switch (icmp->type) {
        case ICMP_ECHO:
            printf("  Echo Request (Ping)\n");
            break;
        case ICMP_ECHOREPLY:
            printf("  Echo Reply (Pong)\n");
            break;
        case ICMP_DEST_UNREACH:
            printf("  Destination Unreachable\n");
            break;
        case ICMP_TIME_EXCEEDED:
            printf("  Time Exceeded\n");
            break;
        default:
            printf("  Other ICMP message\n");
            break;
    }
    
    stats.icmp++;
}

// Process packet
void process_packet(unsigned char *buffer, int size) {
    (void)size;  // Suppress unused parameter warning
    struct ethhdr *eth = (struct ethhdr *)buffer;
    
    stats.total++;
    
    printf("\n[Packet #%d] ----------------------------------------\n", stats.total);
    
    // Print Ethernet header
    print_ethernet(buffer);
    
    // Check if it's an IP packet
    if (ntohs(eth->h_proto) == ETH_P_IP) {
        struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        
        // Print IP header
        print_ip(buffer);
        
        // Check protocol and print appropriate header
        switch (ip->protocol) {
            case IPPROTO_TCP:
                print_tcp(buffer);
                break;
            case IPPROTO_UDP:
                print_udp(buffer);
                break;
            case IPPROTO_ICMP:
                print_icmp(buffer);
                break;
            default:
                stats.other++;
                break;
        }
    } else {
        stats.other++;
    }
}

// Enable promiscuous mode on interface
int enable_promiscuous_mode(int sock, const char *interface) {
    struct ifreq ifr;
    
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);
    
    // Get current flags
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("Failed to get interface flags");
        return -1;
    }
    
    // Set promiscuous mode
    ifr.ifr_flags |= IFF_PROMISC;
    
    if (ioctl(sock, SIOCSIFFLAGS, &ifr) == -1) {
        perror("Failed to set promiscuous mode");
        return -1;
    }
    
    printf("Promiscuous mode enabled on %s\n", interface);
    return 0;
}

// Print statistics
void print_statistics() {
    printf("\n=== Statistics ===\n");
    printf("Total Packets: %d\n", stats.total);
    printf("TCP: %d\n", stats.tcp);
    printf("UDP: %d\n", stats.udp);
    printf("ICMP: %d\n", stats.icmp);
    printf("Other: %d\n", stats.other);
}

int main(int argc, char *argv[]) {
    int sock;
    unsigned char buffer[BUFFER_SIZE];
    ssize_t data_size;
    const char *interface = "eth0";
    int max_packets = -1;  // -1 means capture indefinitely
    
    printf("=== Network Packet Sniffer ===\n");
    printf("WARNING: Only use on networks you own or have permission to monitor!\n\n");
    
    // Parse arguments
    if (argc >= 2) {
        interface = argv[1];
    }
    if (argc >= 3) {
        max_packets = atoi(argv[2]);
    }
    
    // Create raw socket
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("Socket creation failed. Are you running as root?");
        return 1;
    }
    
    // Enable promiscuous mode
    if (enable_promiscuous_mode(sock, interface) < 0) {
        close(sock);
        return 1;
    }
    
    // Set up signal handler
    signal(SIGINT, signal_handler);
    
    printf("Interface: %s\n", interface);
    if (max_packets > 0) {
        printf("Capturing %d packets...\n", max_packets);
    } else {
        printf("Capturing packets... (Press Ctrl+C to stop)\n");
    }
    
    // Main capture loop
    while (running && (max_packets < 0 || stats.total < max_packets)) {
        data_size = recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
        
        if (data_size < 0) {
            if (running) {
                perror("Packet receive failed");
            }
            break;
        }
        
        process_packet(buffer, data_size);
    }
    
    // Print final statistics
    print_statistics();
    
    close(sock);
    printf("\nPacket capture stopped.\n");
    
    return 0;
}
