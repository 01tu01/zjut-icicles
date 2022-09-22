		ORG 0000h
		LJMP MAIN
		ORG 0100H
MAIN:  	MOV	SP,#60H	
		MOV TMOD,#20H
		MOV TH1,#0F4H
		MOV TL1,#0F4H
	   	MOV PCON,#80H
		SETB TR1
		MOV SCON,#50H
		MOV R0,#30H
		MOV R7,#00H
		MOV R6,#00H

REC:	JNB RI,REC					//���ܷ�������
		CLR RI
		MOV A,SBUF
		CJNE A,#06H,SEND
		LJMP SEND2
	
SEND:	MOV A,#15H				 //���;ܾ���Ӧ
		MOV SBUF,A
WAIT1: 	JNB TI,WAIT1
		CLR TI
		LJMP REC	   

SEND2:	MOV A,#00H			 //���ͽ��ܻ�Ӧ
		MOV SBUF,A
WAIT2: 	JNB TI,WAIT2
		CLR TI

REC1:	JNB RI,REC1		   //�����ַ�����
		CLR RI
		MOV A,SBUF
		MOV R7,A
		MOV R6,A
REC2: 	JNB RI,REC2		   //��������
		CLR RI
		MOV A,SBUF
		MOV @R0,A
		ADD A,R6
		MOV R6,A
		INC R0
		DJNZ R7,REC2

REC3:  	JNB RI,REC3			  //����У��λ
		CLR RI
		MOV A,SBUF
		MOV 40H,R6
		CJNE A,40H,WRO		  //У��λ�ж���ȷ�����

TR:		MOV A,#0FH
	   	MOV SBUF,A
WAIT3:	JNB TI,WAIT3
		CLR TI
		SJMP $

WRO:	MOV A,#0F0H
		MOV SBUF,A
WAIT4:	JNB RI,WAIT4
		CLR RI
		SJMP $

END




			
