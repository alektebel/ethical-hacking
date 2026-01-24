CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

PROGRAMS = port_scanner

all: $(PROGRAMS)

port_scanner: port_scanner.c
	$(CC) $(CFLAGS) -o port_scanner port_scanner.c

clean:
	rm -f $(PROGRAMS) *.o

test: port_scanner
	@echo "Testing port scanner on localhost..."
	@echo "Only scanning well-known ports (1-100)"
	./port_scanner 127.0.0.1 1 100

.PHONY: all clean test
