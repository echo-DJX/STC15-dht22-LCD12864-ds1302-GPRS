#ifndef BSP_HH
#define BSP_HH
#include <stc15w.h>
#include "string.h"
#include "intrins.h"
#include "stdio.h"
 #include "math.h"
#include "INTRINS.H"
#include"LCD12864.h"
#include"DS1302.h"
#include "DHT22.h"
#include "UART.h"
//#include "reg51.h"
#define uint  unsigned int		//宏定义，用uint代替unsigned int
#define uchar  unsigned char
typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;
#define FOSC 11059200L
#define T38_4KHz (256-18432000/38400/2)         //1T
extern unsigned char  RH_DATA[];  //温湿度数据
extern void BSP_INIT();
extern void DelayX10ms(unsigned char n)	;
extern void DelayXms(unsigned char n);
extern void Delay1ms();
extern void DelayXus(unsigned char n) ;
extern void DelayX10us(unsigned char n);
extern void Delay(uint t);
extern unsigned char  RH_DATA[5]={0x00,0x00,0x00,0x00,0x00};  //温湿度数据
extern char xdata SHOW_HT[60]; //温湿度显示
extern char xdata SEND_HT[60]; //温湿度发送数据
void DelaySec(int sec);
                        //秒    分    时    日    月  星期    年
extern unsigned char command;
extern unsigned int INT_count;
extern unsigned long TIN3_LONG;
extern void SEND_SIM900(void);



#endif