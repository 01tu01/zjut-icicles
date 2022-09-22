//���ӵ�Ƭ���� JP10 ����̬����ܵ� J12
//�ֱ����ӵ�Ƭ���� P20��P21��P22 �� 74HC138 ģ��� A��B��C�� 
//�ֱ����ӵ�Ƭ���� P34��P35��P36��P37 ��AD/DAģ��� DI��CS��CLK��DO��
//��NE555 ģ�������ñ J11 ����������ñ��װ������һ���ϣ����ⶪ����
ORG 0000H
LJMP MAIN

ORG 0200H
MAIN:
	MOV		SP,#60H
	ACALL 	AD_CHANGE
	
	MOV 	DPTR,#D_table		//��̬��ʾ��λ
	
	MOV		A,#00H				//38��������̬��ʾ��λ
	MOV 	A,R0				//�Ÿ�λ	
	MOVC 	A,@A+DPTR
	MOV 	P2,#03
	MOV 	P0,A
	ACALL 	Delay

	MOV 	A,#00H
	MOV 	A,R1				//��ʮλ	
	MOVC 	A,@A+DPTR
	MOV 	P2,#02
	MOV 	P0,A
	ACALL 	Delay

	MOV 	A,#00H
	MOV 	A,R2				//�Ű�λ	
	MOVC 	A,@A+DPTR
	MOV 	P2,#01
	MOV 	P0,A
	ACALL 	Delay

	MOV 	A,#00H
	MOV 	A,R3				//��ǧλ
	MOVC 	A,@A+DPTR
	MOV		P2,#00
	MOV 	P0,A
	ACALL 	Delay
	
	MOV 	P0,#00H
	LJMP 	MAIN	
	
AD_CHANGE:      			   //��ȡADת���������12λ�����ж��뵥Ƭ���ڣ���SPI����
	INC 	R7				
DELL: 
	DJNZ 	R6,DELL
	CJNE 	R7,#0FFH,RETURN
	MOV 	R7,#00H
	MOV 	R6,#0FFH
	
	MOV 	R0,#0d4H  			//R0������  0X94��0XB4��λ��0XD4������0XA4����
	CLR 	P3.5				//ƬѡCSΪ�͵�ƽ��ѡ��XPT2046
	CLR 	P3.6				//ʱ�ӽ�I/O CLOCKλ�͵�ƽ
	MOV 	R2,#08H	 			//����ѭ������Ĵ���Ϊ8
	MOV 	A,R0				//��һ��ת���������R0����A
LOOP0:
	RLC		A
	MOV		P3.4,C
	CLR 	P3.6
	NOP	
	SETB	P3.6
	NOP
	DJNZ 	R2,LOOP0
	MOV 	A,#00H
	MOV 	R2,#04H
	NOP
	NOP
	NOP
	NOP
LOOP1:
	MOV 	C,P3.7			//������һ�ε�ת������е�1λ
	RRC 	A				//����λλ��ѭ������
	
	SETB	P3.6			//һ��CLKʱ��
	NOP
	CLR 	P3.6
	NOP
	
	DJNZ 	R2,LOOP1		//�Ƿ����8��ת�������������������δ��������
	RRC 	A
	RRC 	A
	RRC 	A
	RRC 	A
	MOV 	R1,A			//R1���4λ����
	MOV 	A,#00H			//A�塰0��
	MOV 	R2,#08H			//����R2ѭ������Ϊ8��Ϊ����8λ����׼��
LOOP2:
	MOV 	C,P3.7			//������һ�ε�ת������е�1λ
	RRC 	A				//����λλ��ѭ������

	CLR 	P3.6			//һ��CLKʱ��
	NOP
	SETB 	P3.6
	NOP
	
	DJNZ 	R2,LOOP2		//�Ƿ����8��ת�������������������δ��������
	
	SWAP 	A			
	MOV 	R0,A 			//R0���8λ
	SETB 	P3.6
	LJMP 	DATA_HEX_DEC
RETURN:
	RET
	
DATA_HEX_DEC:				//����ȡ��12λ2������ת��Ϊʮ���ƴ���R3 R2 R1 R0��ǧλ ��λ ʮλ ��λ��
//	R0-->TL0
//  R1-->TH0
	MOV 	A,R1
	ANL 	A,#0FH
	MOV 	R1,A
    CLR 	A
	
    MOV 	R2,A          	//������
    MOV 	R3,A
    MOV 	R4,A
    MOV 	R5,#16      	//��ת��ʮ��λ��	 
LOOP:
    CLR 	C
    MOV 	A,R0          	//�Ӵ�ת�����ĸ߶��Ƴ�һλ��Cy
    RLC 	A
    MOV 	R0,A
	
    MOV 	A,R1
    RLC 	A
    MOV 	R1,A
	
    MOV 	A,R4           	//�͵�BCD��ĵͶ�
    ADDC 	A,R4           	//����λ��������ӣ��൱������һλ
    DA 		A              	//ʮ���Ƶ��������BCD��
    MOV 	R4,A
	
    MOV 	A,R3
    ADDC 	A,R3
    DA 		A
    MOV 	R3,A
	
    MOV 	A,R2
    ADDC 	A,R2
    MOV 	R2,A
	
    DJNZ 	R5,LOOP
//�Ѿ���TH1 TL1�е����֣�ת����BCD�룬�͵���R2 R3 R4
//*************************************************//
//�ֱ���� R3 R2 R1 R0��ǧλ ��λ ʮλ ��λ
    MOV		A,R4
    MOV 	B,#16
    DIV 	AB
    MOV 	R1,A
    MOV 	R0,B

    MOV 	A,R2
    MOV 	R4,A

    MOV 	A,R3
    MOV 	B,#16
    DIV 	AB
    MOV 	R3,A
    MOV 	R2,B
    RET 
	
Delay:				//��ʱ0.4ms
    MOV 	30H,#10
DEL0: 
	MOV 	31H,#1
DEL1: 
	MOV 	32H,#20
DEL2: 
	DJNZ 	32H,DEL2
    DJNZ 	31H,DEL1
    DJNZ 	30H,DEL0
	  
	RET  
	
D_table:
    DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH	//������0~9
END
