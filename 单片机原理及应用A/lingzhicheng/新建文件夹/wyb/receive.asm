	ORG 0000H
	LJMP MAIN
	ORG 0023H
	LJMP RECE_STR
	ORG 1000H
MAIN:
	MOV SP,#60H		
	MOV TMOD,#20H 	//��ʱ��1��ʽ2
	MOV TH1,#0F4H	//������2400
	MOV TL1,#0F4H
	MOV PCON,#80H	//SMODΪ1,�����ʼӱ�
	SETB TR1
	MOV SCON,#50H
	MOV IE,#90H
	MOV R0,#30H
	MOV R7,#0
	MOV R6,#0
HERE:
	SJMP HERE
/*	MOV 29H,#1
	MOV 30H,#0C0H

LOOP:
	MOV A,29H
	MOV R5,29H
	JZ LOOP
	MOV	R1,#30H
	LCALL KEY1;��ת��KEY1
	LJMP LOOP;�ظ�ѭ��
KEY1:
	MOV	P2,#0FFH;P2��ȫд��1
	MOV	A,P2;����˸�������״̬���м�������Ϊ0
	CPL	A;ȫ��ȡ�����м�������Ϊ1
	JZ KEY1;����ۼ���AȫΪ0�����޼����£���ת��KEY1���¿�ʼ
	LCALL D10ms;ȥ����
	MOV	A,P2;����˸�������״̬���м�������Ϊ0
	CPL	A;ȫ��ȡ�����м�������Ϊ1
	JZ KEY1;����ۼ���AȫΪ0�����޼����£���ת��KEY1���¿�ʼ
	JB ACC.7,PK0
	RET
PK0:
	LCALL PKEY0
	LJMP KEY1
		
PKEY0:
	MOV	P0,@R1
	INC R1
	JNB	P2.0,PKEY0
	LCALL D10ms
	JNB	P2.0,PKEY0
	DJNZ R5,K_RETURN
	MOV R1,#30H
	MOV R5,29H
K_RETURN:
	RET


D10ms:
	MOV	R3,#25
D1:
	MOV	R4,#200
	DJNZ R4,$
	DJNZ R3,D1
	RET	  */
			

RECE_STR:
	PUSH ACC
	PUSH PSW
	MOV P1,#1		//���Ե�
	CLR RI
	MOV A,SBUF		 //���պ����ź�
	CJNE A,#06H,SEND15
SEND00:
	MOV A,#00H		 //������
	MOV SBUF,A
	LJMP HERE_RE
SEND15:
	MOV P1,#2		//���Ե�
	MOV A,#15H		 //��������
	MOV SBUF,A
	LJMP RETURN
HERE_RE:	
	JNB TI,HERE_RE	 
	CLR TI		 
	MOV P1,#4		//���Ե�
RECE_LEN:
	JNB RI,RECE_LEN		//�������ݳ���
	CLR RI		
	MOV A,SBUF			//��ѯ���ճ���
	MOV R7,A
	MOV 29H,R7
	INC R6
	MOV P1,#8		//���Ե�

RECE_DATA:
	JNB RI,RECE_DATA		//��������
	CLR RI		
	MOV A,SBUF			//��ѯ��������
	MOV @R0,A
	INC R0
	INC R6
	DJNZ R7,RECE_DATA
	MOV P1,#16		//���Ե�

RECE_YN:
	JNB RI,RECE_YN		//����У��λ
	CLR RI		
	MOV A,SBUF			//��ѯ����У��λ
	SUBB A,R6
	JNZ SENDF0
SEND0F:
	MOV A,#0FH		 //������ȷ
	MOV SBUF,A
	LJMP HERE_END
SENDF0:
	MOV P1,#32		//���Ե�
	MOV A,#0F0H		 //���Ͳ���ȷ
	MOV SBUF,A
	LJMP RETURN
HERE_END:
	JNB TI,HERE_END	 
	CLR TI
	MOV P1,#64		//���Ե�
	LJMP RETURN		 

RETURN:
	POP PSW
	POP ACC
	RETI

END 