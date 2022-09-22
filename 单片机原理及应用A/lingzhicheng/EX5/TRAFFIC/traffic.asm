//��ͨ��ģ�顢��̬�����ģ�飬���ö�ʱ����ʮ���������
//�� 8 �����������ӵ�Ƭ�� P0 �� JP10 ����̬����ܵ� J12���� 8 �����������ӵ�Ƭ�� P1 �� JP8 �� ��ͨ��ģ��� JP1
//��Ƭ���� P22��P23��P24 �ֱ�ӵ� 74HC138 ģ���A��B��C��JP165 ����ñһ��Ҫ�ε�����������һ�����ϣ����ⶪ����
//�ϱ��̵�30s�����30s���Ƶƾ�Ϊ5s�������̵�25s�����35s��
//���е�����ʾ����ʱ��������ʾ����ʱ
	ORG 		0000H
RESET:
	AJMP		MAIN
	ORG 		000BH			//��ʱ���ж�0���
	AJMP 		INTI0
	ORG 		0100H
		
MAIN:
	MOV			SP,#60H			//��ʱ������ʽ1
	MOV		 	TMOD,#01H
	MOV			DPTR,#TABLE
//12MHz����������1��s����Ҫ10000����������ֵ=65536-10000=55536=D8F0H
	MOV			TH0,#0D8H
	MOV			TL0,#0F0H
	SETB		ET0				//����T0�жϺ����ж�
	SETB		EA
	SETB 		TR0 			//����T0
	MOV 		R0,#01			//��������ֵΪ01
	MOV			30H,#00H		//��ʱ����ʱһ�ٴΣ��ﵽ64h��һ��
	MOV			31H,#30			//�ϱ���������ʱ�䣬30��5��30	
	MOV			32H,#35			//������������ʱ�䣬35��5��25
	MOV 		P1,#11001101B	//110������'011�ϱ���'01�����ϱ���
	CLR 		P3.0	  		//10���ж�����
	SETB 		P3.1
	LCALL		CALCU
	LJMP		DISPLAY

CALCU:
/***********�ϱ����򵹼�ʱ����********************/
 	MOV 		R1,#10			//����Ϊ10
	MOV 		A,31H			//����ʱ���ַŵ�A
	MOV 		B,R1			//����10�ŵ�B
	DIV 		AB				//AΪ�̣�BΪ����
	MOV 		R4,A			//R4�����
	MOV 		R5,B			//R5�������
/***********�������򵹼�ʱ����********************/
	MOV 		R1,#10			//����Ϊ10
	MOV 		A,32H			//����ʱ���ַŵ�A
	MOV 		B,R1			//����10�ŵ�B
	DIV 		AB				//AΪ�̣�BΪ����
	MOV 		R6,A			//R6�����
	MOV 		R7,B			//R7�������
	RET
	
DISPLAY:
/***********�ϱ����򵹼�ʱ��ʾ********************/
	CLR			P2.2
	CLR			P2.3
	CLR			P2.4
	MOV 		A,R4			//LED0�����
	MOVC 		A,@A+DPTR
	MOV 		P0,A
	LCALL 		D04MS
	
	SETB		P2.2
	MOV 		A,R5			//LED1�������
	MOVC 		A,@A+DPTR
	MOV 		P0,A
/***********�������򵹼�ʱ��ʾ********************/
	CLR			P2.2
	CLR			P2.3
	SETB		P2.4
	LCALL 		D04MS 
	MOV 		A,R6			//LED4�����
	MOVC 		A,@A+DPTR
	MOV 		P0,A
	LCALL 		D04MS
	
	SETB		P2.2
	MOV 		A,R7			//LED5�������
	MOVC 		A,@A+DPTR
	MOV 		P0,A
/*********************************************/
	JNB			TF0,DISPLAY		//wait for TF0

INTI0:
	PUSH		PSW				//����״̬�ּĴ���
	PUSH		ACC
	CLR			EA				//�ر����ж�
	MOV			TH0,#0D8H		//��ʱ10ms
	MOV			TL0,#0F0H
	INC			30H
	MOV			A,30H
	CJNE		A,#100,OUT
	MOV			30H,#00H		//��ʱ����ʱһ�ٴΣ��ﵽ64h��һ��
	INC 		R0				//������+1
	DEC			31H
	DEC			32H
	

/***********����״̬����ת��********************/
JMP5SN:
	CJNE 		R0,#31,JMP30EW
	MOV 		P1,#11010110B	//110������'101�ϱ���'10�����ϱ���
	CLR 		P3.0	  		//10���ж�����
	SETB 		P3.1
	MOV			31H,#5	
	LCALL		CALCU
	SJMP 		OUT
JMP30EW:
	CJNE 		R0,#36,JMP5EW
	MOV 		P1,#01111010B	//011������'110�ϱ���'10�����ϱ���
	SETB 		P3.0	  		//01���ж�����
	CLR 		P3.1
	MOV			31H,#30
	MOV			32H,#25
	LCALL		CALCU
	SJMP 		OUT
JMP5EW:
	CJNE 		R0,#66,JMP30SN
	MOV 		P1,#10111010B	//101������'110�ϱ���'10�����ϱ���
	SETB 		P3.0	  		//01���ж�����
	CLR 		P3.1
	MOV			32H,#5
	LCALL		CALCU
	SJMP 		OUT
JMP30SN:
	CJNE 		R0,#71,OUT
	MOV 		R0,#1
	MOV 		P1,#11001101B	//110������'011�ϱ���'01�����ϱ���
	CLR 		P3.0	  		//10���ж�����
	SETB 		P3.1
	MOV			31H,#30
	MOV			32H,#35			
	LCALL		CALCU
	SJMP 		OUT

OUT:
	SETB		EA				//�����ж�
	POP			ACC
	POP			PSW				//����״̬�ּĴ���
	RETI

D04MS:							//��ʱ0.4ms
	MOV 		R3,#2
D1:			 
	MOV 		R2,#10
D2:
	DJNZ 		R2,D2
	DJNZ 		R3,D1
	RET

TABLE:	DB		3FH,06H,5BH,4FH,66H,6DH,7DH,07H	//������0~9
		DB		7FH,6FH
		DB		00H
/*TABLE:	DB		3FH,06H,5BH,4FH,66H,6DH,7DH,07H	//������0~F
			DB		7FH,6FH,77H,7CH,39H,5EH,79H,71H
			DB		00H*/
			
/*TABLE:	DB 		0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H//������0~9
			DB		80H,90H
			DB 		0FFH*/	   

/*TABLE:	DB 		0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H//������0~F
			DB		80H,90H,88H,83H,0C6H,0A1H,86H,8EH
			DB 		0FFH*/
			
		END