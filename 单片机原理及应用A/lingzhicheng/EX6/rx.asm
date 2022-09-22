		ORG		0000H
		LJMP	START
		ORG		0023H
		LJMP	IF_06H
		ORG		1000H
			
START:
		MOV		SP,#60H
		MOV		TMOD,#20H		//��ʱ��0����ʱ������ģʽ2����
		MOV		TH1,#0FAH		//ģʽ2�Զ���װ�صĳ�ֵ
		MOV		TH1,#0FAH
		SETB 	TR1		 		//��ʼ��ʱ
		MOV		SCON,#50H		//��ʽ1,�������-->4.8kbit/s
		MOV		PCON,#00H		//SMOD=0
		MOV		IE,#90H
		MOV		R0,30H			//��ŷ��͵����ݿ��׵�ַ
		MOV		R7,#00H			//��ŷ��͵����ݿ鳤��
		MOV		R6,#00H			//У��ͣ������ֽ��������ֽڵ��ۼӺ�
		
HERE:
		SJMP	HERE
		
IF_06H:
		PUSH	ACC
		PUSH	PSW
		CLR		RI				//����������RI��־λ
		MOV		A,SBUF			//�˶������ź��ǲ���06H
		CJNE	A,#06H,TX_15H	//�����06H����00HӦ�𣬷�����15H�ܾ�

TX_00H:
		MOV		A,#00H			
		MOV		SBUF,A			//���ͳ�00H��ʾ���Խ�������
		LJMP	HERE_RE
		
TX_15H:
		MOV		A,#15H			//����15H��ʾ�����Խ���
		MOV		SBUF,A
		LJMP	RETURN
			
HERE_RE:
		JNB		TI,HERE_RE		//�ȴ�������ϣ��������׼������
		CLR		TI
		
HAVE1:
		JNB		RI,HAVE1		//�ȴ��������ݳ���
		CLR		RI
		MOV		A,SBUF
		MOV		R7,A			//R7�����ݳ���
		MOV		R6,A			//R6��У���

HAVE2:
		JNB		RI,HAVE2		//�ȴ�������ʽ����		
		CLR		RI
		MOV		A,SBUF
		MOV		@R0,A
		MOV		A,R6
		ADD		A,@R0
		MOV		R6,A
		INC		@R0
		DJNZ	R7,HAVE2		//���û��������20�����ݣ���������
		
RX_CHECK:						//����У���
		JNB		RI,RX_CHECK
		CLR		RI		
		MOV		A,SBUF
		MOV		39H,A
		CJNE	A,39H,TX_ERR	//���У����ȷ�����������ok����������#F0H
		
TX_OK:							//У����ȷ������0FH
		MOV		A,#0FH
		MOV		SBUF,A
		LJMP	HERE_END
			
TX_ERR:							//У����󣬷���F0H
		MOV		A,#0F0H
		MOV		SBUF,A			
		
HERE_END:						//�ȴ��������
		JNB TI,HERE_END	 	
		CLR TI

RETURN:
		POP		PSW
		POP		ACC
		RETI

		END
			