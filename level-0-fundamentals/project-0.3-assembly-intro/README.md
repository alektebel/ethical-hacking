# Project 0.3: Introduction to Assembly Language

## Overview

Learn to read and write x86-64 assembly language. This is crucial for understanding exploits, reverse engineering, and what's really happening at the CPU level.

## Learning Objectives

- Understand CPU registers and their purposes
- Learn basic assembly instructions
- Understand the stack and calling conventions
- Read disassembled code
- Write simple shellcode

## Concepts Covered

1. **CPU Architecture**
   - Registers (RAX, RBX, RCX, RDX, RSI, RDI, RSP, RBP, RIP)
   - Flags register
   - Instruction pointer

2. **Assembly Instructions**
   - MOV, PUSH, POP
   - ADD, SUB, MUL, DIV
   - JMP, CALL, RET
   - CMP, TEST

3. **The Stack**
   - Stack frame layout
   - Function prologue/epilogue
   - Local variables
   - Return addresses

4. **Calling Conventions**
   - System V AMD64 ABI (Linux)
   - Parameter passing
   - Return values

## Projects

### 1. Hello World in Assembly
The classic first program, written in pure assembly.

### 2. Simple Calculator
Build a calculator that performs basic arithmetic operations.

### 3. Function Calls
Understand how functions are called and return.

### 4. Basic Shellcode
Write position-independent code that spawns a shell.

## Getting Started

```bash
cd project-0.3-assembly-intro

# Assemble with NASM
nasm -f elf64 hello.asm -o hello.o

# Link
ld hello.o -o hello

# Run
./hello
```

## Debugging Assembly

```bash
# Debug with GDB
gdb ./hello
(gdb) break _start
(gdb) run
(gdb) stepi          # Step one instruction
(gdb) info registers # Show all registers
(gdb) x/10i $rip     # Examine next 10 instructions

# Disassemble existing binary
objdump -d ./hello -M intel
```

## Exercises

1. **Exercise 1**: Write a program that adds two numbers
2. **Exercise 2**: Implement a loop that counts from 1 to 10
3. **Exercise 3**: Write a function that calculates factorial
4. **Exercise 4**: Create position-independent shellcode

## Tips

- Use Intel syntax (easier to read than AT&T syntax)
- Comment your code heavily - assembly is hard to read
- Use GDB to step through and watch registers
- Start simple and build complexity gradually

## Common Pitfalls

- Forgetting to preserve registers
- Stack misalignment (must be 16-byte aligned on function calls)
- Not null-terminating strings
- Using wrong syscall numbers

## Resources

- [x86-64 Instruction Reference](https://www.felixcloutier.com/x86/)
- [System V AMD64 ABI](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)
- [Shellcoder's Handbook](https://www.amazon.com/Shellcoders-Handbook-Discovering-Exploiting-Security/dp/047008023X)
- [NASM Documentation](https://www.nasm.us/doc/)

## Next Steps

After completing this project, you're ready for Level 1: Network Protocols!
