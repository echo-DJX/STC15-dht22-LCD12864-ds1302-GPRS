//===============================头文件调用===========================//
#include "bsp.h"
uint xdata hour,min,sec;
uint xdata year,month,day;
//char idata timenow[7]={0x00,0x00,0x12,0x01,0x06,0x03,0x10};//"秒-分-时-日-月-星期-年"寄存器初始值
char timenow[7];
//uint xdata hour,min,sec;
//uint xdata year,month,day;
//==================实时时钟模块 时钟芯片型号：DS1302==================//
//=====================================================================//
//	语法格式：	void DS1302_WriteByte(uchar ucDa)
//	实现功能：	往DS1302写入1Byte数据
//	参数：		uchar ucDa——写入的数据
//	返回值：	无
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
//	语法格式：	uchar DS1302_ReadByte(void) 
//	实现功能：	从DS1302读取1Byte数据
//	参数：		无
//	返回值：	uchar temp
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
//	语法格式：	void DS1302_W1302(uchar ucAddr, uchar ucDa) 
//	实现功能：	往DS1302写入数据（先写地址，后写命令/数据）
//	参数：		uchar ucAddr——DS1302地址，ucDa——要写的数据
//	返回值：	无
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
//	语法格式：	uchar DS1302_R1302(uchar ucAddr) 
//	实现功能：	读取DS1302地址的数据（先写地址，后读命令/数据）
//	参数：		uchar ucAddr——DS1302地址
//	返回值：	uchar ucDa
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
//	语法格式：	void DS1302_Set1302(uchar *pSecDa) 
//	实现功能：	设置DS1302初始时间 
//	参数：		uchar pSecDa——初始时间地址
//	返回值：	无
//=====================================================================//
void DS1302_Set1302(uchar *pSecDa)
{
	uchar i;
	uchar ucAddr=0x80; 
	DS1302_W1302(0x8e,0x00);  //写允许
	for(i=7;i>0;i--)
	{ 
		DS1302_W1302(ucAddr,*pSecDa); 
		pSecDa++;
		ucAddr+=2;
	}
	DS1302_W1302(0x8e,0x80); 
}

//=====================================================================//
//	语法格式：	void DS1302_Get1302(uchar ucCurtime[]) 
//	实现功能：	读取DS1302当前时间
//	参数：		uchar ucCurtime——保存当前时间地址
//	返回值：	无
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
	sprintf(SHOW_DA,"日期20%02d-%02d-%02d",year,month,day); 
	PutStr(1,0,SHOW_DA);		    
    Delay1ms();
}
void	get_TIME()
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

     sprintf(SHOW_TI,"时间%02d:%02d:%02d",hour,min,sec);
	  PutStr(2,0,SHOW_TI);
	 Delay1ms();
		 
}
void DS1302_Initial()
{
    T_RST = 0;
    T_CLK = 0;
    DS1302_W1302(0x8e, 0x00);   //允许写操作
    DS1302_W1302(0x80, 0x00);   //时钟启动
    DS1302_W1302(0x90, 0x00);   //一个二极管＋4K电阻充电
    DS1302_W1302(0x8e, 0x80);   //写保护
}