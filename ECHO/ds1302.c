//===============================ͷ�ļ�����===========================//
#include "bsp.h"
uint xdata hour,min,sec;
uint xdata year,month,day;
//char idata timenow[7]={0x00,0x00,0x12,0x01,0x06,0x03,0x10};//"��-��-ʱ-��-��-����-��"�Ĵ�����ʼֵ
char timenow[7];
//uint xdata hour,min,sec;
//uint xdata year,month,day;
//==================ʵʱʱ��ģ�� ʱ��оƬ�ͺţ�DS1302==================//
//=====================================================================//
//	�﷨��ʽ��	void DS1302_WriteByte(uchar ucDa)
//	ʵ�ֹ��ܣ�	��DS1302д��1Byte����
//	������		uchar ucDa����д�������
//	����ֵ��	��
//=====================================================================//
void DS1302_WriteByte(uchar ucDa) 		
{ 
	uchar i,temp;
	temp=ucDa; 
	for(i=0;i<8;i++)
	{
		T_CLK=0;
		DelayXus(2);
		temp>>=1;
		T_IO=CY;
		_nop_();
		T_CLK=1;
		DelayXus(2);
	} 
}

//=====================================================================//
//	�﷨��ʽ��	uchar DS1302_ReadByte(void) 
//	ʵ�ֹ��ܣ�	��DS1302��ȡ1Byte����
//	������		��
//	����ֵ��	uchar temp
//=====================================================================//
uchar DS1302_ReadByte(void) 
{ 
	uchar i,temp;
	temp=0;
	for(i=0;i<8;i++)
	{
		T_CLK=0;
		DelayXus(2);
		temp>>=1;
		if(T_IO)
		   temp|=0x80;
		T_CLK=1;
		DelayXus(2);
	} 
	return(temp); 
}

//=====================================================================//
//	�﷨��ʽ��	void DS1302_W1302(uchar ucAddr, uchar ucDa) 
//	ʵ�ֹ��ܣ�	��DS1302д�����ݣ���д��ַ����д����/���ݣ�
//	������		uchar ucAddr����DS1302��ַ��ucDa����Ҫд������
//	����ֵ��	��
//=====================================================================//
void DS1302_W1302(uchar ucAddr, uchar ucDa)
{
	T_RST=0;
	DelayXus(1);
	T_CLK=0;
	DelayXus(1);
	T_RST=1;
	DelayXus(2);
	DS1302_WriteByte(ucAddr); 
	DS1302_WriteByte(ucDa); 
	T_CLK=1;
	DelayXus(1);
	T_RST=0;
	DelayXus(1);
} 

//=====================================================================//
//	�﷨��ʽ��	uchar DS1302_R1302(uchar ucAddr) 
//	ʵ�ֹ��ܣ�	��ȡDS1302��ַ�����ݣ���д��ַ���������/���ݣ�
//	������		uchar ucAddr����DS1302��ַ
//	����ֵ��	uchar ucDa
//=====================================================================//
uchar DS1302_R1302(uchar ucAddr)
{
	uchar ucDa;
	T_RST = 0;
	DelayXus(1);
	T_CLK = 0;
	DelayXus(1);
	T_RST = 1;
	DelayXus(2);
	DS1302_WriteByte(ucAddr); 
	ucDa = DS1302_ReadByte(); 
	T_CLK = 1;
	DelayXus(1);
	T_RST =0;
	DelayXus(1);
	return(ucDa);
}

//=====================================================================//
//	�﷨��ʽ��	void DS1302_Set1302(uchar *pSecDa) 
//	ʵ�ֹ��ܣ�	����DS1302��ʼʱ�� 
//	������		uchar pSecDa������ʼʱ���ַ
//	����ֵ��	��
//=====================================================================//
void DS1302_Set1302(uchar *pSecDa)
{
	uchar i;
	uchar ucAddr=0x80; 
	DS1302_W1302(0x8e,0x00);  //д����
	for(i=7;i>0;i--)
	{ 
		DS1302_W1302(ucAddr,*pSecDa); 
		pSecDa++;
		ucAddr+=2;
	}
	DS1302_W1302(0x8e,0x80); 
}

//=====================================================================//
//	�﷨��ʽ��	void DS1302_Get1302(uchar ucCurtime[]) 
//	ʵ�ֹ��ܣ�	��ȡDS1302��ǰʱ��
//	������		uchar ucCurtime�������浱ǰʱ���ַ
//	����ֵ��	��
//=====================================================================//
void DS1302_DA_TI(void)
{
	uchar i;
	uchar tmp;
	uchar ucAddr=0x81;		
	for (i=0;i<7;i++)								
	{
		timenow[i]=DS1302_R1302(ucAddr);
		ucAddr+=2;
	}
	get_DATA();
	get_TIME();
} 
void	get_DATA()
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
	sprintf(SHOW_DA,"����20%02d-%02d-%02d",year,month,day); 
	PutStr(1,0,SHOW_DA);		    
    Delay1ms();
}
void	get_TIME()
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

     sprintf(SHOW_TI,"ʱ��%02d:%02d:%02d",hour,min,sec);
	  PutStr(2,0,SHOW_TI);
	 Delay1ms();
		 
}
void DS1302_Initial()
{
    T_RST = 0;
    T_CLK = 0;
    DS1302_W1302(0x8e, 0x00);   //����д����
    DS1302_W1302(0x80, 0x00);   //ʱ������
    DS1302_W1302(0x90, 0x00);   //һ�������ܣ�4K������
    DS1302_W1302(0x8e, 0x80);   //д����
}