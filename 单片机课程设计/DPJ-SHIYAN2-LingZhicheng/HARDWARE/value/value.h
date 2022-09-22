#ifndef _VALUE_H
#define _VALUE_H
#include "sys.h"
#include "usart3.h"	 
#include "MQ.h"
#include "malloc.h"
#include "tftlcd.h"
#include "ltdc.h"
#include "tftlcd.h"
#include "touch.h" 
#include "24cxx.h"
#include "pcf8574.h"
#include "PMS5003.h"
#include "dht11.h"
#include "sgp30.h"
#include "adc.h"
#include "common.h"

#define Dnum     400    //������ʾ������������

#define Dtype    9     //������������� �¶ȡ�ʪ�ȡ�MQ2(����)��pm2.5��pm1.0��PM10��MQ7(co)��co2��TVOC

#define adrr    200   //����ֵ�洢��ַ
typedef struct 
{
	 
	u8  update;                  //���ݸ��±�־ 
	u16 Revnum[Dtype];           //�ѽ��յ�����������
  u16 DataBuff[Dtype][Dnum];	 //���ݻ�������
	
	//�������
	u8  qxdate;   //������Ҫ����
	u8  DtypeSel;// ��������ѡ��
	float Yxs;   //Y��ϵ�� ���ڵ��� Y������ֵ  
	
	//����	 
	s16 Avalue[Dtype];          // ����ֵ����
	u16 Af;                     // ����ֵ ��־ 0-8 λ��Ӧ0-8���������� 
	s16 Atemp;                  //  �����ݴ�ֵ  
	u16 LAn;                    //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
	
	//
	u8 mode;// �豸�������ĸ�ģʽ��  0 wifi  1�ɼ�ģʽ
	u8 wifiF;//�Ƿ�������
	u32 Wificnt;
	u8  Wifidat[100];
	u8 RevAdrr;// 0ȫ������ 1-9���ն�Ӧ��id�ն��豸
}Data_dev;  
extern Data_dev DataInfo; //������Ϣ�ṹ��

typedef struct
{
	_pms_dev *pms;
	dht22_dev *dht22;
	adc_dev *adc;
	sgp30_dev *sgp;
	u8 level;
}_data_dev;

extern _data_dev data; 



u8 data_Analysis(  u8 *buf);//���ݷ���
//���߲�������
void QxPra(u8 ch);
 //����ֵ��������
void BjPra(u8 ch);
// ����ֵ�ȽϺ���
void BjzBj(void);
#endif


