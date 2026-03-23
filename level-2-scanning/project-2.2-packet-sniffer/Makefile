CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = packet_sniffer

all: $(PROGRAMS)

packet_sniffer: packet_sniffer.c
	$(CC) $(CFLAGS) -o packet_sniffer packet_sniffer.c

clean:
	rm -f $(PROGRAMS) *.o

test: packet_sniffer
	@echo "Testing packet sniffer on loopback interface..."
	@echo "Note: This requires root privileges"
	@echo "Capturing 10 packets on lo (loopback) interface:"
	@sudo ./packet_sniffer lo 10 || echo "Test requires root privileges. Run: sudo make test"

.PHONY: all clean test
