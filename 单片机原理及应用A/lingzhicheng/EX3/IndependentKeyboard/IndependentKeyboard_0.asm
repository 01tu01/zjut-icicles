		ORG		0000H
		AJMP	START
		ORG 	0100H
			
START:	MOV		SP,#60H
MAIN:	LCALL	KEY1;��ת��KEY1
		LJMP	MAIN;�ظ�ѭ��
KEY1:	MOV		P1,#0FFH;P1��ȫд��1
		MOV		B,A;
		MOV		P2,B;
		MOV		A,P1;����˸�������״̬���м�������Ϊ0
		CPL		A;ȫ��ȡ�����м�������Ϊ1
		JZ		KEY1;����ۼ���AȫΪ0�����޼����£���ת��KEY1���¿�ʼ
		LCALL	D10ms;ȥ����
		MOV		A,P1;����˸�������״̬���м�������Ϊ0
		CPL		A;ȫ��ȡ�����м�������Ϊ1
		JZ		KEY1;����ۼ���AȫΪ0�����޼����£���ת��KEY1���¿�ʼ
		JB		ACC.0,PK0
		JB		ACC.1,PK1
		JB		ACC.2,PK2
		JB		ACC.3,PK3
		JB		ACC.4,PK4
		JB		ACC.5,PK5
		JB		ACC.6,PK6
		JB		ACC.7,PK7
		RET

PK0:	LCALL	PKEY0
		LJMP	KEY1
PK1:	LCALL	PKEY1
		LJMP	KEY1
PK2:	LCALL	PKEY2
		LJMP	KEY1
PK3:	LCALL	PKEY3
		LJMP	KEY1		
PK4:	LCALL	PKEY4
		LJMP	KEY1		
PK5:	LCALL	PKEY5
		LJMP	KEY1
PK6:	LCALL	PKEY6
		LJMP	KEY1
PK7:	LCALL	PKEY7
		LJMP	KEY1	
		
PKEY0:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.0,PKEY0
		LCALL	D10ms
		JNB		P1.0,PKEY0
		RET
PKEY1:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.1,PKEY1
		LCALL	D10ms
		JNB		P1.1,PKEY1
		RET
PKEY2:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.2,PKEY2
		LCALL	D10ms
		JNB		P1.2,PKEY2
		RET
PKEY3:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.3,PKEY3
		LCALL	D10ms
		JNB		P1.3,PKEY3
		RET
PKEY4:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.4,PKEY4
		LCALL	D10ms
		JNB		P1.4,PKEY4
		RET
PKEY5:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.5,PKEY5
		LCALL	D10ms
		JNB		P1.5,PKEY5
		RET
PKEY6:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.6,PKEY6
		LCALL	D10ms
		JNB		P1.6,PKEY6
		RET
PKEY7:	MOV		B,A;
		MOV		P2,B;
		JNB		P1.7,PKEY7
		LCALL	D10ms
		JNB		P1.7,PKEY7
		RET

D10ms:	MOV		R7,#25
D1:		MOV		R6,#200
		DJNZ	R6,$
		DJNZ	R7,D1
		RET
	
		END
			