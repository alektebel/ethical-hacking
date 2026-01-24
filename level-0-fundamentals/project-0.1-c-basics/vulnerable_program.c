/*
 * Vulnerable Program - Intentionally Insecure for Learning
 * 
 * WARNING: This program contains deliberate security vulnerabilities.
 * Use only in a controlled environment for educational purposes!
 * 
 * Vulnerabilities included:
 * 1. Buffer overflow
 * 2. Format string vulnerability
 * 3. Integer overflow
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VULNERABILITY 1: Buffer Overflow
void vulnerable_function(char *input) {
    char buffer[64];
    
    printf("\n=== Buffer Overflow Vulnerability ===\n");
    printf("Buffer size: 64 bytes\n");
    printf("Input size: %lu bytes\n", strlen(input));
    
    // DANGEROUS: No bounds checking!
    strcpy(buffer, input);
    
    printf("Copied to buffer: %s\n", buffer);
}

// VULNERABILITY 2: Format String Vulnerability
void format_string_vuln(char *user_input) {
    printf("\n=== Format String Vulnerability ===\n");
    
    // DANGEROUS: User input used directly as format string!
    printf(user_input);
    printf("\n");
    
    // SAFE version would be:
    // printf("%s", user_input);
}

// VULNERABILITY 3: Integer Overflow
void integer_overflow(unsigned int size) {
    printf("\n=== Integer Overflow Vulnerability ===\n");
    printf("Requested size: %u\n", size);
    
    // Calculate total size (can overflow!)
    unsigned int total = size * sizeof(int);
    printf("Calculated total: %u bytes\n", total);
    
    // This could allocate much less memory than expected!
    int *buffer = (int*)malloc(total);
    if (buffer == NULL) {
        printf("Allocation failed!\n");
        return;
    }
    
    printf("Allocated at: %p\n", (void*)buffer);
    
    // If overflow occurred, this could write beyond allocated memory
    // for (unsigned int i = 0; i < size; i++) {
    //     buffer[i] = i;  // DANGEROUS if overflow occurred!
    // }
    
    free(buffer);
}

// Safe version of buffer copy
void safe_function(char *input) {
    char buffer[64];
    
    printf("\n=== Safe Version ===\n");
    
    // Use strncpy with size check
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    printf("Safely copied: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    printf("==============================================\n");
    printf("Vulnerable Program - Educational Purposes Only\n");
    printf("==============================================\n");
    
    if (argc < 2) {
        printf("\nUsage: %s <mode>\n", argv[0]);
        printf("Modes:\n");
        printf("  1 - Buffer overflow demo\n");
        printf("  2 - Format string demo\n");
        printf("  3 - Integer overflow demo\n");
        printf("  4 - Safe version demo\n");
        return 1;
    }
    
    int mode = atoi(argv[1]);
    
    switch (mode) {
        case 1:
            printf("\nDemo: Buffer Overflow\n");
            printf("Try: ./vulnerable_program 1\n");
            printf("This demonstrates how strcpy can overflow a buffer\n");
            vulnerable_function("This is a normal string");
            
            printf("\nNow with a longer string...\n");
            char long_input[100];
            memset(long_input, 'A', 99);
            long_input[99] = '\0';
            vulnerable_function(long_input);
            break;
            
        case 2:
            printf("\nDemo: Format String Vulnerability\n");
            printf("Normal use:\n");
            format_string_vuln("Hello World");
            
            printf("\nWith format specifiers:\n");
            format_string_vuln("Value: %x %x %x %x");
            break;
            
        case 3:
            printf("\nDemo: Integer Overflow\n");
            printf("Normal allocation:\n");
            integer_overflow(100);
            
            printf("\nOversized allocation (potential overflow):\n");
            integer_overflow(0xFFFFFFFF / 2);
            break;
            
        case 4:
            printf("\nDemo: Safe Implementation\n");
            safe_function("This is a normal string");
            
            char long_input[100];
            memset(long_input, 'A', 99);
            long_input[99] = '\0';
            safe_function(long_input);
            break;
            
        default:
            printf("Invalid mode. Use 1-4.\n");
            return 1;
    }
    
    printf("\n=== Learning Points ===\n");
    printf("1. Never use strcpy - use strncpy or strlcpy\n");
    printf("2. Never use user input as format string\n");
    printf("3. Always validate integer calculations\n");
    printf("4. Compile with -fstack-protector to detect some issues\n");
    printf("5. Use static analysis tools (e.g., Flawfinder, Cppcheck)\n");
    
    return 0;
}
