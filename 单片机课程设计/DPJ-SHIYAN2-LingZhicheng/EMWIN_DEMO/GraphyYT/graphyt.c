#include "graphyt.h"
#include "DIALOG.h"
#include "stdlib.h"
#include "math.h"
#include "GUI.h"
#include "usart.h"
#include "adc.h"
#include "malloc.h"
#include "includes.h"
#include "timer.h"
#include "led.h"
#include "value.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//STemwin GRAPH�ؼ�ʹ��   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/3/19
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
const u8*  mmenu_tbl[9]=//ϵͳһ��Ŀ¼�ĸ���
{
	// �¶ȡ�ʪ�ȡ�MQ2(����)��pm2.5��pm1.0��PM10��MQ7(co)��co2��TVOC
	"Temp",
	"Humi",
	"MQ-2",
	"PM2.5",
	"PM1.0",
	"PM10",
	"O3",
	"Co2",
	"TVOC", 
	 
	 
};

int				GClose=0;
//�ؼ�ID
#define ID_FRAMEWIN_0 	(GUI_ID_USER + 0x00)
#define ID_GRAPH_0 		(GUI_ID_USER + 0x01)
#define ID_BUTTON_0 	(GUI_ID_USER + 0x02)
#define ID_BUTTON_1 	(GUI_ID_USER + 0x03)
#define ID_BUTTON_2 	(GUI_ID_USER + 0x04)
#define ID_BUTTON_3 	(GUI_ID_USER + 0x05)
#define ID_BUTTON_4 	(GUI_ID_USER + 0x06)
#define ID_BUTTON_5 	(GUI_ID_USER + 0x07)

#define BORDER_TOP        	10
#define BORDER_BOTTOM     	15
#define BORDER_LEFT       	40
#define BORDER_RIGHT      	10

#define VERMULTIPLE         (10)        //��ֱ�̶���������

static GRAPH_SCALE_Handle hScaleV;   	//��ֱ�̶Ⱦ�� 
static GRAPH_SCALE_Handle hScaleH;   	//ˮƽ�̶Ⱦ��


_oscill_dev oscilldev;

GUI_COLOR LineColor[]={GUI_RED,GUI_BLACK,GUI_WHITE,GUI_YELLOW,GUI_BLUE,GUI_DARKMAGENTA};
GUI_COLOR BackColor[]={GUI_BLACK,GUI_LIGHTRED,GUI_DARKMAGENTA,GUI_WHITE,GUI_GREEN};
//�Ի�����Դ��
 
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 0x64, 0},
	{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 8, 8, 454, 230, 0, 0x0, 0},
 
};
//FrameWin�ؼ��ص�����
static void _cbFrame_exe(WM_MESSAGE * pMsg) 
{ 
  switch (pMsg->MsgId) 
 { 
  case WM_NOTIFY_PARENT: 
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED)
	  { 
      int Id = WM_GetId(pMsg->hWinSrc);      // Id of widget 
      if (Id == GUI_ID_CLOSE) 
		  { 
          GClose=1;  //����Ҫ�ڹرնԻ���ǰ�������� 
      } 
    } 
    FRAMEWIN_Callback(pMsg); 
    break; 
  default: 
    FRAMEWIN_Callback(pMsg); 
    break;   
 }  
}
 
