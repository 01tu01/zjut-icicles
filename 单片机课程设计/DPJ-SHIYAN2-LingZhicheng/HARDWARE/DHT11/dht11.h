#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//DHT11��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//IO��������
#define DHT11_IO_IN()  {GPIOA->MODER&=~(3<<(6*2));GPIOA->MODER|=0<<(6*2);}	//PB12����ģʽ
#define DHT11_IO_OUT() {GPIOA->MODER&=~(3<<(6*2));GPIOA->MODER|=1<<(6*2);} 	//PB12���ģʽ
 
////IO��������											   
#define	DHT11_DQ_OUT    PAout(6)//���ݶ˿�	PB12
#define	DHT11_DQ_IN     PAin(6) //���ݶ˿�	PB12 

typedef struct
{
	u8 temp;    //�¶���������
	u8 humi;     //ʪ����������
	u8 temp1;    //�¶�С������
	u8 humi1;    //ʪ��С������
	u8 isUpdate;	
}dht22_dev;
   	
u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11  
u8 DHT11_Read(dht22_dev *dht22);
#endif
