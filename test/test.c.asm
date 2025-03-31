		.file "/mnt/Home/Ged/portable-project.ru/yuko-va/entropy/riscv64toys/riscv64toys/test/test.c"
		.option pic

		.global pubVar
		.bss
		.align	4
		.type	pubVar, @object
		.size	pubVar, 4
pubVar:
		.zero	4



		.bss
		.align	4
		.local	privVar
		.comm	privVar, 4, 4
		.align	4



		.text
		.align	1
		.global	test
		.type	test, @function
test:
		addi sp, sp, -16
		sd ra, 8(sp)
		sd s0, 0(sp)
		addi s0, sp, 16
		nop
test_block_0:
.line 24
		li t0, 3		# CFG_EXPR_LITERAL_INT
		mv a2, t0
		li t0, 2		# CFG_EXPR_LITERAL_INT
		mv a1, t0
		li t0, 1		# CFG_EXPR_LITERAL_INT
		mv a0, t0
		call write		# write
		mv t0, a0
L3:
		nop
		ld ra, 8(sp)
		ld s0, 0(sp)
		addi sp, sp, 16
		jr ra
		.size	test, . - test


		.text
		.align	1
		.global	main
		.type	main, @function
main:
		addi sp, sp, -16
		sd ra, 8(sp)
		sd s0, 0(sp)
		addi s0, sp, 16
		nop
		addi sp, sp, -32
		nop
main_block_0:
.line 34
		li t0, 123		# CFG_EXPR_LITERAL_INT
		la t1, pubVar
		sw t0, 0(t1)		# pubVar
.line 35
		li t0, 456		# CFG_EXPR_LITERAL_INT
		la t1, privVar
		sw t0, 0(t1)		# privVar
.line 37
		li t0, 0		# CFG_EXPR_LITERAL_INT
		sw t0, -24(s0)		# stdinfd
.line 38
		li t0, 1		# CFG_EXPR_LITERAL_INT
		sw t0, -32(s0)		# stdoutfd
.line 39
		li t0, 2		# CFG_EXPR_LITERAL_INT
		sw t0, -40(s0)		# stderrfd
.line 41
		la t0, L9		# "Hello!\n"
		sd t0, -48(s0)		# str
.line 43
		li t0, 7		# CFG_EXPR_LITERAL_INT
		mv a2, t0
		ld t0, -48(s0)		# str
		mv a1, t0
		lw t0, -32(s0)		# stdoutfd
		mv a0, t0
		call write		# write
		mv t0, a0
.line 45
		li t0, 3		# CFG_EXPR_LITERAL_INT
		li t1, 5		# CFG_EXPR_LITERAL_INT
		add t0, t0, t1		# CFG_EXPR_ADD
		sw t1, -56(s0)		# x
.line 49
		lw t0, -56(s0)		# x
		li t1, 2		# CFG_EXPR_LITERAL_INT
		mul t0, t0, t1		# CFG_EXPR_MUL
		mv a0, t1
		j L7		# return
L7:
		nop
		addi sp, sp, 32
		nop
		ld ra, 8(sp)
		ld s0, 0(sp)
		addi sp, sp, 16
		jr ra
		.size	main, . - main


		.section	.rodata
		.align	4
L9:
		.byte 72, 101, 108, 108, 111, 33, 92, 110, 34, 0, 0, 0


