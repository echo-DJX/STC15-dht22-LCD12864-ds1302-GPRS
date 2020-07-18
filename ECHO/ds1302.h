#ifndef	_DS1302_H
#define _DS1302_H
#include "bsp.h"

extern char timenow[7];	    //定义全局变量

//===========================DS1302相关引脚定义================================//
sbit T_RST=P2^5;            	//实时时钟复位线引脚
sbit T_IO =P2^6;                //实时时钟数据线引脚
sbit T_CLK=P2^7; 			    //实时时钟时钟线引脚

//=================================函数声明===================================//
 void DS1302_WriteByte(unsigned char ucDa);			 //往DS1302写入1Byte数据函数
 unsigned char DS1302_ReadByte(void) ;					 //从DS1302读取1Byte数据函数
 void DS1302_W1302(unsigned char ucAddr, unsigned char ucDa);	 //往DS1302指定地址写入数据函数
extern unsigned char DS1302_R1302(unsigned char ucAddr);			 //读取DS1302地址的数据
extern void  DS1302_Set1302(unsigned char *pSecDa);			 //设置DS1302初始时间
extern void  DS1302_DA_TI(void);			 //读取DS1302当前时间
extern void DS1302_Initial(void);               //DS1302初始化 
void get_DATA();
void get_TIME();
extern char xdata SHOW_TI[];
extern char xdata SHOW_DA[];
extern unsigned int xdata hour,min,sec;
extern unsigned int xdata year,month,day;
#endif