//P1��LED��ABCDEF��P3.2��K1��P3.3��K4��P0�Ӿ�̬�����ABCDEF		
		ORG	 	0000H
		AJMP	START
		
		ORG		0003H
		AJMP	INTT0
		
		ORG		0013H
		AJMP	INTT1
		
		ORG		0100H
START:	MOV		SP,#60H
		MOV		PSW,#00H
		SETB	EX0
		SETB	IT0
		SETB	EX1
		SETB	IT1
		SETB	EA
		MOV		IP,#01H
		MOV		P3,#0FFH
MAIN:	MOV		DPTR,#TABLE
		MOV		R0,#03H
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
		
INTT0:	PUSH	PSW
		PUSH	ACC
		MOV		PSW,#08H
		MOV		A,P3
		CPL		A
		JZ		RETURN
		LCALL	D10ms			//ȥ����
		MOV		A,P3
		CPL		A
		JZ		RETURN
		JB		ACC.2,Pkey0
		LJMP	RETURN
		
INTT1:	PUSH	PSW
		PUSH	ACC
		MOV		PSW,#10H
		MOV		A,P3
		CPL		A
		JZ		RETURN
		LCALL	D10ms		//ȥ����
		MOV		A,P3
		CPL		A
		JZ		RETURN
		JB		ACC.3,Pkey2
		LJMP	RETURN
/***********************/	
Pkey0:	MOV		A,#00H
		MOVC	A,@A+DPTR
		CJNE	A,#0FFH,Pkey1
		LJMP	RETURN	
Pkey1:	MOV		P0,A
		LCALL	D1S
		INC		DPTR
		LJMP	Pkey0	
/***********************/
Pkey2:	MOV		R1,#01H
		MOV		R3,#08H
		ACALL	Pkey3
		LJMP	RETURN
Pkey3:	MOV		A,R1
		MOV		P1,A
		RL		A
		MOV		R1,A
		LCALL	D1S
		DJNZ	R3,Pkey3
		RET	
/***********************/
RETURN:	
		POP		ACC
		POP		PSW
		RETI
		
TABLE:	DB 		0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H
		DB		80H,90H,88H,83H,0C6H,0A1H,86H,8EH
		DB		0FFH

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