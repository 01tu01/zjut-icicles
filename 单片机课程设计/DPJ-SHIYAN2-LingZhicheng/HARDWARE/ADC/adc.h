#ifndef __ADC_H
#define __ADC_H
#include "sys.h"


#define Q0 PHout(5)	 
#define Q1 PHout(2)	

typedef struct
{
	u16 mq2,mq7;
	u8 isUpdate;
}adc_dev;

void Q_Init(void);
void MY_ADC_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u32 ch); 		        //���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u32 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ

#endif 
