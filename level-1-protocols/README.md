# Level 1: Network Protocols

Now that you understand the fundamentals, it's time to dive deep into network protocols by implementing them yourself.

## Why Implement Protocols?

The best way to understand how networks work is to build the protocols from scratch. This level teaches you:
- How TCP/IP really works under the hood
- How to craft custom packets
- How protocols can be exploited
- The foundation for building network tools

## Projects in This Level

### Project 1.1: Raw Sockets & Packet Crafting
Learn to create and send custom network packets using raw sockets.

**Topics Covered:**
- Raw socket creation
- IP header construction
- Checksum calculation
- Packet injection

### Project 1.2: TCP/IP Protocol Implementation
Build a simplified TCP/IP stack to understand connection management.

**Topics Covered:**
- TCP three-way handshake
- Sequence numbers
- Connection state management
- Reliable delivery

### Project 1.3: DNS Protocol & Queries
Implement a DNS client and understand how domain name resolution works.

**Topics Covered:**
- DNS packet format
- Query types (A, AAAA, MX, etc.)
- DNS recursion
- DNS spoofing basics

## Prerequisites

Before starting Level 1, you should have completed:
- Level 0: Fundamentals
- Understanding of C programming
- Basic socket programming knowledge
- Network protocol basics

## Tools You'll Need

- Wireshark (for packet analysis)
- tcpdump (for packet capture)
- netcat (for testing)
- Root/sudo access (for raw sockets)

## Important Notes

⚠️ **Raw sockets require root privileges**
Many projects in this level need root/sudo to create raw sockets and manipulate packets.

⚠️ **Use in isolated networks**
Test these tools only on networks you control. Packet injection can disrupt networks.

## Estimated Time

- Project 1.1: 2-3 weeks
- Project 1.2: 3-4 weeks
- Project 1.3: 2-3 weeks

## Next Level

After completing Level 1, proceed to Level 2: Network Scanning & Reconnaissance.
