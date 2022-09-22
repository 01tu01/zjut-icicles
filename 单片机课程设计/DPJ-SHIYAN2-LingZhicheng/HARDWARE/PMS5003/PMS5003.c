#include "sys.h"
#include "stdio.h"
#include "usart.h"
#include "PMS5003.h"



u8 Proces_Data(u8 buf[], _pms_dev* pms)
{
	u8 i;                   //״̬
    u16 sum = 0;
    DATA_LEN = 0x1c;              // ����֡���� = 2*13 + 2   ����+У��λ
      pms->length = DATA_LEN; 
	//У����
		pms->checksum = ((buf[26]<<8) + buf[27]);
		sum = 0x42 + 0x4d + (u8)DATA_LEN & 0xff;   
   	for(i = 0 ; i < 26 ; i++)
	  {
		    sum += buf[i];
	  }

	  if (pms->checksum == sum) {}                      
		else return 0;
			
//CF=1,��׼������
        pms->data1 = (buf[0] << 8) + buf[1];   
    	  pms->data2 = (buf[2] << 8) + buf[3];
	      pms->data3 = (buf[4] << 8) + buf[5];
//����������
	      pms->data4 = (buf[6] << 8) + buf[7];
				pms->data5 = (buf[8] << 8) + buf[9];
				pms->data6 = (buf[10] << 8) + buf[11];  
//0.1L������
				pms->data7 = (buf[12] << 8) + buf[13];
				pms->data8 = (buf[14] << 8) + buf[15];
				pms->data9 = (buf[16] << 8) + buf[17];
				pms->data10 = (buf[18] << 8) + buf[19];
				pms->data11 = (buf[20] << 8) + buf[21];
				pms->data12 = (buf[22] << 8) + buf[23];
//�汾��+�������
				pms->id = buf[24];
				pms->error = buf[25];
}
