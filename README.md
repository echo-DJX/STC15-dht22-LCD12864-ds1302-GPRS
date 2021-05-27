# STC15-dht22-LCD12864-ds1302-sim900a

LCD显示dht22温湿度数据和ds1302的时间，通过sim900a将数据通过tcp透传至onenet，通过折线图查看一天的温湿度变化，一个简单的温湿度监控的课设项目

bsp.c系统初始化函数
dht22.c dht22的驱动
display.c 显示屏LCD12864函数
ds1302.c  ds1302的驱动函数
UART.c  通过串口驱动sim900a与onenet进行tcp通信 将温湿度数据上传。

展示：

![contents](https://github.com/echo-DJX/STC15-dht22-LCD12864-ds1302-sim900a/tree/master/img/img\2 (1).jpg)
![contents](https://github.com/echo-DJX/STC15-dht22-LCD12864-ds1302-sim900a/tree/master/img/img\2 (2).jpg)





