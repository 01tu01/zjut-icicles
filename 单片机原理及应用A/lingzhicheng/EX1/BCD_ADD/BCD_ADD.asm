	ORG		0000H
	LJMP	MAIN
	ORG	  	0100H
MAIN:
	MOV		SP,#60H
	CLR		C
	MOV		R2,#50H
	MOV		51H,#00H;�͵��ֽ�������
	MOV		R0,#30H
	MOV 	R1,#40H
	LCALL	BCD_ADD_BYTES
	SJMP	$
	
BCD_ADD_BYTES:
	MOV		A,@R0;ȡ������
	ADDC	A,@R1;���
	DA		A;ʮ���Ƶ���
	MOV	    @R0,A;����
	INC		51H;�ֽ���1
	INC		R0;��ַ��1
	INC 	R1
	DJNZ    50H	,BCD_ADD_BYTES;�����ֽ�δ�����������������ִ��
	JC		NEXT;�͵�����ֽ��н�λ��ת��next
	RET
	
NEXT:
	INC 	51H
	MOV 	@R0,#01H
	RET
	
	END