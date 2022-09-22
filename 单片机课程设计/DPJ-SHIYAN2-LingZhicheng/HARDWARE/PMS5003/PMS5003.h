#ifndef _PMS5003_H
#define _PMS5003_H
#include "sys.h"
#include "stdio.h"
#include "usart.h"

typedef struct 
{
	u16 length;      //֡����
	u16 data1;       //PM1.0Ũ��(CF=1,��׼������) ��λug/m3
	u16 data2;       //PM2.5Ũ��(CF=1,��׼������) ��λug/m3
	u16 data3;       //PM10 Ũ��(CF=1,��׼������) ��λug/m3
	u16 data4;       //PM1.0Ũ��(����������) ��λug/m3
	u16 data5;       //PM2.5Ũ��(����������) ��λug/m3
	u16 data6;       //PM10 Ũ��(����������) ��λug/m3
	u16 data7;       //0.1��������ֱ����0.3um���Ͽ��������
	u16 data8;       //0.1��������ֱ����0.5um���Ͽ��������
	u16 data9;       //0.1��������ֱ����1.0um���Ͽ��������
	u16 data10;      //0.1��������ֱ����2.5um���Ͽ��������
	u16 data11;      //0.1��������ֱ����5.0um���Ͽ��������
	u16 data12;      //0.1��������ֱ����10um���Ͽ��������
	u8 id;           //�汾��
	u8 error;        //�������
	u16 checksum;    //У���
	u8 isUpdate;
}_pms_dev;



u8 Proces_Data(u8 buf[],_pms_dev* pms);


#endif
