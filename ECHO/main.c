
#include "bsp.h"
unsigned char  RH_DATA[5];

void main()
{  
   	BSP_INIT();	 //����������ʼ��    	
	LcmClearTXT();
 //   PutStr(0,0,"��ʪ�ȼ��ϵͳ");
	while(1) 
	{ 
		DS1302_DA_TI();//����ʱ��
		Delay(10);
		RH();
		PutStr(3,0,SHOW_HT);//��ʪ��
	//	LcmClearTXT();
		DelayXms(500);
		DelayXms(300);
	//	SEND_SIM900();
	}	
}




