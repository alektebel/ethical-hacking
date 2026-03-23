# Project 2.2: Network Packet Sniffer

Learn to capture and analyze network traffic by building a packet sniffer from scratch.

## 🎯 Learning Objectives

- Understand how packet capture works at a low level
- Learn about promiscuous mode and raw sockets
- Parse network protocols (Ethernet, IP, TCP, UDP, ICMP)
- Analyze network traffic patterns
- Build a foundation for network security analysis

## 📚 Concepts Covered

### Packet Capture Basics
- **Promiscuous Mode**: Interface captures all packets on the network, not just those destined for it
- **Raw Sockets**: Low-level access to network packets
- **Packet Filtering**: Capturing specific types of traffic
- **Protocol Parsing**: Extracting information from packet headers

### Network Protocols
- **Ethernet Frame**: MAC addresses, frame types
- **IP Header**: Source/destination IPs, protocol, TTL
- **TCP Header**: Ports, flags (SYN, ACK, FIN, etc.), sequence numbers
- **UDP Header**: Ports, datagram structure
- **ICMP**: Ping requests/replies, error messages

### Security Applications
- **Network Monitoring**: Detecting suspicious traffic
- **Protocol Analysis**: Understanding network communication
- **Troubleshooting**: Diagnosing network issues
- **Intrusion Detection**: Identifying attack patterns

## 🛠️ Implementation

### Basic Packet Sniffer (`packet_sniffer.c`)

A command-line packet sniffer that captures and displays network traffic with the following features:

**Features:**
- Raw socket creation for packet capture
- Promiscuous mode setup
- Protocol identification (TCP, UDP, ICMP)
- Header parsing and display
- Packet count statistics
- Optional packet filtering

**Key Functions:**
- `create_raw_socket()`: Creates a raw socket for packet capture
- `enable_promiscuous_mode()`: Enables promiscuous mode on network interface
- `parse_ethernet()`: Extracts Ethernet frame information
- `parse_ip()`: Parses IP header
- `parse_tcp()`: Parses TCP header
- `parse_udp()`: Parses UDP header
- `parse_icmp()`: Parses ICMP packet
- `print_packet_info()`: Displays packet details

## 📖 How It Works

1. **Socket Creation**: Creates a raw socket with `AF_PACKET` to receive all packets
2. **Promiscuous Mode**: Sets the network interface to capture all traffic
3. **Packet Reception**: Receives packets using `recvfrom()`
4. **Protocol Parsing**: Analyzes packet structure starting from Ethernet frame
5. **Display**: Shows relevant information (IPs, ports, protocols, flags)

## 🚀 Building and Running

### Compilation
```bash
make
```

### Running the Sniffer
```bash
# Requires root privileges
sudo ./packet_sniffer [interface] [count]

# Examples:
sudo ./packet_sniffer eth0           # Capture on eth0 indefinitely
sudo ./packet_sniffer eth0 100       # Capture 100 packets on eth0
sudo ./packet_sniffer wlan0 50       # Capture 50 packets on wlan0
```

### Testing
```bash
# Test on loopback interface
make test
```

## 📊 Example Output

```
=== Network Packet Sniffer ===
Interface: eth0
Capturing packets... (Press Ctrl+C to stop)

[Packet #1] ----------------------------------------
Ethernet: 08:00:27:12:34:56 -> ff:ff:ff:ff:ff:ff
Protocol: IP (0x0800)
IP: 192.168.1.100 -> 192.168.1.255 (UDP)
  TTL: 64, Length: 229
UDP: 68 -> 67
  Length: 209

[Packet #2] ----------------------------------------
Ethernet: 08:00:27:12:34:56 -> 52:54:00:12:35:02
Protocol: IP (0x0800)
IP: 192.168.1.100 -> 8.8.8.8 (TCP)
  TTL: 64, Length: 60
TCP: 45678 -> 443
  Flags: [SYN]
  Seq: 1234567890

[Packet #3] ----------------------------------------
Ethernet: 52:54:00:12:35:02 -> 08:00:27:12:34:56
Protocol: IP (0x0800)
IP: 8.8.8.8 -> 192.168.1.100 (TCP)
  TTL: 54, Length: 60
TCP: 443 -> 45678
  Flags: [SYN, ACK]
  Seq: 9876543210, Ack: 1234567891

=== Statistics ===
Total Packets: 3
TCP: 2
UDP: 1
ICMP: 0
Other: 0
```

