#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "tftlcd.h"
#include "adc.h"
#include "pcf8574.h"
#include "timer.h"
#include "sdram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "WM.h"
#include "graphyt.h"
#include "includes.h"
#include "DIALOG.h"
#include "Display.h"
#include "value.h"
 

//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С	
#define START_STK_SIZE 				128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				128
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				5
//�����ջ��С
#define LED0_STK_SIZE				628
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			6
//�����ջ��С
#define EMWINDEMO_STK_SIZE			712
//������ƿ�
OS_TCB EmwindemoTaskTCB;
//�����ջ
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *p_arg);
 //PORT��ʼ��
void PORT_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOF_CLK_ENABLE();   //ʹ��GPIOFʱ��
    
	  //PF7���ڴ�������Ϳ����干��
    //PF7��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	
	  __HAL_RCC_GPIOH_CLK_ENABLE();   //ʹ��GPIOHʱ��
    
	  //PH2,PH3����MQ7���ȵ�ƽ
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3 ;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
		
		   
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET);   //PF7��ʼ����Ϊ0
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_RESET);   //PH2��ʼ����Ϊ0,����Q1
		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_SET);   //PH3��ʼ����Ϊ1������Q0
	
}

int main(void)
{
		u8 i=0;
		OS_ERR err;
		CPU_SR_ALLOC();
    
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz  
	
    HAL_Init();                     //��ʼ��HAL��
    delay_init(180);                //��ʼ����ʱ����
	
    uart_init(115200);              //��ʼ��USART

	  usart3_init(115200);
	
	
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    PCF8574_Init();                 //��ʼ��PCF8574
    MY_ADC_Init();                  //��ʼ��ADC
    SDRAM_Init();                   //SDRAM��ʼ��
    TFTLCD_Init();  		        		//LCD��ʼ��
    TP_Init();				        			//��������ʼ��
	
    my_mem_init(SRAMIN);    		    //��ʼ���ڲ��ڴ��
		my_mem_init(SRAMEX);    		    //��ʼ���ⲿ�ڴ��
		my_mem_init(SRAMCCM);    		    //��ʼ��CCM�ڴ��
		
	
	  SGP30_Init(); 
    SGP30_Start_Measure();
		DHT11_Init(); 
		
		PORT_Init();
		
		for(i=0;i<Dtype;i++)
		  AT24CXX_Read(adrr+i*2,(u8*)&DataInfo.Avalue[i],2) ;//��ȡ����ֵ����
	
//		while(1) 
//		{
//			DHT11_Read(data.dht22);
//		
//		}
	 
    
    
    OSInit(&err);		            //��ʼ��UCOSIII
	OS_CRITICAL_ENTER();            //�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	            //�˳��ٽ���	 
	OSStart(&err);                  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	//ʹ��ʱ��Ƭ��ת���ȹ���,����Ĭ�ϵ�ʱ��Ƭ����
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	__HAL_RCC_CRC_CLK_ENABLE();		//ʹ��CRCʱ��
    WM_SetCreateFlags(WM_CF_MEMDEV); //�������д��ڵĴ洢�豸
	GUI_Init();  			//STemWin��ʼ��
	WM_MULTIBUF_Enable(1);  //����STemWin�໺��,RGB�����ܻ��õ�
	OS_CRITICAL_ENTER();	//�����ٽ���
	//STemWin Demo����	
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,		
				 (CPU_CHAR*   )"Emwindemo task", 		
                 (OS_TASK_PTR )emwindemo_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,     
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//����������
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);			 
	//LED0����
	OSTaskCreate((OS_TCB*     )&Led0TaskTCB,		
				 (CPU_CHAR*   )"Led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK*    )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);	                 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}
extern WM_HWIN CreateFramewin(void);
extern WM_HWIN CreateIamgeFramewin(void);
extern WM_HWIN CreateInputPassword(void);
//EMWINDEMO����
u8 mf=1; 
void emwindemo_task(void *p_arg)
{
	GUI_CURSOR_Show();
	//����Ƥ��
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	 CreateIamgeFramewin();//��ʾͼƬ
	 CreateInputPassword();//������֤
	 mf=0;//����������ȷ
		while(1)
		{
			CreateFramewin(); 
		}
}

//TOUCH����
void touch_task(void *p_arg)
{
	OS_ERR err;
	
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *p_arg)
{	CPU_SR_ALLOC();
	OS_ERR err;
	u8 cnt=0,modeT=0xff,key,i=0,res=0;
	 u16 co2 = 0,tt=1000;
	 u16 tvoc = 0;
	 u16 mq2,mq7;
//	u8 constate=0;	//����״̬
	char p[100]; 
  data.adc = mymalloc(SRAMEX, sizeof(adc_dev));
	data.dht22 = mymalloc(SRAMEX, sizeof(dht22_dev));
	data.pms = mymalloc(SRAMEX, sizeof(_pms_dev));
	data.sgp = mymalloc(SRAMEX, sizeof(sgp30_dev));
	
	//DataInfo.mode=1;
  DataInfo.mode=0;
	
	printf("pre-11111111111111111111111111DataInfo.mode=%d\r\n",DataInfo.mode);
	
	DataInfo.wifiF=0;
	DataInfo.RevAdrr=0;//Ĭ�Ͻ���ȫ���ɼ��ն� ����
	
	//��ֹ��һ�βɼ����ݴ��� �Ȳɼ�һ��
	
	if (USART_RX_STA & 0x8000)//��ȡPMS5003 ���� PM1.0 2.5 10
	{		 
			Proces_Data(USART_RX_BUF, data.pms) ; 
			USART_RX_STA = 0;  
	}
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	DHT11_Read(data.dht22);//��ȡ��ʪ������ 
	Read_Air_Quality(&co2, &tvoc);
	OS_CRITICAL_EXIT();	//�˳��ٽ���
	
	while(mf)
		delay_ms(10);//����������ȷ���ڽ���ɼ�ģʽ
	
	
	while(1)
	{  
		if(cnt++>50)
		{
			LED0 = !LED0;
			cnt=0;
		}
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//��ʱ10ms
	  key=KEY_Scan(0);
		
	  if(key==WKUP_PRES)
			//DataInfo.mode=!DataInfo.mode;			//�л�����ģʽ
		DataInfo.mode=0;
		
		else if(key==KEY2_PRES)
		{
			if(DataInfo.mode==0)//wifiģʽ
		  { 
				DataInfo.RevAdrr++;
				
				if(DataInfo.RevAdrr>9)
					DataInfo.RevAdrr=0;
			}
			
			DataInfo.RevAdrr=0;//ʹ��WIFI0���ա���
			
			
		}
		
		if(modeT!=DataInfo.mode)//ģʽ�л�
		{
		  modeT=DataInfo.mode;//���棬��ֹÿ�ζ�����
			
			if(DataInfo.mode==0)//WiFiģʽ
			{  
				if(DataInfo.wifiF==0)//δ���� ��ʼ������
				{
					atk_8266_send_cmd("AT","OK",50);
					
				  atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//����WIFI STAģʽ
					atk_8266_send_cmd("AT+RST","OK",20);		//����ģ�� 
					
					delay_ms(4000);         //��ʱ2S�ȴ������ɹ�
					
					PCF8574_WriteBit(BEEP_IO,1);
					
				  printf("pre-222222222222222222222\r\n");
					
			  	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	        while(atk_8266_send_cmd(p,"WIFI GOT IP",300));					//����Ŀ��·����,���һ��IP
					
					PCF8574_WriteBit(BEEP_IO,1);
					printf("pre-33333333333333333333333\r\n");
					
					delay_ms(1000);
				
					sprintf((char*)p,"AT+CIPSTART=\"UDP\",\"255.255.255.255\",8080,8086");    //����Ŀ��UDP������ 8080 Զ�̶˿� 8086 ���ض˿�   ipbuf,,(u8*)portnum
					delay_ms(200);
					atk_8266_send_cmd("AT+CIPMUX=0","OK",20);  //������ģʽ
					delay_ms(200); 
					
					while(atk_8266_send_cmd(p,"OK",500)); 
					
					printf("pre-44444444444444444444444444444\r\n");
					
					memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));//����������0
					
				  USART3_RX_STA=0;		   	//������һ�ν���
					
				}
				
			  DataInfo.wifiF=0;// 
			}
			else//�ɼ�ģʽ
			{
				SGP30_Init(); //���³�ʼ��
				SGP30_Start_Measure();
				DHT11_Init(); 
		    uart_init(9600);              //��ʼ��USART
			}
		}
//		
		if(DataInfo.mode==1)//�ɼ�ģʽ
		{ 
			if(++tt>100)
			{tt=0;
				if (USART_RX_STA & 0x8000)//��ȡPMS5003 ���� PM1.0 2.5 10
				{		 
						Proces_Data(USART_RX_BUF, data.pms) ; 
						USART_RX_STA = 0;  
				}
			  OS_CRITICAL_ENTER();	//�����ٽ���
		    DHT11_Read(data.dht22);//��ȡ��ʪ������
			  OS_CRITICAL_EXIT();	//�˳��ٽ���
				mq2 = Get_Adc_Average(ADC_CHANNEL_7, 2)*1.22;
			  data.adc->mq2 =mq2;// MQ2_get(mq2); 
			//mq7=	(300- Get_Adc_Average(ADC_CHANNEL_6, 5))*1.5;//O3
		   
				 mq7 = Get_Adc_Average(ADC_CHANNEL_6, 2)*1.22;
			  data.adc->mq7 = MQ7_get(mq7);//mq7;//
				
				Read_Air_Quality(&co2, &tvoc);
					
			  data.sgp->co2 = co2;
			  data.sgp->tvoc = tvoc;
				//������������� �¶ȡ�ʪ�ȡ�MQ2(����)��pm2.5��pm1.0��PM10��MQ7(co)��co2��TVOC
				sprintf(p,"data,%d,%d,%d,%d,%d,%d,%d,%d,%d,ok",//temp,humi,Get_Adc_Average(5,5),data.data5,data.data4,data.data6,Get_Adc_Average(4,5),CO2,TVOC);
								      	data.dht22->temp, 
												data.dht22->humi, 
												data.adc->mq2,
												data.pms->data5,
												data.pms->data4, 
												data.pms->data6, 
												data.adc->mq7,
												data.sgp->co2,
												data.sgp->tvoc);	
			 data_Analysis( (u8*)p);//�����ַ���
       DataInfo.update=1;//ˢ�±�־��1
		   DataInfo.qxdate=1;//ˢ�±�־��1
			 BjzBj();	// ����ֵ�ȽϺ���
		 } 
		}   
    else //WiFi ����ģʽ
		{
		//	printf("pre-5555555555555555555555555\r\n");   
			if(USART3_RX_STA&0X8000)		//���յ�һ��������
			{ 
				printf("pre-6666666666666666666666666666666\r\n");
				
				res=data_Analysis( (u8*)USART3_RX_BUF);//�����ַ���
				
				if(res)//�����ɹ� ������Ҫ���յ��豸ID
				{
					DataInfo.Wificnt++;  
					for(i=0;i<90;i++)
						DataInfo.Wifidat[i]=USART3_RX_BUF[i];
					
					DataInfo.Wifidat[i]=0; 
				}
				
				memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));//����������0
				USART3_RX_STA=0;		   	//������һ�ν���
				DataInfo.update=1;//ˢ�±�־��1
				DataInfo.qxdate=1;//ˢ�±�־��1
			
				BjzBj();	// ����ֵ�ȽϺ���
				DataInfo.wifiF=1;//�ܽ������ݱ�־������
			} 
			
			
			
		}
		
		
		
		
		
		
	}
}



