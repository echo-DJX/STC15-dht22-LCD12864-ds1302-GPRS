
#include"bsp.h"
unsigned char buf5[]={0x1A};
/*----------------------------
UART 中断服务程序
-----------------------------*/
void UATR_INIT()
{
	  P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;

    ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
    

#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif

    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    TH1 = (65536 - (FOSC/4/BAUD))>>8;
    TR1 = 1;                    //定时器1开始启动
    ES = 1;                     //使能串口中断
    EA = 1;
	
    

}
void Uart() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;                 //清除RI位
        P0 = SBUF;              //P0显示串口数据
        P22 = RB8;              //P2.2显示校验位
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
    }
	 
}

/*----------------------------
发送串口数据
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;                //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;                //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;                //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;                //设置校验位为0
#endif
    }
    busy = 1;
    SBUF = ACC;                 //写数据到UART数据寄存器
}

/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}

