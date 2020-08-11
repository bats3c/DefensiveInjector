section .text

global NtOpenProcess
global NtCreateThreadEx
global NtWriteVirtualMemory
global NtAllocateVirtualMemory

NtOpenProcess:
	mov r10, rcx
	mov eax, 26h
	syscall
	ret

NtCreateThreadEx:
	mov r10, rcx
	mov eax, 0xbd
	syscall
	ret

NtWriteVirtualMemory:
	mov r10, rcx
	mov eax, 3Ah
	syscall
	ret

NtAllocateVirtualMemory:
	mov r10, rcx
	mov eax, 18h
	syscall
	ret