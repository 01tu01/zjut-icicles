		ORG		0000H
		LJMP	START
		ORG		1000H
			
START:
		MOV		SP,#60H
		MOV		TMOD,#20H		//��ʱ��0����ʱ������ģʽ2����
		MOV		TH1,#0FAH		//ģʽ2�Զ���װ�صĳ�ֵ
		MOV		TH1,#0FAH
		SETB 	TR1		 		//��ʼ��ʱ
		MOV		SCON,#50H		//��ʽ1����,�������-->4.8kbit/s
		MOV		PCON,#00H		//SMOD=0
		MOV		R0,30H			//��ŷ��͵����ݿ��׵�ַ
		MOV		R7,#20H			//��ŷ��͵����ݿ鳤��
		MOV		R6,#00H			//У��ͣ������ֽ��������ֽڵ��ۼӺ�
		
TX_ACK:	
		MOV		A,#06H			//����06Hѯ���Ƿ���Խ�������
		MOV		SBUF,A
		
WAIT1:	
		JNB		TI,WAIT1		//�ȴ�������һ���ֽ�
		CLR		TI				//����������TI��־λ

RX_YES:	
		JNB		RI,RX_YES		//�ȴ��һ��ش��Ƿ���Խ���
		CLR		RI				//����������RI��־λ
		
NEXT1:	
		MOV		A,SBUF			//���յ��һ����͹�����ACK
		CJNE	A,#00H,TX_ACK  	//��Ϊ00H���ʾ���Խ������ݣ������������ͣ������ٴ�ѯ��
		
TX_LENGTH:
		MOV		A,R7			//�ȷ����ֽڳ�����R7
		MOV		SBUF,A
		
WAIT2:
		JNB		TI,WAIT2		//�ȴ����ݷ������
		CLR		TI				//����������TI��־λ
		MOV		R6,A			//����У���

TX_NEWS:						//��ѯ��������
		MOV		A,@R0
		MOV		SBUF,A
		
TX_NEWS_WAIT:
		JNB		TI,TX_NEWS_WAIT
		CLR		TI				//����������TI��־λ
		MOV		A,R6
		ADD		A,@R0
		MOV		R6,A
		INC		@R0
		DJNZ	R7,TX_NEWS		//���û������32�����ݣ���������
		
TX_CHECK:
		MOV		A,R6
		ADD		A,@R0
		MOV		R6,A
		MOV		A,R6			//����У��λ
		MOV		SBUF,A
		
WAIT3:							//�ȴ�������У��λ
		JNB		TI,WAIT3
		CLR		TI
		
WAIT4:							//�ȴ�������У��λ
		JNB		RI,WAIT4
		CLR		RI
		
IF_0FH:
		MOV		A,SBUF			//�����յ�У���Ƿ���ȷ�Ļָ��浽�ۼ���
		CJNE	A,#0FH,START

HERE:	
		SJMP	HERE

		END
		
