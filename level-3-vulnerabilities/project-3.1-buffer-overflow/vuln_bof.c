/*
 * Buffer Overflow Example - Educational Vulnerable Program
 * 
 * WARNING: This program contains intentional security vulnerabilities
 * for educational purposes only. Compile with protections disabled.
 * 
 * Compile: gcc -fno-stack-protector -z execstack -no-pie -o vuln_bof vuln_bof.c
 * Run:     ./vuln_bof
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A function we want to call through exploitation
void secret_function() {
    printf("\n");
    printf("=================================\n");
    printf("🎉 SUCCESS! Secret function called!\n");
    printf("=================================\n");
    printf("\nYou successfully exploited the buffer overflow!\n");
    printf("In a real exploit, this could be:\n");
    printf("- Spawning a shell\n");
    printf("- Escalating privileges\n");
    printf("- Executing arbitrary code\n");
    printf("\n");
}

// Vulnerable function with buffer overflow
void vulnerable_function(char *input) {
    char buffer[64];
    
    printf("\n=== Vulnerable Function ===\n");
    printf("Buffer address: %p\n", (void*)buffer);
    printf("Buffer size: 64 bytes\n");
    printf("Input length: %lu bytes\n\n", strlen(input));
    
    // VULNERABILITY: No bounds checking!
    strcpy(buffer, input);
    
    printf("Buffer contents: %s\n", buffer);
}

// Safe version for comparison
void safe_function(char *input) {
    char buffer[64];
    
    printf("\n=== Safe Function ===\n");
    
    // SAFE: Using strncpy with proper size
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    printf("Buffer contents: %s\n", buffer);
}

void print_instructions() {
    printf("\n=== Buffer Overflow Tutorial ===\n\n");
    
    printf("This program demonstrates a classic stack buffer overflow.\n");
    printf("The vulnerable_function has a 64-byte buffer but uses strcpy\n");
    printf("without bounds checking.\n\n");
    
    printf("EXPLOITATION STEPS:\n");
    printf("1. Find the offset to the return address\n");
    printf("2. Overwrite the return address with target function address\n");
    printf("3. The program will jump to your target when function returns\n\n");
    
    printf("SECRET FUNCTION ADDRESS: %p\n\n", (void*)secret_function);
    
    printf("EXAMPLE EXPLOIT:\n");
    printf("$ python -c 'print(\"A\"*72 + \"\\x??\\x??\\x??\\x??\\x??\\x??\\x??\\x??\")' | ./vuln_bof\n");
    printf("(Replace ?? with the secret_function address in little-endian)\n\n");
    
    printf("DEBUG WITH GDB:\n");
    printf("$ gdb ./vuln_bof\n");
    printf("(gdb) run < <(python -c 'print(\"A\"*100)')\n");
    printf("(gdb) info registers\n");
    printf("(gdb) x/20x $rsp\n\n");
}

int main(int argc, char *argv[]) {
    char input[256];
    
    printf("==============================================\n");
    printf("Buffer Overflow Educational Program\n");
    printf("==============================================\n");
    
    if (argc > 1) {
        if (strcmp(argv[1], "help") == 0) {
            print_instructions();
            return 0;
        }
    }
    
    printf("\nEnter input (or 'help' for exploitation guide): ");
    fflush(stdout);
    
    // Read input
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    // Remove newline
    input[strcspn(input, "\n")] = 0;
    
    if (strcmp(input, "help") == 0) {
        print_instructions();
        return 0;
    }
    
    if (strcmp(input, "safe") == 0) {
        safe_function("This is a safe string that will be truncated if too long - AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        return 0;
    }
    
    // Call vulnerable function
    vulnerable_function(input);
    
    printf("\nProgram completed normally.\n");
    printf("(If you see this, the exploit didn't work)\n");
    
    return 0;
}
