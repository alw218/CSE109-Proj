section .data
	section .bss
	input resb 20		;will store input
	count resb 4		;will hold our current position in the string

	section .text
global _start
_start:

	mov eax, 3
	mov ebx, 0		;take user input
	mov ecx, input		;should be in form:  Firstname Lastname
	mov edx, 20		;eg Kyle Butler
	int 0x80

	mov ecx, 0
	mov edx, 32		;ecx holds counter, edx hold ascii for space
loopS:
	;; mov [count], ecx		;store whatever is in ecx in our count variable
	cmp ecx, 20		;if ecx is 20, we are done
	je endloopS
	mov ebx, dword[input+ecx] ;otherwise, convert current char in the string to ascii number
	cmp ebx, edx		  ;compare that ascii to ascii for space, held in edx
	je equal		  ;if they are equal, replace space with a period
	inc ecx			  ;increment ecx and restart the loop
	jmp loopS		  ;to check the next character in the string
equal:
	mov [input+ecx], dword 46
	inc ecx			;replace space with period and restart loop to look for
	jmp loopS		;next space character

endloopS:
	mov eax, 4
	mov ebx, 1
	mov ecx, input		;output the new string to the screen
	mov edx, 20
	int 0x80

	mov eax, 1
	mov ebx, 0		;standard exit procedure
	int 0x80