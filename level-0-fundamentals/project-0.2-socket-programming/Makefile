CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = echo_server echo_client

all: $(PROGRAMS)

echo_server: echo_server.c
	$(CC) $(CFLAGS) -o echo_server echo_server.c

echo_client: echo_client.c
	$(CC) $(CFLAGS) -o echo_client echo_client.c

clean:
	rm -f $(PROGRAMS) *.o

test_server: echo_server
	@echo "Starting echo server..."
	@echo "In another terminal, run: make test_client"
	./echo_server

test_client: echo_client
	./echo_client localhost

.PHONY: all clean test_server test_client
