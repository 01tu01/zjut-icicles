ORG 0000H

LJMP MAIN
ORG 0050H
	MAIN:
		MOV SP,#60H
		MOV DPTR,#0200H
		MOV R0,#40H
		MOV R2,#00H
		MOV R3,#00H
	F1:
		MOV A,R2
		MOVC A,@A+DPTR
		MOV @R0,A
		SUBB A,R3
		JC F2
		
		MOV A,R2
		MOVC A,@A+DPTR
		MOV R3,A;���û�н�λ���������ݴ�R3
	F2:	
		CLR C;ѭ��ʮ���Σ����ҳ�����������ȴ���40H--4FH
		INC R0
		INC R2
		CJNE R2,#10H,F1
		
		MOV R1,#40H
	PAIXU:
		MOV R0,#40H
		MOV A,@R0
		MOV R3,A
	F3:	
		INC R0
		MOV A,@R0
		SUBB A,R3
		JNC F4;���޽�λ�����λ�ȵ�λ�����轻��
		MOV A,@R0;���н�λ����������
		MOV R2,A
		MOV A,R3
		MOV @R0,A
		DEC R0
		MOV A,R2
		MOV @R0,A
		INC R0
		CLR C
		CJNE R0,#4FH,F3
	F4:
		MOV A,@R0
		MOV R3,A
		CLR C
		CJNE R0,#4FH,F3
		
		INC R1
		CJNE R1,#4FH,PAIXU
		
		SJMP $
		END	
		
		
		