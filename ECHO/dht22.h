
#ifndef DHT22_HH
#define DHT22_HH
#include"bsp.h"

sbit DHT11_DAT=P0^4;   // P2^3
void Delay10us(void);
unsigned char  DHT11_COM(void);
extern void RH(void);
unsigned char check(void);
extern void RH_SEND(void);
#endif