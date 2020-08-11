CC=x86_64-w64-mingw32-gcc
ASM_CC=nasm

OUTFILE=defensiveinjector.exe

all: syscalls injector

syscalls:
	$(ASM_CC) -f win64 syscalls.asm -o syscalls.lib

injector:
	$(CC) main.c -o $(OUTFILE) -L./ -lsyscalls