//�Ի���ص�����
static void _cbDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	//int NCode;
//	int Id;
	
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
			//��ʼ��FRAMEWIN
			hItem = pMsg->hWin;
			FRAMEWIN_SetText(hItem, (void*)mmenu_tbl[DataInfo.DtypeSel]);//��������
			FRAMEWIN_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);//GUI_FONT_24B_ASCII
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	 FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
			//��ʼ��GRAPH
			hItem=WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			oscilldev.linecolorindex=0;	        //����Ĭ�Ϻ�ɫ
			oscilldev.backcolorindex=2;	        //����Ĭ�Ϻ�ɫ
			oscilldev.linecolor=LineColor[oscilldev.linecolorindex];
			oscilldev.backcolor=BackColor[oscilldev.backcolorindex];
			oscilldev.graphdata=GRAPH_DATA_YT_Create(oscilldev.linecolor,401,0,0);  //����YT���ݶ���
			GRAPH_AttachData(hItem,oscilldev.graphdata);		                    //�����ݶ�����ӵ�GRAPH�ؼ���
			GRAPH_SetBorder(hItem,BORDER_LEFT,BORDER_TOP,BORDER_RIGHT,BORDER_BOTTOM);//���ñ߽�
            GRAPH_SetGridDistX(hItem,50);		//����ˮƽ������
			GRAPH_SetGridDistY(hItem,20);		//���ô�ֱ������
			GRAPH_SetGridVis(hItem,1);			//��������ɼ�
		
			hScaleV=GRAPH_SCALE_Create(35,GUI_TA_RIGHT,GRAPH_SCALE_CF_VERTICAL,20); //���ƴ�ֱ�̶�
			GRAPH_SCALE_SetTextColor(hScaleV,GUI_YELLOW);
			GRAPH_AttachScale(hItem,hScaleV);   //���̶ȶ��󸽼ӵ�ͼ��С����
            GRAPH_SCALE_SetFactor(hScaleV,DataInfo.Yxs);  //���ÿ̶�ϵ��
            GRAPH_SCALE_SetOff(hScaleV,000);    //0  ���� 0 ����Ҫ��ֵ ��ֱ�̶������ƶ�200�����ص㣬������ֱ�̶Ȼ��и�ֵ
			
			hScaleH=GRAPH_SCALE_Create(218,GUI_TA_HCENTER,GRAPH_SCALE_CF_HORIZONTAL,50);//����ˮƽ�̶�
			GRAPH_SCALE_SetFactor(hScaleH,0.1);  //���ÿ̶�ϵ��
			GRAPH_SCALE_SetTextColor(hScaleH,GUI_DARKGREEN);
			GRAPH_AttachScale(hItem,hScaleH);   //���̶ȶ��󸽼ӵ�ͼ��С����
 
			break;
		 case WM_NOTIFY_PARENT:  
			 
		 
		default:
			WM_DefaultProc(pMsg);
			break;
  }
}

//��������WM_HBKWIN�ص�����
static void _cbBkWindow(WM_MESSAGE* pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear(); 
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

//ͼ����ʾdemo
void Graphyt_demo(void) 
{
	WM_HWIN hWin,ClientWin;
	//int Graph_xSize,Graph_ySize;                
	int i;
   
	WM_SetCallback(WM_HBKWIN,_cbBkWindow);    //���ñ������ڻص�����
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN,0,0);
	
	//Ϊ��ܴ������ûص�����
  WM_SetCallback(hWin,_cbFrame_exe);
	ClientWin = WM_GetDialogItem(hWin, ID_GRAPH_0);
	WM_GetWindowSizeX(ClientWin);//Graph_xSize=
	WM_GetWindowSizeY(ClientWin);//Graph_ySize=
	 
	 
	GUI_Exec();
	GClose=0;
    	for(i=0;i<DataInfo.Revnum[DataInfo.DtypeSel];i++) //��GRAPHͼ��С�����������,ע��Ҫ��20������Ϊ��ֱ��������(����)DataInfo.Yxs���� 
			{  
			 	GRAPH_DATA_YT_AddValue(oscilldev.graphdata,DataInfo.DataBuff[DataInfo.DtypeSel][i]/DataInfo.Yxs+ 0);
			}
			
	while(1)
	{  LED1 = !LED1;
		if(GClose==1)
    { 
		  WM_DeleteWindow(hWin);//ɾ������ 
	    return;
	  }
		if(DataInfo.qxdate==1)//��һ�����ݸ���һ������
		{	
			GRAPH_DATA_YT_AddValue(oscilldev.graphdata,DataInfo.DataBuff[DataInfo.DtypeSel][DataInfo.Revnum[DataInfo.DtypeSel]-1]/DataInfo.Yxs+ 0);
			 
 			DataInfo.qxdate=0;//��־����	
		}
		GUI_Delay(100);
	}
	 
}

