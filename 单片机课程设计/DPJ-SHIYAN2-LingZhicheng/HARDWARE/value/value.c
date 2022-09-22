#include "value.h"
#include "stdlib.h"
#include "string.h"
Data_dev DataInfo; //������Ϣ�ṹ��

_data_dev data;

//��buf����õ���cx���������ڵ�λ��
//����ֵ:0~0XFE,����������λ�õ�ƫ��.
//       0XFF,�������ڵ�cx������							  
u8 NMEA_Comma_Pos(u8 *buf,u8 cx)
{	 		    
	u8 *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//����'*'���߷Ƿ��ַ�,�򲻴��ڵ�cx������
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}
//m^n����
//����ֵ:m^n�η�.
u32 NMEA_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}
//strת��Ϊ����,��','����'*'����
//buf:���ִ洢��
//dx:С����λ��,���ظ����ú���
//����ֵ:ת�������ֵ
int NMEA_Str2num(u8 *buf,u8*dx)
{
	u8 *p=buf;
	u32 ires=0,fres=0;
	u8 ilen=0,flen=0,i;
	u8 mask=0;
	int res;
	while(1) //�õ�������С���ĳ���
	{
		if(*p=='-'){mask|=0X02;p++;}//�Ǹ���
		if(*p==','||(*p=='*'))break;//����������
		if(*p=='.'){mask|=0X01;p++;}//����С������
		else if(*p>'9'||(*p<'0'))	//�зǷ��ַ�
		{	
			ilen=0;
			flen=0;
			break;
		}	
		if(mask&0X01)flen++;
		else ilen++;
		p++;
	}
	if(mask&0X02)buf++;	//ȥ������
	for(i=0;i<ilen;i++)	//�õ�������������
	{  
		ires+=NMEA_Pow(10,ilen-1-i)*(buf[i]-'0');
	}
	if(flen>5)flen=5;	//���ȡ5λС��
	*dx=flen;	 		//С����λ��
	for(i=0;i<flen;i++)	//�õ�С����������
	{  
		fres+=NMEA_Pow(10,flen-1-i)*(buf[ilen+1+i]-'0');
	} 
	res=ires*NMEA_Pow(10,flen)+fres;
	if(mask&0X02)res=-res;		   
	return res;
}
//������ǰ�ƶ�һλ
void DataMoveForward(u16 dat[])
{
	u16 i=0;
	for(i=0;i<Dnum-1;i++)
	{
	  dat[i]=dat[i+1];
	}
	
}
//�������յ��Ĵ�����Ϣ
// 
//buf:���յ���GPS���ݻ������׵�ַ
u8 data_Analysis(  u8 *buf)
{
	u8 *p1,dx,i,ID;			 
	u8 posx;     
	u32 temp;	   
	  
	u16 datN,Lt;
	p1=(u8*)strstr((const char *)buf,"data");     //" ���ҵ�data�ַ���
	
 if(DataInfo.mode==0&&DataInfo.RevAdrr>0)//WiFiģʽ �Ҳ���ȫ����ģʽ
 { 
	 ID=*(p1+4)-0x30;
  if(DataInfo.RevAdrr!=ID)
		return 0; //����������Ҫ���յ�����ID��һ���˳�
 }
	
	for(i=0;i<Dtype;i++)
	{
		posx=NMEA_Comma_Pos(p1,i+1);								//��i������
		if(posx!=0XFF)
		{
			
			if(i==2)//Mq2
			   temp=MQ2_get(NMEA_Str2num(p1+posx,&dx));
//			else if(i==6)//Mq7
//			   temp=MQ7_get(NMEA_Str2num(p1+posx,&dx));
			else 	 
			   temp=NMEA_Str2num(p1+posx,&dx); 
			
			
			Lt=i;//��1~9������
			if(DataInfo.Revnum[Lt]<Dnum)//�жϽ��յ������Ƿ�ﵽ���� δ��������
			{
				datN=DataInfo.Revnum[Lt]; //��Ҫ���յĵڼ����ֽ����� ��ֵ��N
				DataInfo.DataBuff[Lt][datN]=temp;//��ֵ
				DataInfo.Revnum[Lt]++; //����������һ
				
			}
			else
			{
			 DataMoveForward(DataInfo.DataBuff[Lt]);	//������ǰ�ƶ�һλ�����µ����ݸ�ֵ���������һλ
			 datN=Dnum-1;		
			 DataInfo.DataBuff[Lt][datN]=temp;//��ֵ
			}	 
		}	  
	}  
	return 1;
}
//���߲�������
void QxPra(u8 ch)
{ 
	DataInfo.DtypeSel=ch;//��ǰѡ����ĸ���������
  switch(ch)
	{
	  case 0://  �¶�  
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
		 case 1:// ʪ�� 
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
		 case 2:// MQ2(����)�� 
		   DataInfo.Yxs=30;//Y�� ϵ�� ��ֵ������Y����������Ϊ6000
		break;
		case 3:// pm2.5�� 
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
	  case 4:// ��pm1.0 
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
	  case 5:// PM10 
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
	  case 6:// MQ7(co) 
		   DataInfo.Yxs=0.5;//Y�� ϵ�� ��ֵ������Y����������Ϊ100
		break;
		case 7:// co2 
		   DataInfo.Yxs=15;//Y�� ϵ�� ��ֵ������Y����������Ϊ3000
		break;
	  case 8:// TVOC
		   DataInfo.Yxs=15;//Y�� ϵ�� ��ֵ������Y����������Ϊ3000
		break; 
	}


}

//����ֵ��������
void BjPra(u8 ch)
{ 
	DataInfo.DtypeSel=ch;//��ǰѡ����ĸ���������
	DataInfo.Atemp=DataInfo.Avalue[DataInfo.DtypeSel];
  switch(ch)
	{
	  case 0://  �¶�  
		   DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
		 case 1:// ʪ�� 
		  DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
		 case 2:// MQ2(����)
		  DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
		case 3:// pm2.5�� 
		   DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
	  case 4:// ��pm1.0 
		    DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
	  case 5:// PM10 
		   DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
	  case 6:// MQ7(co) 
		    DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
		case 7:// co2 
		    DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break;
	  case 8:// TVOC
		    DataInfo.LAn=5;//  //  �����������ڰ�ѹ״̬ ����׷�ӵ����ֵ
		break; 
	}


}

// ����ֵ�ȽϺ���
void BjzBj(void)
{u16 i=0;
	DataInfo.Af=0;
  for(i=0;i<Dtype;i++)
	{
	  if(DataInfo.DataBuff[i][DataInfo.Revnum[i]-1]>DataInfo.Avalue[i])//������µ����һ��ֵ���ڱ���ֵ
		{ 
		   DataInfo.Af|=1<<i;
		} 
	}
  if(DataInfo.Af>0)
		PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ����� ��
	else 
		PCF8574_WriteBit(BEEP_IO,1);	//���Ʒ����� ��


}






