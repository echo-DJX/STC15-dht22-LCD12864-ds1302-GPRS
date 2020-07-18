#include"bsp.h"
uchar code initTime[] = {0x50, 0x53, 0x19, 0x25, 0x09, 0x05, 0x19};	 //初始化时间
unsigned char INT_TIME[]={60,254,24,24,24,24,24,200,40,40};

void BSP_INIT()
{   
    int K;
	TIN3_LONG=0;
	command=0; //当前执行命令
    INT_count=0;//计时
  // UATR_INIT();
  //  ES=0;//关串口
  // AUXR = 0x14;                //T2为1T模式, 并启动定时器2	
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
	P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
	PSB=0;           //LCD串口通信方式
	LcmInit();	       //LCD12864初始化				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	LcmClearTXT();	   //LCD12864清屏	
    DS1302_Initial();
	DS1302_Set1302(initTime);			//设置DS1302的日期和时间
	for(K=0;K<7;K++)
	  timenow[K]=0x00;
	Delay(100);
	LcmClearTXT();	   //LCD12864清屏

/*		UATR_INIT();
		RH_SEND();
		DelaySec(30);
		SendString("AT+CGCLASS=\"B\"\r\n");
		DelaySec(5);
		SendString("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");
		DelaySec(5);
		SendString("AT+CGATT=1\r\n");
		DelaySec(5);
	    SendString("AT+CIPCSGP=1,\"CMNET\"\r\n");
		DelaySec(5);
		SendString("AT+CLPORT=\"TCP\",\"4001\"\r\n");
		DelaySec(5);
		SendString("AT+CIPSTART=\"TCP\",\"183.230.40.34\",\"80\"\r\n");
		DelaySec(30);
		SendString("AT+CIPSEND\r\n");
		DelaySec(10);
		SendString("POST /devices/548152733/datapoints?type=3 HTTP/1.1\r\n");
		SendString("api-key:bVAsevzZT4dyobUj27iizubiL9Q=\r\n");
		SendString("Host:api.heclouds.com\r\n");
        SendString("Content-Length:36\r\n\n");
      //  SendString("{\"temperature\":11.5,\"humidity\":51.7}\r\n");
	  	SendString(SEND_HT);//发送温湿度过去
		DelaySec(10);
		SendString(buf5);
	//	ES=0;
	//	EA=0; */  
}
void SEND_SIM900()            //中断入口
{
	unsigned char buf5[]={0x1A};
	unsigned char DD[8];
    INT_count++;
	sprintf(DD,"AA%d",INT_count);
	PutStr(0,0,DD);
	INT_count=INT_count%1000;

/*    if(INT_count==INT_TIME[command])
	{

		switch(command)
		{
		  case 0://UATR_INIT();
		  		PutStr(0,0,"AAAA");	
				 break;
		  case 1:SendString("AT+CGCLASS=\"B\"\r\n");
				 break;
		  case 2:SendString("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");
				 break;
		  case 3:SendString("AT+CGATT=1\r\n");
				 break;
		  case 4:SendString("AT+CIPCSGP=1,\"CMNET\"\r\n");
				break;	
		  case 5:SendString("AT+CLPORT=\"TCP\",\"4001\"\r\n");
				break;
		  case 6:SendString("AT+CIPSTART=\"TCP\",\"183.230.40.34\",\"80\"\r\n");
				break;
		  case 7:SendString("AT+CIPSEND\r\n");
				break;
		  case 8:RH_SEND();	
		  		 SendString("POST /devices/548152733/datapoints?type=3 HTTP/1.1\r\n");
				 SendString("api-key:bVAsevzZT4dyobUj27iizubiL9Q=\r\n");
				 SendString("Host:api.heclouds.com\r\n");
       			 SendString("Content-Length:36\r\n\n");
      			 //  SendString("{\"temperature\":11.5,\"humidity\":51.7}\r\n");
	  			 SendString(SEND_HT);//发送温湿度过去
				 break;
		  case 9:SendString(buf5);
		  		break;				
		}
		command++;
		command=command%10;
	} */ 
}


void DelaySec(int sec)
{
	unsigned int i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}
void Delay(uint t)
{
	uint ii;
  	for(ii=t;ii>0;ii--)
    	DelayX10ms(1);	//ori=113
}
void DelayX10us(unsigned char n)		//@11.0592MHz
{
	unsigned char i; 
	do
	{ 
	  _nop_();
	  i = 25;
	  while (--i);
	}while(n--);
}

void DelayXus(unsigned char n)     //@11.0592MHz
{
    while (n--)
    {
        _nop_();
        _nop_();
		_nop_();
    }
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void DelayXms(unsigned char n)
{
   unsigned char i;
   for(i=0;i<n;i++)
      Delay1ms(); 
}	

void DelayX10ms(unsigned char n)		//@11.0592MHz
{
	unsigned char i, j;
  do
   {
	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
   }while(--n);
}
