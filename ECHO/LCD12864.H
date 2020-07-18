#ifndef 	_LCD12864_h_
#define 	_LCD12864_h_
/**************************************************************
               iO口宏定义区
***************************************************************/
#include "bsp.h"
sbit CS =P0^0;//RS
sbit SID=P0^1;//RW
sbit SCK=P0^2;//E
sbit PSB=P0^3;//并串方式选择：1--并口，2--串口


 void WriteCommand( unsigned char Cbyte );
 void WriteData( unsigned char Dbyte );
extern void LcmInit( void );
extern void LcmClearTXT( void );
//extern void LcmClearBMP( void );

extern void PutStr(unsigned char row,unsigned char col,unsigned char *puts);
//extern void PutNum(unsigned char row,unsigned char col,unsigned int num);
void LineClear(unsigned char row);
#endif