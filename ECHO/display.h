#ifndef	_DISPLAY_H
#define _DISPLAY_H
#include "bsp.h"


//=================================函数声明===================================//
void RH_Display(unsigned char row,unsigned char col);    
void wendu_Display(unsigned char row,unsigned char col);	
void shidu_Display(unsigned char row,unsigned char col);	
void Time_Display(unsigned char row,unsigned char col);						  //在LCD上显示“时间”函数
void Date_Display(unsigned char row,unsigned char col);	
extern char xdata lcdstr[32];

#endif