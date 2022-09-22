//P0�öŰ��߽ӵ���̬�����JP3
	ORG		0000H
RESET:
	LJMP	MAIN
	ORG		001BH;��ʱ���ж�1���
	LJMP	T1_INT
	ORG		0100H
	
MAIN:
	MOV		SP,#60H
	MOV		DPTR,#TABLE
	MOV		TMOD,#10H;��ʱ������ʽ1
	MOV		P0,#0FFH
	MOV		R0,#00H
	MOV		30H,#00H;��ʱ����ʱһ�ٴΣ��ﵽ64h��һ��
	;12MHz����������1��s����Ҫ10000����������ֵ=65536-10000=55536=D8F0H
	MOV		TH1,#0D8H
	MOV		TL1,#0F0H
	SETB	ET1;����T1�жϺ����ж�
	SETB	EA
	SETB	TR1;����T1
	JNB		TF1,$;wait for TF1

T1_INT:
	PUSH	PSW;����״̬�ּĴ���
	PUSH	ACC
	CLR		EA;�ر����ж�
	MOV		TH1,#0D8H
	MOV		TL1,#0F0H
	INC		30H
	MOV		A,30H	
	CJNE	A,#100,CONTINUE_T0
	MOV		A,R0
	MOVC	A,@A+DPTR
	CJNE	A,#0FFH,SHOW
	MOV		R0,#00H

SHOW:
	MOV		P0,A
	INC		R0
	SETB	EA;�����ж�
	POP		ACC
	POP		PSW;����״̬�ּĴ���
	RETI

CONTINUE_T0:
	SETB	EA;�����ж�
	POP		ACC
	POP		PSW;����״̬�ּĴ���
	RETI
	
TABLE:	
	DB 		0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H
	DB		80H,90H,88H,83H,0C6H,0A1H,86H,8EH
	DB		0FFH

	END
	