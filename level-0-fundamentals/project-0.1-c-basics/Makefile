CC = gcc
CFLAGS = -Wall -Wextra -g
SAFE_FLAGS = -fstack-protector-all -D_FORTIFY_SOURCE=2
UNSAFE_FLAGS = -fno-stack-protector -z execstack

# Targets
all: memory_basics vulnerable_program safe_version

memory_basics: memory_basics.c
	$(CC) $(CFLAGS) $(SAFE_FLAGS) -o memory_basics memory_basics.c

vulnerable_program: vulnerable_program.c
	$(CC) $(CFLAGS) $(UNSAFE_FLAGS) -o vulnerable_program vulnerable_program.c
	@echo "WARNING: vulnerable_program compiled without protections for educational purposes"

safe_version: vulnerable_program.c
	$(CC) $(CFLAGS) $(SAFE_FLAGS) -o safe_version vulnerable_program.c

clean:
	rm -f memory_basics vulnerable_program safe_version *.o

test: all
	@echo "Running memory_basics..."
	./memory_basics
	@echo "\nRunning vulnerable_program demos..."
	./vulnerable_program 1
	./vulnerable_program 4

.PHONY: all clean test
