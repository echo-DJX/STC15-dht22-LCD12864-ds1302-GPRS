//===============================头文件调用===========================//
#include "bsp.h"

char xdata lcdstr[32];

//uint xdata hour,min,sec;
//uint xdata year,month,day;

//====================================================================//
//	语法格式：	void Temperature_Display(uint temp_value)
//	实现功能：	在LCD上显示“温度”
//	参数：		uint temp_value
//	返回值：	无
//====================================================================//

//====================================================================//
//	语法格式：	void Data_Display(void)	
//	实现功能：	在LCD上显示“日期”
//	参数：		无
//	返回值：	无
//====================================================================//
void Date_Display(unsigned char row,unsigned char col)			
{
	uchar tmp;
	uchar  high,low;
	uint year1,month1,day1;
//	uchar str[]="DS16(10,100,'日期：2015-01-01',12);\r\n";

	tmp=timenow[6];					//取出年
//	tmp=0x15;
	low=tmp&0x0f;				 
	high=(tmp&0xf0)>>4;
	year1=(uint)high*10+low;	
	if (year1<100)
	   {year=year1;
	   }		

	tmp=timenow[4];					//取出月
//	tmp=0x02;
	low=tmp&0x0f;				
	high=(tmp&0xf0)>>4;	
	month1=(uint)high*10+low;
	if (month1<13)
	   {month=month1;
	   }		

	tmp=timenow[3];					//取出日
//	tmp=0x23;								
	low=tmp&0x0f;				
	high=(tmp&0xf0)>>4;		
    day1=(uint)high*10+low;
	if (day1<32)
	   {day=day1;
	   }	
	sprintf(lcdstr,"日期：20%02d-%02d-%02d",year,month,day); 
    PutStr(row,col,lcdstr);
    Delay1ms();
}

//====================================================================//
//	语法格式：	void Time_Display(void)	
//	实现功能：	在LCD上显示“时间”
//	参数：		无
//	返回值：	无
//====================================================================//
void Time_Display(unsigned char row,unsigned char col)			
{
	uchar tmp;
	uint  high,low;
	uint hour1,min1,sec1;

       tmp=timenow[2];					//取出时
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;			
       hour1=high*10+low;
	   if (hour1<24)
	   {hour=hour1;
	   }

	   tmp=timenow[1];					//取出分							
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;			
	   min1=high*10+low;
	   if (min1<60)
	   {min=min1;
	   }

	   tmp=timenow[0];				    //取出秒
//	   tmp=0x49;
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;		
	   sec1=high*10+low;
	   if (sec1<60)
	   {sec=sec1;
	   }

     sprintf(lcdstr,"时间：%02d:%02d:%02d",hour,min,sec);
	 PutStr(row,col,lcdstr);
	 Delay1ms();
		 
}
void wendu_Display(unsigned char row,unsigned char col)
{  
     uint tmp,tmp1,tmp2;
	 if(RH_DATA[2]<128)
	 {
	   tmp=RH_DATA[2]*256+RH_DATA[3];
	   tmp1=tmp/10;
	   tmp2=tmp%10;
	   sprintf(lcdstr,"温度：%2d.%1dC",tmp1,tmp2);
	   PutStr(row,col,lcdstr);
	 }
	 else
	 {
	   tmp=(RH_DATA[2]-128)*256+RH_DATA[3];
	   tmp1=tmp/10;
	   tmp2=tmp%10;
	   sprintf(lcdstr,"温度：-%2d.%1dC",tmp1,tmp2);
	   PutStr(row,col,lcdstr);
	 }
	 Delay1ms();
}
void shidu_Display(unsigned char row,unsigned char col)
{  	 
     uint tmp,tmp1,tmp2;
	 tmp=RH_DATA[0]*256+RH_DATA[1];
	 tmp1=tmp/10;
	 tmp2=tmp%10;
     sprintf(lcdstr,"湿度：%2d.%1d%%",tmp1,tmp2);
	 PutStr(row,col,lcdstr);
	 Delay1ms();
}

void RH_Display(unsigned char row,unsigned char col)
{  
     uint  tmp,tmp1,tmp2,tmp3,tmp4;
  	 tmp=RH_DATA[0]*256+RH_DATA[1];
	 tmp1=tmp/10;
	 tmp2=tmp%10;
	 if(RH_DATA[2]<128)
	 {
	   tmp=RH_DATA[2]*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(lcdstr,"H=%2d.%1d%% T=%2d.%1dC",tmp1,tmp2,tmp3,tmp4);
	   PutStr(row,col,lcdstr);
	 }
	 else
	 {
	   tmp=(RH_DATA[2]-128)*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(lcdstr,"H=%2d.%1d%% T=-%2d.%1dC",tmp1,tmp2,tmp3,tmp4);
	   PutStr(row,col,lcdstr);
	 }
	 Delay1ms();
}
