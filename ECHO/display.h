#ifndef	_DISPLAY_H
#define _DISPLAY_H
#include "bsp.h"


//=================================��������===================================//
void RH_Display(unsigned char row,unsigned char col);    
void wendu_Display(unsigned char row,unsigned char col);	
void shidu_Display(unsigned char row,unsigned char col);	
void Time_Display(unsigned char row,unsigned char col);						  //��LCD����ʾ��ʱ�䡱����
void Date_Display(unsigned char row,unsigned char col);	
extern char xdata lcdstr[32];

#endif