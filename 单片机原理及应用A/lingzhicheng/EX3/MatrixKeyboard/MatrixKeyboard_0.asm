		ORG		0000H
		AJMP	START
		ORG 	0100H
START:	MOV		SP,#60H
		MOV		DPTR,#TABLE
		LCALL	KEY2
		LJMP	START
		
KEY2:	LCALL 	KS;���ü��̼���ӳ���ks
		JNZ		K1;�޼�������AΪ0���м���������ת��K1
		LCALL	D10ms
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
		
LK:		ADD		A,R4;�к�R4���к�ACC
		MOVC	A,@A+DPTR
		MOV		P2,A
		ACALL	K4
		
K4:		LCALL	KS;����Ƿ���Ѿ��ɿ�
		JNZ		K4
		LCALL	D10ms
		JNZ		K4
		LCALL	KEY2
		
KS:		MOV		P1,#0FH
		MOV		A,P1
		XRL		A,#0FH
		RET
		
D10ms:	MOV		R7,#25
D1:		MOV		R6,#200
		DJNZ	R6,$
		DJNZ	R7,D1
		RET
		
TABLE:	DB 		0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H
		DB		80H,90H,88H,83H,0C6H,0A1H,86H,8EH
		DB		0FFH
		END