/*
 * Memory Basics - Understanding Pointers and Memory Management
 * 
 * This program demonstrates fundamental memory concepts in C that are
 * crucial for understanding security vulnerabilities.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to demonstrate stack memory
void stack_example() {
    int stack_var = 42;
    int stack_array[5] = {1, 2, 3, 4, 5};
    
    printf("\n=== Stack Memory Example ===\n");
    printf("Stack variable value: %d\n", stack_var);
    printf("Stack variable address: %p\n", (void*)&stack_var);
    printf("Stack array address: %p\n", (void*)stack_array);
    printf("Size of stack array: %lu bytes\n", sizeof(stack_array));
    
    // Show that stack grows downward (usually)
    int another_var;
    printf("Another var address: %p\n", (void*)&another_var);
    printf("Stack direction: %s\n", 
           &another_var < &stack_var ? "grows down" : "grows up");
}

// Function to demonstrate heap memory
void heap_example() {
    printf("\n=== Heap Memory Example ===\n");
    
    // Allocate memory on heap
    int *heap_ptr = (int*)malloc(sizeof(int) * 5);
    if (heap_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    
    // Initialize heap memory
    for (int i = 0; i < 5; i++) {
        heap_ptr[i] = i * 10;
    }
    
    printf("Heap array address: %p\n", (void*)heap_ptr);
    printf("Heap array values: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", heap_ptr[i]);
    }
    printf("\n");
    
    // ALWAYS free allocated memory!
    free(heap_ptr);
    printf("Memory freed (but pointer still holds address: %p)\n", (void*)heap_ptr);
    
    // Good practice: set to NULL after freeing
    heap_ptr = NULL;
}

// Function to demonstrate pointer arithmetic
void pointer_arithmetic() {
    printf("\n=== Pointer Arithmetic ===\n");
    
    int numbers[5] = {10, 20, 30, 40, 50};
    int *ptr = numbers;
    
    printf("Array address: %p\n", (void*)numbers);
    printf("Pointer address: %p\n", (void*)ptr);
    
    // Accessing array elements using pointer arithmetic
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d, address: %p\n", 
               i, *(ptr + i), (void*)(ptr + i));
    }
    
    // Show size differences
    printf("\nPointer increments by %lu bytes (sizeof(int))\n", sizeof(int));
}

// Function to demonstrate dangerous operations (educational purposes)
void dangerous_operations() {
    printf("\n=== Dangerous Operations (Educational) ===\n");
    
    // 1. Buffer overflow example (DANGEROUS!)
    char small_buffer[8];
    printf("Small buffer address: %p, size: %lu\n", 
           (void*)small_buffer, sizeof(small_buffer));
    
    // SAFE operation
    strncpy(small_buffer, "Hello", sizeof(small_buffer) - 1);
    small_buffer[sizeof(small_buffer) - 1] = '\0';
    printf("Safe copy: %s\n", small_buffer);
    
    // 2. Memory leak example
    printf("\nMemory leak example:\n");
    for (int i = 0; i < 3; i++) {
        int *leak = (int*)malloc(sizeof(int));
        printf("Allocated memory at: %p (iteration %d)\n", (void*)leak, i);
        // OOPS! Never freed - this is a memory leak!
        // In a real program, you would: free(leak);
    }
    printf("Warning: Memory leaked! Should use valgrind to detect.\n");
    
    // 3. Use-after-free example
    printf("\nUse-after-free example:\n");
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 100;
    printf("Before free: %d at %p\n", *ptr, (void*)ptr);
    free(ptr);
    // DANGEROUS: Using pointer after free!
    printf("After free (DANGEROUS!): address still %p\n", (void*)ptr);
    // printf("Value: %d\n", *ptr); // This would be use-after-free bug!
}

// Function to demonstrate safe string handling
void safe_string_handling() {
    printf("\n=== Safe String Handling ===\n");
    
    char buffer[16];
    const char *long_string = "This is a very long string that won't fit";
    
    // UNSAFE: strcpy(buffer, long_string); // Buffer overflow!
    
    // SAFE: Use strncpy
    strncpy(buffer, long_string, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null termination
    
    printf("Safely copied (truncated): %s\n", buffer);
    printf("Original string: %s\n", long_string);
    
    // Better: Use snprintf
    char buffer2[16];
    snprintf(buffer2, sizeof(buffer2), "%s", long_string);
    printf("Using snprintf: %s\n", buffer2);
}

int main() {
    printf("==============================================\n");
    printf("Memory Basics - Educational Security Demo\n");
    printf("==============================================\n");
    
    stack_example();
    heap_example();
    pointer_arithmetic();
    dangerous_operations();
    safe_string_handling();
    
    printf("\n=== Summary ===\n");
    printf("Key takeaways:\n");
    printf("1. Stack memory is automatic, heap requires manual management\n");
    printf("2. Always free() what you malloc()\n");
    printf("3. Use safe string functions (strncpy, snprintf)\n");
    printf("4. Check buffer boundaries\n");
    printf("5. Set pointers to NULL after freeing\n");
    printf("\nRun with valgrind to detect memory issues:\n");
    printf("  valgrind --leak-check=full ./memory_basics\n");
    
    return 0;
}
