CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = icmp_ping

all: $(PROGRAMS)

icmp_ping: icmp_ping.c
	$(CC) $(CFLAGS) -o icmp_ping icmp_ping.c

clean:
	rm -f $(PROGRAMS) *.o

test: icmp_ping
	@echo "Testing ICMP ping (requires root)..."
	@echo "Run: sudo ./icmp_ping 127.0.0.1"

.PHONY: all clean test
