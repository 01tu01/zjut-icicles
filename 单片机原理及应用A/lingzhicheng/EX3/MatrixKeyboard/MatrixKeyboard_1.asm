//P0��λѡ��P1�Ӿ���ʽ���̣�P2����ֵ
		ORG		0000H
		AJMP	RESET
		ORG 	0100H
RESET:	MOV		SP,#60H
		MOV		DPTR,#TABLE
		MOV		R5,#80H;8'b1000 0000
		MOV		R0,#08H
		MOV		B,#00H
MAIN:	MOV		P2,#00H
		LCALL	KEY2
		DJNZ	R0,MAIN
		LJMP	RESET
		
KEY2:	LCALL 	KS;���ü��̼���ӳ���ks
		JNZ		K1;�޼�������AΪ0���м���������ת��K1(��0ת��)
		LCALL	D10ms
		INC		R0;����޼����£�R0ֵ��Ҫ�ָ�
		RET
		
K1:		LCALL	D10ms;ȥ����10ms
		LCALL	KS;�ٴμ��
		JNZ		K2;��Ȼ�м���������תK2������ص�KEY2���¿�ʼ��һ����
		AJMP	KEY2
		
K2:		MOV		R2,#0EFH;1110'1111�ݴ��R2����P1.4Ϊ0
		MOV 	R4,#00H;0�к�����R4�ݴ�
K3:		MOV		P1,R2;����ɨ��ֵ����P1�ڣ�P1.4Ϊ0
L0:		JB		P1.0,L1;��0���ߵ�ƽ��P1.0Ϊ1���ް��£���ת��L1���1��
		MOV		A,#00H;����������0���׼��̺��ͽ�ACC
		AJMP	LK;��ת��LK�����к�+�к�
L1:		JB  	P1.1,L2
		MOV		A,#04H
		AJMP	LK
L2:		JB		P1.2,L3
		MOV		A,#08H
		AJMP	LK
L3:		JB		P1.3,NEXT;��0~3�о��޼���������NEXT��׼�������һ��
		MOV		A,#0CH
		AJMP	LK
		
NEXT:	INC		R4;�кż�1
		MOV		A,R2;��R2ɨ��ֵ����A
		JNB		ACC.7,KEY2;�ж�A�����λ�Ƿ�Ϊ0�������Ѿ�0111��0000����������ɨ���꣬�򷵻�KEY2
		RL		A;�����ǣ���A����һλ��ɨ����һ��
		MOV		R2,A;��һ�е�A������R2
		AJMP	K3;�ص�K3��ʼɨ����һ��
		
LK:		ADD		A,R4;�к�R4���к�ACC���ӵ�A
		ACALL	LEFT
		MOVC	A,@A+DPTR
		MOV		P0,B
		MOV		P2,A
		ACALL	K4
		LCALL	DELAY
		DJNZ	R0,KEY2
		LJMP    RESET
		
K4:		LCALL	KS;����Ƿ���Ѿ��ɿ�
		JNZ		K4
		LCALL	D10ms
		JNZ		K4
		RET

		
KS:		MOV		P1,#0FH
		MOV		A,P1
		XRL		A,#0FH
		RET
		
LEFT:	MOV		B,A
		MOV		A,R5
		RL		A
		MOV		R5,A
		MOV		A,B
		MOV		B,R5
		RET
		
TABLE:	DB		3FH,06H,5BH,4FH,66H,6DH,7DH,07H
		DB		7FH,6FH,77H,7CH,39H,5EH,79H,71H
		DB		00H

D10ms:	MOV		R7,#25
D1:		MOV		R6,#200
		DJNZ	R6,$
		DJNZ	R7,D1
		RET

DELAY:	MOV		R7,#10
D2:		MOV		R6,#20
D3:		DJNZ	R6,D3
		DJNZ	R7,D2
		RET
		
		END