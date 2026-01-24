# Project 0.2: Networking Fundamentals & Socket Programming

## Overview

Learn network programming from the ground up by building client-server applications in C. Understanding sockets is fundamental to all network security work.

## Learning Objectives

- Understand TCP/IP networking concepts
- Master socket programming in C
- Build client-server applications
- Learn network byte order and data serialization
- Understand common network protocols

## Concepts Covered

1. **Socket Basics**
   - Creating sockets
   - Binding to addresses
   - Listening and accepting connections
   - Connecting to servers

2. **TCP vs UDP**
   - Connection-oriented vs connectionless
   - Reliability vs speed tradeoffs
   - When to use each protocol

3. **Network Byte Order**
   - Big-endian vs little-endian
   - htonl, htons, ntohl, ntohs
   - Portability considerations

4. **Protocol Design**
   - Message framing
   - Error handling
   - State management

## Projects

### 1. Simple Echo Server
Build a basic TCP server that echoes back what clients send.

### 2. Chat Application
Create a multi-client chat server using select() or poll().

### 3. File Transfer Protocol
Implement a simple file transfer protocol over TCP.

### 4. UDP Ping Tool
Build a UDP-based ping tool to understand connectionless protocols.

## Getting Started

```bash
cd project-0.2-socket-programming

# Compile server
gcc -o echo_server echo_server.c

# Compile client
gcc -o echo_client echo_client.c

# Run in separate terminals
./echo_server
./echo_client localhost
```

## Testing Your Programs

```bash
# Test with netcat
nc localhost 8080

# Monitor with tcpdump
sudo tcpdump -i lo port 8080

# Check listening ports
netstat -tuln | grep 8080
```

## Exercises

1. **Exercise 1**: Modify the echo server to handle multiple clients
2. **Exercise 2**: Add authentication to the chat server
3. **Exercise 3**: Implement timeouts and reconnection logic
4. **Exercise 4**: Build a simple HTTP server

## Common Pitfalls

- Forgetting to use network byte order
- Not handling partial sends/receives
- Not closing sockets properly
- Not handling SIGPIPE on broken connections

## Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Unix Network Programming (Stevens)](https://www.amazon.com/Unix-Network-Programming-Sockets-Networking/dp/0131411551)
- [TCP/IP Illustrated](https://www.amazon.com/TCP-Illustrated-Volume-Implementation/dp/0201633469)

## Next Steps

After completing this project, move on to Project 0.3: Assembly Language.
