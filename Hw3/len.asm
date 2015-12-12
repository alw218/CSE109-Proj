SYS_EXIT equ 1
	SYS_READ equ 3
	SYS_WRITE equ 4
	STDIN equ 0
	STDOUT equ 1


	segment .bss
	char resb 1

	section .text
	global main
main:
	mov edx,msg3
	call strlen
	mov edx,1 		; Set the length
	add ecx,'0'		; Turn the count in ecx into an ASCII DIGIT
	mov [char], ecx		; Copy the char into memory
	mov ecx, char
	mov ebx,STDOUT
	mov eax,SYS_WRITE
	int 0x80
	mov eax,SYS_EXIT
	int 0x80

strlen:
	mov ecx,0
lab2:
	cmp [edx],byte 0
	jz lab1
	inc ecx
	inc edx
	jmp lab2
lab1:
	ret


	segment .data
	 msg2 db 'AB', 0x0
	 msg3 db '123456789', 0x0