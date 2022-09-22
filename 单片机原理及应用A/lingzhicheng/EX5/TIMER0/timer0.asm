//P2.0��LEDģ��J12��A	
	ORG		0000H
RESET:
	LJMP	MAIN
	ORG		000BH;��ʱ���ж�0���
	LJMP	T0_INT
	ORG		0100H
	
MAIN:
	MOV		SP,#60H
	MOV		TMOD,#01H;��ʱ������ʽ1
	MOV		30H,#00H;��ʱ����ʱһ�ٴΣ��ﵽ64h��һ��
	;12MHz����������1��s����Ҫ10000����������ֵ=65536-10000=55536=D8F0H
	MOV		TH0,#0D8H
	MOV		TL0,#0F0H
	SETB	P2.0
	SETB	ET0;����T0�жϺ����ж�
	SETB	EA
	SETB	TR0;����T0
	JNB		TF0,$;wait for TF0

T0_INT:
	PUSH	PSW;����״̬�ּĴ���
	PUSH	ACC
	CLR		EA;�ر����ж�
	MOV		TH0,#0D8H
	MOV		TL0,#0F0H
	INC		30H
	MOV		A,30H
	CJNE	A,#100,CONTINUE_T0
	MOV		30H,#00H;��ʱ����ʱһ�ٴΣ��ﵽ64h��һ��
	CPL		P2.0

CONTINUE_T0:
	SETB	EA;�����ж�
	POP		ACC
	POP		PSW;����״̬�ּĴ���
	RETI
	
	END