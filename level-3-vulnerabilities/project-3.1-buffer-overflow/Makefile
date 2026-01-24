CC = gcc
CFLAGS = -Wall -Wextra -g

# Vulnerable version (no protections)
UNSAFE_FLAGS = -fno-stack-protector -z execstack -no-pie

# Safe version (with protections)
SAFE_FLAGS = -fstack-protector-all -D_FORTIFY_SOURCE=2

PROGRAMS = vuln_bof vuln_bof_safe

all: $(PROGRAMS)

vuln_bof: vuln_bof.c
	$(CC) $(CFLAGS) $(UNSAFE_FLAGS) -o vuln_bof vuln_bof.c
	@echo "WARNING: vuln_bof compiled without protections for educational purposes"

vuln_bof_safe: vuln_bof.c
	$(CC) $(CFLAGS) $(SAFE_FLAGS) -o vuln_bof_safe vuln_bof.c
	@echo "vuln_bof_safe compiled with security protections enabled"

clean:
	rm -f $(PROGRAMS) *.o core

test: vuln_bof
	@echo "Running vulnerable program with safe input..."
	@echo "This is a test" | ./vuln_bof
	@echo ""
	@echo "For exploitation practice, run: ./vuln_bof help"

.PHONY: all clean test
