AS = nasm
LD = ld
ASFLAGS = -f elf64
LDFLAGS = 

PROGRAMS = hello calculator shellcode

all: $(PROGRAMS)

hello: hello.asm
	$(AS) $(ASFLAGS) hello.asm -o hello.o
	$(LD) $(LDFLAGS) hello.o -o hello

calculator: calculator.asm
	$(AS) $(ASFLAGS) calculator.asm -o calculator.o
	$(LD) $(LDFLAGS) calculator.o -o calculator

shellcode: shellcode.asm
	$(AS) $(ASFLAGS) shellcode.asm -o shellcode.o
	$(LD) $(LDFLAGS) shellcode.o -o shellcode

shellcode_bytes: shellcode
	@echo "Extracting shellcode bytes..."
	objcopy -O binary --only-section=.text shellcode shellcode.bin
	xxd -i shellcode.bin

clean:
	rm -f *.o $(PROGRAMS) shellcode.bin

test: all
	@echo "Running hello..."
	./hello
	@echo "\nRunning calculator..."
	./calculator
	@echo "\nShellcode (run manually in safe environment):"
	@echo "./shellcode"

.PHONY: all clean test shellcode_bytes
