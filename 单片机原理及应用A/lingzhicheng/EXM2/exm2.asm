    ORG     0000H
    LJMP    MAIN
    ORG     0100H
MAIN:
    MOV     DPTR,#0500H
    MOV     R1,#40H       //�ŵ�40H~4FH
    MOV     R3,#16        //ת��16��

LOOP:
    MOV     A,#00H		
    MOVC    A,@A+DPTR
    MOV     @R1,A
    INC     R1
    INC     DPTR
    DJNZ    R3,LOOP     //���16������ת��
    MOV     R2,#00H
    MOV     R3,#00H
    
PAIXU:
	MOV     R0,#40H
	MOV     A,@R0
	MOV     R3,A
F1:	
	INC     R0
	MOV     A,@R0
	SUBB    A,R3
	JNC     F2      //���޽�λ�����λ�ȵ�λ�����轻��
	MOV     A,@R0   //���н�λ����������
	MOV     R2,A
	MOV     A,R3
	MOV     @R0,A
	DEC     R0
	MOV     A,R2
	MOV     @R0,A
	INC     R0
	CLR     C
	CJNE    R0,#4FH,F1
F2:
	MOV     A,@R0
	MOV     R3,A
	CLR     C
	CJNE    R0,#4FH,F1
	INC     R1
	CJNE    R1,#4FH,PAIXU
    
    MOV     R0,#4FH     //���������С��
    MOV     A,@R0
    MOV     R0,A
    MOV     R1,#40H
    MOV     A,@R1
    MOV     R1,A
    
    SJMP    $

ORG 0500H
DB 22H,55H,0A0H,11H,0C0H,99H,12H,0B0H,44H,0F1H,77H,33H,0EFH,66H,88H,0D0H
    
END