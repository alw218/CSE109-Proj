	;; Amber Wallace
	;; alw218
	;; Hw3
	SYS_EXIT equ 1
	SYS_READ equ 3
	SYS_WRITE equ 4
	STDIN equ 0
	STDOUT equ 1

	;;  Create a text section that contains a program that scans the string until it reaches the 0 byte and writes each
	;;  token to standard output, one token per line, skipping blanks between tokens.
	section .text
	global main
main:
	mov ecx,str
	mov edx,1
	mov eax,4
	mov ebx,1
	call lab1
	mov eax,SYS_EXIT
	int 0x80

lab1:
	cmp [ecx], byte 0
	jz lab2
	mov al, [ecx]
	cmp al, 32
	jz space
	mov ebx,1 		;file descriptor (stdout)
	mov eax,4 		;system call number (sys_write)
	int 0x80 		;call kernel
	inc ecx
	jmp lab1

lab2:
	ret

space:
	inc ecx
	mov al,[ecx]
	cmp al, 32
	jz space
	;; in the event there are no more spaces print new line
	push cx
	mov edx,len1 		;message length
	 mov ecx,msg1 		;message to write
	 mov ebx,1 		;file descriptor (stdout)
	 mov eax,4 		;system call number (sys_write)
	 int 0x80 		;call kernel
	pop cx
	dec edx
	jmp lab1

	section .data
count:	db 0
spacechar:	db ' ', 0x0
str:	dw '  This  is a test ', 0x0
	len equ $ - str
msg1:	dw '', 0x0a
	len1 equ $ - msg1