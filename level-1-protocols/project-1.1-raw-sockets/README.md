# Project 1.1: Raw Sockets & Packet Crafting

## Overview

Learn to create and send custom network packets using raw sockets. This is the foundation for building network scanning tools and understanding packet-level networking.

## Learning Objectives

- Create raw sockets in C
- Construct IP and TCP/UDP headers manually
- Calculate network checksums
- Send custom packets
- Understand packet structure at the byte level

## Concepts Covered

1. **Raw Sockets**
   - Why use raw sockets
   - Permission requirements
   - Socket options (IP_HDRINCL)

2. **IP Header**
   - Version, IHL, TOS
   - Total length, identification
   - Flags, fragment offset
   - TTL, protocol, checksum
   - Source and destination addresses

3. **TCP/UDP Headers**
   - Port numbers
   - Sequence/acknowledgment numbers
   - Flags (SYN, ACK, FIN, etc.)
   - Window size, checksum

4. **Checksum Calculation**
   - Internet checksum algorithm
   - Pseudo-header for TCP/UDP

## Projects

### 1. ICMP Ping Tool
Build your own ping utility using raw ICMP packets.

### 2. SYN Packet Sender
Create a tool that sends TCP SYN packets.

### 3. Custom Packet Crafter
Build a flexible packet crafting tool.

## Getting Started

```bash
cd project-1.1-raw-sockets

# Compile
gcc -o icmp_ping icmp_ping.c

# Run (needs root!)
sudo ./icmp_ping 8.8.8.8
```

## Important Notes

⚠️ **Root Required**: Raw sockets need root/sudo privileges

⚠️ **Legal Warning**: Only use on networks you own or have permission to test

## Resources

- [RFC 791 - Internet Protocol](https://tools.ietf.org/html/rfc791)
- [RFC 793 - TCP](https://tools.ietf.org/html/rfc793)
- [RFC 768 - UDP](https://tools.ietf.org/html/rfc768)
