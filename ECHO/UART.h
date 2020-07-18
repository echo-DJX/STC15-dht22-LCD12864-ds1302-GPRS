#ifndef	_UART_H
#define _UART_H
#include "bsp.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L          //ϵͳƵ��
#define BAUD 9600             //���ڲ�����

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

#define PARITYBIT EVEN_PARITY   //����У��λ


#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

extern bit busy;

void SendData(BYTE dat);
extern void SendString(char *s);
extern void UATR_INIT(void);


#endif