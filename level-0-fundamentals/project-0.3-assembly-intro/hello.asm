; hello.asm - Hello World in x86-64 Assembly
; This demonstrates basic syscalls and string output
;
; Assemble: nasm -f elf64 hello.asm -o hello.o
; Link:     ld hello.o -o hello
; Run:      ./hello

section .data
    ; Define our message
    message db 'Hello, Assembly World!', 0x0a  ; 0x0a = newline
    message_len equ $ - message                 ; Calculate length

section .text
    global _start

_start:
    ; Write to stdout
    ; syscall number 1 = write
    ; rdi = file descriptor (1 = stdout)
    ; rsi = buffer address
    ; rdx = buffer length
    
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; fd: stdout
    mov rsi, message        ; buffer
    mov rdx, message_len    ; length
    syscall                 ; invoke syscall
    
    ; Exit program
    ; syscall number 60 = exit
    ; rdi = exit code
    
    mov rax, 60             ; syscall: exit
    mov rdi, 0              ; exit code 0
    syscall                 ; invoke syscall
