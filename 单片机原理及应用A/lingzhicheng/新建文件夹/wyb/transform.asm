	ORG 0000H
	LJMP MAIN
	ORG 1000H
MAIN:
	MOV SP,#60H	
	MOV DPTR,#TAB	
	MOV R0,#30H
	MOV R2,#0
CIN:
	MOV A,R2		 //����TABд��30H-4FH������
	MOVC A,@A+DPTR
	MOV @R0,A
	INC R0
	INC R2
	CJNE R2,#20H,CIN
START:
	MOV TMOD,#20H 	//��ʱ��1��ʽ2
	MOV TH1,#0F4H	//������2400
	MOV TL1,#0F4H
	MOV PCON,#80H	//SMODΪ1,�����ʼӱ�
	SETB TR1
	MOV SCON,#50H
	MOV R0,#30H
	MOV R7,#20H

SEND_RE:
	MOV A,#06H		 //�Ⱥ���
	MOV SBUF,A
HERE_RE:
	JNB TI,HERE_RE	 
	CLR TI
	MOV P1,#1		//���Ե�		 
RECE_RE:
	JNB RI,RECE_RE		 //δ�յ��ظ�������
	CLR RI		
	MOV A,SBUF			//��ѯ����
	CJNE A,#00H,SEND_RE

SEND_LEN:
	MOV A,R7		 //�ȷ����ݳ���
	MOV SBUF,A
HERE_LEN:
	JNB TI,HERE_LEN	 
	CLR TI
	MOV P1,#2		//���Ե�
	INC R6

SEND:				 //��ѯ����
	MOV A,@R0
	MOV SBUF,A
HREE:
	JNB TI,HREE	 
	CLR TI
	INC R0
	INC R6
	DJNZ R7,SEND
	MOV P1,#4		//���Ե�

SEND_YN:
	MOV A,R6		 //���У��λ
	MOV SBUF,A
HERE_YN:
	JNB TI,HERE_YN	 
	CLR TI
	MOV P1,#8		//���Ե�
RECE_END:
	JNB RI,RECE_END		 //δ�յ��ظ�������
	CLR RI		
	MOV A,SBUF			//��ѯ����
	CJNE A,#0FH,START	//���մ������·���

HERE:
	MOV P1,#16		//���Ե�
	SJMP HERE

TAB: 				//������
	DB 0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H
	DB 90H,0C0H,11H,01H,0FFH,50H,12H,13H
	DB 0FEH,1FH,2FH,3FH,4FH,5FH,6FH,7FH
	DB 88H,99H,55H,66H,22H,33H,10H,05H
/*TAB: 				//������
	DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH
	DB 00H	
*/
END 