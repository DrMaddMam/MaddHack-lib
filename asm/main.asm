BITS 64
section .data
	msg1 db "Hello, World!", 10, 0
section .text
global _start
global strlen
global autoprint
strlen:
	xor rax,rax
.l1:
	cmp BYTE [rdi+rax],0
	jz .done
	inc rax
	jmp .l1
.done:
	ret
autoprint:
	mov rsi,rdi
	call strlen
	mov rdx,rax
	mov rax,1
	mov rdi,1
	syscall
    ret

_start:
	mov rdi,msg1
	call autoprint
	mov rax,60
	xor rdi,rdi
	syscall