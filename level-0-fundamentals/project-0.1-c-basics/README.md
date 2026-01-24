# Project 0.1: C Programming Basics & Memory Management

## Overview

Master C programming with a security perspective. This project teaches you to write C code while understanding common vulnerabilities.

## Learning Objectives

- Understand pointers and memory management
- Recognize buffer overflow conditions
- Learn safe string handling
- Understand the stack and heap

## Concepts Covered

1. **Pointers and Memory Addresses**
   - How memory works
   - Pointer arithmetic
   - NULL pointers

2. **Dynamic Memory Management**
   - malloc/calloc/realloc/free
   - Memory leaks
   - Use-after-free bugs

3. **Buffers and Arrays**
   - Fixed vs dynamic buffers
   - String handling (strcpy vs strncpy)
   - Buffer overflows

## Projects

### 1. Memory Visualizer
Build a program that shows how memory is allocated and freed.

### 2. Safe String Library
Implement safe string functions that prevent buffer overflows.

### 3. Vulnerable Program
Create a simple program with deliberate vulnerabilities to learn what NOT to do.

## Getting Started

```bash
cd project-0.1-c-basics
gcc -o memory_basics memory_basics.c
./memory_basics
```

## Compilation Tips

For debugging:
```bash
gcc -g -Wall -Wextra -o program program.c
```

For security analysis:
```bash
gcc -fstack-protector-all -D_FORTIFY_SOURCE=2 -o program program.c
```

## Exercises

1. **Exercise 1**: Write a program that demonstrates the difference between stack and heap memory
2. **Exercise 2**: Create a buffer overflow vulnerability and exploit it (safely!)
3. **Exercise 3**: Implement bounds checking for array access

## Resources

- [C Programming: A Modern Approach](http://knking.com/books/c2/)
- [The C Programming Language (K&R)](https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628)
- [Secure Coding in C and C++](https://www.amazon.com/Secure-Coding-2nd-Software-Engineering/dp/0321822137)

## Next Steps

After completing this project, move on to Project 0.2: Socket Programming.
