		ORG 	0000H
		AJMP	START
		ORG		0100H
START:	
		MOV		SP,#60H
		
MAIN:	MOV   	R7,#08H; ��ʾ��λ
		//MOV		R6,#80H;1000��0000B����һ�����ƺ�����λ��ʼ��ʾ
		MOV		R6,#0
		MOV		R0,#30H;��ʾ������30H
LOOP:
		//MOV 	A,R6;��ȡ��ʾλ
		//RL		A;��ʾλ����
		//MOV		R6,A;�Ż�R6�ݴ���ʾλ
		//MOV		P2,A;��P2�����ʾλ
		MOV		P2,R6
		INC		R6
		MOV		A,@R0;��ȡ��ʾֵ
		MOV		P0,A;�������P0��
		LCALL	DELAY;������ʱ�ӳ���
		INC		R0;��ʾ������+1
		DJNZ	R7,LOOP;�ж��Ƿ���ʾ���λ��δ�������loop
		AJMP	MAIN
		
DELAY:	MOV		R2,#10;��ʱ�ӳ���10*1*20*2=0.4ms
D2:		MOV		R3,#1
D1:		MOV		R4,#20
D3:		DJNZ	R4,D3
		DJNZ	R3,D1
		DJNZ	R2,D2
		RET

		END
		