## 🔍 Understanding the Code

### Raw Socket Creation
```c
// Create raw socket for packet capture
int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
```
- `AF_PACKET`: Access to raw packets
- `SOCK_RAW`: Raw socket type
- `ETH_P_ALL`: Capture all protocols

### Promiscuous Mode
```c
// Set interface to promiscuous mode
struct ifreq ifr;
ioctl(sock, SIOCGIFFLAGS, &ifr);
ifr.ifr_flags |= IFF_PROMISC;
ioctl(sock, SIOCSIFFLAGS, &ifr);
```

### Protocol Headers
Each protocol has a specific header structure:
- **Ethernet**: 14 bytes (dst MAC, src MAC, type)
- **IP**: Variable (minimum 20 bytes)
- **TCP**: Variable (minimum 20 bytes)
- **UDP**: 8 bytes

## 💡 Exercises

### Beginner
1. Modify the sniffer to only capture TCP packets
2. Add a filter to capture packets from a specific IP address
3. Count packets by protocol type and display statistics

### Intermediate
4. Implement HTTP header extraction from TCP packets
5. Add DNS query/response parsing
6. Save captured packets to a PCAP file format

### Advanced
7. Implement packet reassembly for fragmented IP packets
8. Add pattern matching to detect specific payloads
9. Create a simple intrusion detection system (IDS) that alerts on suspicious patterns
10. Implement BPF (Berkeley Packet Filter) for efficient filtering

## ⚠️ Legal and Ethical Considerations

**CRITICAL WARNING**: Packet sniffing has serious legal and ethical implications.

### Legal Issues
- Intercepting network traffic without authorization is **illegal** in most jurisdictions
- Violates laws like:
  - Computer Fraud and Abuse Act (CFAA) in the USA
  - Computer Misuse Act in the UK
  - Similar laws in most countries
- Can result in criminal charges and imprisonment

### When Packet Sniffing is Legal
- ✅ Your own network and devices
- ✅ Corporate networks with explicit written authorization
- ✅ Security audits with proper contracts
- ✅ Penetration testing engagements (with scope agreement)
- ✅ Educational purposes on isolated lab networks

### Ethical Guidelines
1. **Only capture traffic on networks you own**
2. **Never intercept other people's communications**
3. **Respect privacy** - even on your own network, be mindful of others
4. **Secure captured data** - packet captures may contain sensitive information
5. **Get written permission** for any professional testing
6. **Use for defense, not attack** - improve security, don't compromise it

### Best Practices
- Test in isolated virtual environments (VirtualBox, VMware)
- Use your own VPN or test servers
- Never save or share captured credentials or personal data
- Delete packet captures containing sensitive information
- Understand your organization's policies before using sniffers at work

## 🔧 Prerequisites

- Completed Level 0 and Level 1 projects
- Understanding of TCP/IP and network protocols
- Root/sudo access (required for raw sockets)
- Basic knowledge of C structures and pointers

## 📚 Additional Resources

- **tcpdump**: Command-line packet analyzer
- **Wireshark**: GUI packet analyzer (compare your results)
- **libpcap**: Packet capture library (for advanced projects)
- RFC 791 (IP), RFC 793 (TCP), RFC 768 (UDP)

## ⏱️ Estimated Time

- Understanding concepts: 3-4 hours
- Implementation: 10-15 hours
- Testing and experimentation: 5-8 hours
- Total: 2-3 weeks (with other commitments)

## 🎓 What You'll Learn

By completing this project, you'll understand:
- How network monitoring tools like Wireshark work internally
- The structure of network packets at the byte level
- How to analyze network traffic programmatically
- The foundation for building network security tools
- Practical skills for network troubleshooting and analysis

---

**Remember**: "With great power comes great responsibility." Use packet sniffing only for legitimate purposes on networks you own or have explicit permission to monitor.
