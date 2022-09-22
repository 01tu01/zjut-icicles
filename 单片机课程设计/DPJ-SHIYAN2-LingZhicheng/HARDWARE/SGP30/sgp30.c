#include "sgp30.h"
#include "delay.h"
#include "usart.h"
//IO��������
#define sgp30SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define sgp30SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
//IO����
#define sgp30IIC_SCL   PBout(8) //SCL
#define sgp30IIC_SDA   PBout(9) //SDA
#define sgp30READ_SDA  PBin(9)  //����SDA

//IIC��ʼ��
static void SGP30IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOHʱ��
    
    //PB8,9��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    sgp30IIC_SDA=1;
    sgp30IIC_SCL=1;  
}

//����IIC��ʼ�ź�
static void SGP30IIC_Start(void)
{
	sgp30SDA_OUT();     //sda�����
	sgp30IIC_SDA=1;	  	  
	sgp30IIC_SCL=1;
	delay_us(4);
 	sgp30IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	sgp30IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
static void SGP30IIC_Stop(void)
{
	sgp30SDA_OUT();//sda�����
	sgp30IIC_SCL=0;
	sgp30IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	sgp30IIC_SCL=1; 
	sgp30IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
static u8 SGP30IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	sgp30SDA_IN();      //SDA����Ϊ����  
	sgp30IIC_SDA=1;delay_us(1);	   
	sgp30IIC_SCL=1;delay_us(1);	 
	while(sgp30READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			SGP30IIC_Stop();
			return 1;
		}
	}
	sgp30IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
static void SGP30IIC_Ack(void)
{
	sgp30IIC_SCL=0;
	sgp30SDA_OUT();
	sgp30IIC_SDA=0;
	delay_us(2);
	sgp30IIC_SCL=1;
	delay_us(2);
	sgp30IIC_SCL=0;
}
//������ACKӦ��		    
static void SGP30IIC_NAck(void)
{
	sgp30IIC_SCL=0;
	sgp30SDA_OUT();
	sgp30IIC_SDA=1;
	delay_us(2);
	sgp30IIC_SCL=1;
	delay_us(2);
	sgp30IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
static void SGP30IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	sgp30SDA_OUT(); 	    
    sgp30IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        sgp30IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		sgp30IIC_SCL=1;
		delay_us(2); 
		sgp30IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
static u8 SGP30IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	sgp30SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        sgp30IIC_SCL=0; 
        delay_us(2);
		    sgp30IIC_SCL=1;
        receive<<=1;
        if(sgp30READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        SGP30IIC_NAck();//����nACK
    else
        SGP30IIC_Ack(); //����ACK   
    return receive;
}


//��ʼ��IIC���ߣ�����SGP30
void SGP30_Init(void)
{	
	 SGP30IIC_Init();		//��ʼ��IIC����
	
	//�鿴SGP30�����кţ�ȷ��������������
	SGP30IIC_Start();
	SGP30IIC_Send_Byte(0x58<<1);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Send_Byte(0x36);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Send_Byte(0x82);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Stop();
}

//��ʼ��SGP30�Ŀ���������⹦��
void SGP30_Start_Measure(void)
{	
	//����Init_air_quality����
	SGP30IIC_Start();
	SGP30IIC_Send_Byte(0x58<<1);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Send_Byte(0x20);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Send_Byte(0x03);
	if(SGP30IIC_Wait_Ack()==1){}
	else{}
	SGP30IIC_Stop();
	
	//delay_ms(15000);		//��Ҫʱ�������г�ʼ��
	
	//����Measure_air_quality����
	SGP30IIC_Start();
	SGP30IIC_Send_Byte(0x58<<1);
	SGP30IIC_Wait_Ack();
	SGP30IIC_Send_Byte(0x20);
	SGP30IIC_Wait_Ack();
	SGP30IIC_Send_Byte(0x08);
	SGP30IIC_Wait_Ack();
	SGP30IIC_Stop();
}



void Read_Air_Quality(u16 *co2, u16 *tvoc)
{
	u8 co2_high = 0;
	u8 co2_low = 0;
	u8 tvoc_high = 0;
	u8 tvoc_low = 0;
	
	//����Measure_air_quality����
	SGP30IIC_Start();
	SGP30IIC_Send_Byte(0x58<<1);
	SGP30IIC_Wait_Ack();
	SGP30IIC_Send_Byte(0x20);
	SGP30IIC_Wait_Ack();
	SGP30IIC_Send_Byte(0x08);
  SGP30IIC_Wait_Ack();
	
	delay_ms(500);		//��Ҫʱ�������м��
	
	//���Ͷ���ַ����ȡ����16λ��Ũ��ֵ����Ӧ��8λCRC���ֵ
	SGP30IIC_Start();
	SGP30IIC_Send_Byte((0x58<<1)|0x01);     //read
	SGP30IIC_Wait_Ack();
	co2_high = SGP30IIC_Read_Byte(1);
	co2_low = SGP30IIC_Read_Byte(1);
	SGP30IIC_Read_Byte(1);
	tvoc_high = SGP30IIC_Read_Byte(1);
	tvoc_low = SGP30IIC_Read_Byte(1);
	SGP30IIC_Read_Byte(0);
	SGP30IIC_Stop();
	
	    *co2 = (co2_high<<8)|co2_low;
 	    *tvoc = (tvoc_high<<8)|tvoc_low;

}
/*
//��ȡ�������Ҵ�����Ũ��
void Read_Air_Quality_2(u16 *h2, u16 *ethanol)
{
	u8 h2_high = 0;
	u8 h2_low = 0;
	u8 ethanol_high = 0;
	u8 ethanol_low = 0;
	
	//����Measure_air_quality����
	IIC_Start();
	IIC_Send_Byte(0x58<<1);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x20);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x50);
	IIC_Wait_Ack();

	
	delay_ms(500);		//��Ҫʱ�������м��
	
	//���Ͷ���ַ����ȡ����16λ��Ũ��ֵ����Ӧ��8λCRC���ֵ
	IIC_Start();
	IIC_Send_Byte((0x58<<1)|0x01);     //read
	IIC_Wait_Ack();
	h2_high = IIC_Read_Byte(1);
	h2_low = IIC_Read_Byte(1);
  IIC_Read_Byte(1);
	ethanol_high = IIC_Read_Byte(1);
	ethanol_low = IIC_Read_Byte(1);
	IIC_Read_Byte(0);
	IIC_Stop();
	
	    *h2 = (h2_high<<8)|h2_low;
 	    *ethanol = (ethanol_high<<8)|ethanol_low;
			
}*/


