
#include "bsp.h"
unsigned char  RH_DATA[5];

void main()
{  
   	BSP_INIT();	 //所有器件初始化    	
	LcmClearTXT();
 //   PutStr(0,0,"温湿度检测系统");
	while(1) 
	{ 
		DS1302_DA_TI();//日期时间
		Delay(10);
		RH();
		PutStr(3,0,SHOW_HT);//温湿度
	//	LcmClearTXT();
		DelayXms(500);
		DelayXms(300);
	//	SEND_SIM900();
	}	
}




