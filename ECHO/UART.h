#ifndef	_UART_H
#define _UART_H
#include "bsp.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L          //系统频率
#define BAUD 9600             //串口波特率

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

#define PARITYBIT EVEN_PARITY   //定义校验位


#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

extern bit busy;

void SendData(BYTE dat);
extern void SendString(char *s);
extern void UATR_INIT(void);


#endif