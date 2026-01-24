; calculator.asm - Simple Assembly Calculator
; Demonstrates arithmetic operations and stack usage
;
; Assemble: nasm -f elf64 calculator.asm -o calculator.o
; Link:     ld calculator.o -o calculator

section .data
    msg_result db 'Result: ', 0
    msg_result_len equ $ - msg_result
    newline db 0x0a
    
section .bss
    result_buffer resb 20   ; Buffer for number to string conversion

section .text
    global _start

; Function: add two numbers
; Parameters: rdi = first number, rsi = second number
; Returns: rax = result
add_numbers:
    mov rax, rdi
    add rax, rsi
    ret

; Function: subtract two numbers
; Parameters: rdi = first number, rsi = second number
; Returns: rax = result
subtract_numbers:
    mov rax, rdi
    sub rax, rsi
    ret

; Function: multiply two numbers
; Parameters: rdi = first number, rsi = second number
; Returns: rax = result
multiply_numbers:
    mov rax, rdi
    imul rax, rsi
    ret

; Function: print a number
; Parameters: rdi = number to print
print_number:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    
    mov rax, rdi        ; Number to convert
    mov rbx, 10         ; Divisor
    mov rcx, 0          ; Digit counter
    
    ; Handle zero case
    test rax, rax
    jnz .convert_loop
    
    mov byte [result_buffer], '0'
    mov rcx, 1
    jmp .print
    
.convert_loop:
    ; Check if done
    test rax, rax
    jz .reverse
    
    ; Get remainder (digit)
    xor rdx, rdx
    div rbx
    
    ; Convert to ASCII and push
    add rdx, '0'
    push rdx
    inc rcx
    
    jmp .convert_loop
    
.reverse:
    ; Pop digits and store in buffer
    mov r12, 0
.pop_loop:
    test rcx, rcx
    jz .print
    
    pop rdx
    mov byte [result_buffer + r12], dl
    inc r12
    dec rcx
    
    jmp .pop_loop
    
.print:
    ; Print the buffer
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; stdout
    mov rsi, result_buffer  ; buffer
    mov rdx, r12            ; length
    syscall
    
    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall
    
    pop r12
    pop rbx
    pop rbp
    ret

_start:
    ; Print header
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_result
    mov rdx, msg_result_len
    syscall
    
    ; Example: 15 + 27 = 42
    mov rdi, 15
    mov rsi, 27
    call add_numbers
    
    mov rdi, rax
    call print_number
    
    ; Example: 50 - 8 = 42
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_result
    mov rdx, msg_result_len
    syscall
    
    mov rdi, 50
    mov rsi, 8
    call subtract_numbers
    
    mov rdi, rax
    call print_number
    
    ; Example: 6 * 7 = 42
    mov rax, 1
    mov rdi, 1
    mov rsi, msg_result
    mov rdx, msg_result_len
    syscall
    
    mov rdi, 6
    mov rsi, 7
    call multiply_numbers
    
    mov rdi, rax
    call print_number
    
    ; Exit
    mov rax, 60
    mov rdi, 0
    syscall
