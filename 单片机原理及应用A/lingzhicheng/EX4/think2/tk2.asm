//P3.3��k4��P1��LED��ABCDEF��
		ORG	 	0000H
		AJMP	START
		ORG		0013H;�ⲿ�ж�1�����λ0013h
		AJMP	INTT1
		ORG		0100H
	
START:	MOV		SP,#60H
		SETB	EX1;���ж�
		SETB	IT1
		SETB	EA
		MOV		IP,#04H;�����ж�1Ϊ�����ȼ�
		MOV		P3,#0FFH
MAIN:	MOV		R0,#03H
		MOV		R2,#08H
		ACALL	LOOP
		LJMP	MAIN

LOOP:	MOV		A,R0
		MOV		P1,A
		RL		A
		MOV		R0,A
		LCALL	D1S
		DJNZ	R2,LOOP
		RET
		
INTT1:	MOV		A,P3
		CPL		A
		JZ		RETURN
		LCALL	D10ms	;ȥ����
		MOV		A,P3
		CPL		A
		JZ		RETURN
		JB		ACC.3,Pkey0
		RETI
		
Pkey0:	
		MOV		R1,#01H
		MOV		R3,#08H
		ACALL	Pkey1
		LJMP	RETURN
		
Pkey1:	MOV		A,R1
		MOV		P1,A
		RL		A
		MOV		R1,A
		LCALL	D1S
		DJNZ	R3,Pkey1
		RET		
		
RETURN:	RETI

D10ms:	MOV		R7,#25
D4:		MOV		R6,#200
		DJNZ	R6,$
		DJNZ	R7,D4
		RET

D1S:	MOV		R5,#20
D5:		MOV		R6,#100
D6:		MOV		R7,#248
D7:		DJNZ	R7,D7
		DJNZ	R6,D6
		DJNZ	R5,D5
		RET	
		
		END