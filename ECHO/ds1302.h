#ifndef	_DS1302_H
#define _DS1302_H
#include "bsp.h"

extern char timenow[7];	    //����ȫ�ֱ���

//===========================DS1302������Ŷ���================================//
sbit T_RST=P2^5;            	//ʵʱʱ�Ӹ�λ������
sbit T_IO =P2^6;                //ʵʱʱ������������
sbit T_CLK=P2^7; 			    //ʵʱʱ��ʱ��������

//=================================��������===================================//
 void DS1302_WriteByte(unsigned char ucDa);			 //��DS1302д��1Byte���ݺ���
 unsigned char DS1302_ReadByte(void) ;					 //��DS1302��ȡ1Byte���ݺ���
 void DS1302_W1302(unsigned char ucAddr, unsigned char ucDa);	 //��DS1302ָ����ַд�����ݺ���
extern unsigned char DS1302_R1302(unsigned char ucAddr);			 //��ȡDS1302��ַ������
extern void  DS1302_Set1302(unsigned char *pSecDa);			 //����DS1302��ʼʱ��
extern void  DS1302_DA_TI(void);			 //��ȡDS1302��ǰʱ��
extern void DS1302_Initial(void);               //DS1302��ʼ�� 
void get_DATA();
void get_TIME();
extern char xdata SHOW_TI[];
extern char xdata SHOW_DA[];
extern unsigned int xdata hour,min,sec;
extern unsigned int xdata year,month,day;
#endif