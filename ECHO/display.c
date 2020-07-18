//===============================ͷ�ļ�����===========================//
#include "bsp.h"

char xdata lcdstr[32];

//uint xdata hour,min,sec;
//uint xdata year,month,day;

//====================================================================//
//	�﷨��ʽ��	void Temperature_Display(uint temp_value)
//	ʵ�ֹ��ܣ�	��LCD����ʾ���¶ȡ�
//	������		uint temp_value
//	����ֵ��	��
//====================================================================//

//====================================================================//
//	�﷨��ʽ��	void Data_Display(void)	
//	ʵ�ֹ��ܣ�	��LCD����ʾ�����ڡ�
//	������		��
//	����ֵ��	��
//====================================================================//
void Date_Display(unsigned char row,unsigned char col)			
{
	uchar tmp;
	uchar  high,low;
	uint year1,month1,day1;
//	uchar str[]="DS16(10,100,'���ڣ�2015-01-01',12);\r\n";

	tmp=timenow[6];					//ȡ����
//	tmp=0x15;
	low=tmp&0x0f;				 
	high=(tmp&0xf0)>>4;
	year1=(uint)high*10+low;	
	if (year1<100)
	   {year=year1;
	   }		

	tmp=timenow[4];					//ȡ����
//	tmp=0x02;
	low=tmp&0x0f;				
	high=(tmp&0xf0)>>4;	
	month1=(uint)high*10+low;
	if (month1<13)
	   {month=month1;
	   }		

	tmp=timenow[3];					//ȡ����
//	tmp=0x23;								
	low=tmp&0x0f;				
	high=(tmp&0xf0)>>4;		
    day1=(uint)high*10+low;
	if (day1<32)
	   {day=day1;
	   }	
	sprintf(lcdstr,"���ڣ�20%02d-%02d-%02d",year,month,day); 
    PutStr(row,col,lcdstr);
    Delay1ms();
}

//====================================================================//
//	�﷨��ʽ��	void Time_Display(void)	
//	ʵ�ֹ��ܣ�	��LCD����ʾ��ʱ�䡱
//	������		��
//	����ֵ��	��
//====================================================================//
void Time_Display(unsigned char row,unsigned char col)			
{
	uchar tmp;
	uint  high,low;
	uint hour1,min1,sec1;

       tmp=timenow[2];					//ȡ��ʱ
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;			
       hour1=high*10+low;
	   if (hour1<24)
	   {hour=hour1;
	   }

	   tmp=timenow[1];					//ȡ����							
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;			
	   min1=high*10+low;
	   if (min1<60)
	   {min=min1;
	   }

	   tmp=timenow[0];				    //ȡ����
//	   tmp=0x49;
	   low=tmp&0x0f;				
	   high=(tmp&0xf0)>>4;		
	   sec1=high*10+low;
	   if (sec1<60)
	   {sec=sec1;
	   }

     sprintf(lcdstr,"ʱ�䣺%02d:%02d:%02d",hour,min,sec);
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
	   sprintf(lcdstr,"�¶ȣ�%2d.%1dC",tmp1,tmp2);
	   PutStr(row,col,lcdstr);
	 }
	 else
	 {
	   tmp=(RH_DATA[2]-128)*256+RH_DATA[3];
	   tmp1=tmp/10;
	   tmp2=tmp%10;
	   sprintf(lcdstr,"�¶ȣ�-%2d.%1dC",tmp1,tmp2);
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
     sprintf(lcdstr,"ʪ�ȣ�%2d.%1d%%",tmp1,tmp2);
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
