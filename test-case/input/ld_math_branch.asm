	NOT R1, R0
	NOT R2, R0
	AND r3, r1, r2
	AND r4, r1, xF 
	ADD r5, r4, r5
	ADD r5, r5, xF
	NOT r6, r0
LOOP:
	ADD r6, r6, x1
	BRnz LOOP
	JSR FUNC
	ADD r1, r0, x1
	ADD r2, r0, x2
	ADD r3, r0, x3
	ST r3, x-3e
	STR r2, r0, x4
	STI r1, x-3c
	LD r1, x-41
	LDI r3, x-42
	LDR r4, r0, x0
	LEA r4, x4
	ST r4, x2b
	TRAP x70
FUNC:
	RET
