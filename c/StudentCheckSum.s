	.file	"StudentCheckSum.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Enter your student number: "
.LC1:
	.string	"%s"
.LC2:
	.string	"Input must be 8 numbers"
.LC3:
	.string	"Input must be numbers only"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"The sum of your student number is: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	sub	rsp, 112
	.cfi_def_cfa_offset 128
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 104[rsp], rax
	xor	eax, eax
	lea	rdi, .LC0[rip] ; Gebruik deze string -
	call	printf@PLT ; Vraag de studentnummer
	mov	rbx, rsp
	mov	rsi, rbx
	lea	rdi, .LC1[rip] ; Gebruik deze string -
	mov	eax, 0
	call	__isoc99_scanf@PLT ; Haal studentnummer op
	mov	rdi, rbx
	call	strlen@PLT ; Bereken lengte van studentnummer
	cmp	rax, 8 ; Check of de input 8 karakters lang is
	jne	.L9 ; Ga naar .L9 als de input niet 8 karakters lang is
	mov	edx, 0
	mov	esi, 0
.L2:
	cmp	edx, 7 ; (Tweede paramater van for loop) Kijk of edx gelijk is aan 7
	jg	.L10 ; Als edx groter is dan 7, ga uit de for loop
	movsx	rax, edx
	movzx	eax, BYTE PTR [rsp+rax] ; Haal de karakter op
	lea	ecx, -48[rax] ; Verander de karakter naar een getalz
	cmp	cl, 9 ; Als de waarde van de char groter is dan 9 -
	ja	.L11 ; voer dan deze code uit
	movsx	eax, al
	lea	esi, -48[rax+rsi] ; Bereken de som van de karakters
	add	edx, 1 ; (Derde paramater van for loop) Tel een iteratie op bij edx
	jmp	.L2 ; Loop terug naar .L2
.L9:
	lea	rdi, .LC2[rip] ; Gebruik deze string -
	call	puts@PLT ; Print error message
	mov	eax, 1 ; Return 1
	jmp	.L1 ; Ga naar einde programma
.L11:
	lea	rdi, .LC3[rip] ; Gebruik deze string -
	call	puts@PLT ; Print error message
	mov	eax, 1 ; Return 1
	jmp	.L1 ; Ga naar einde programma
.L10:
	lea	rdi, .LC4[rip] ; Gebruik deze string -
	mov	eax, 0 ; Return 0
	call	printf@PLT ; Print resultaat
	mov	eax, 0 ; Return 0
.L1:
	mov	rdx, QWORD PTR 104[rsp]
	sub	rdx, QWORD PTR fs:40
	jne	.L12
	add	rsp, 112
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
