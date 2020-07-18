#include "bsp.h"

extern unsigned char  RH_DATA[];

void Delay10us(void)		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}


u8  DHT11_COM(void)
 {
     u8 i;
    u8  U8temp,U8comdata;
        U8comdata=0;
       for(i=0;i<8;i++)	   
	    {
	   	while(!DHT11_DAT);
		     Delay10us();
		       Delay10us();
		       Delay10us();
		       Delay10us();      //��ʱ40us������
	  		U8temp=0;
	        if(DHT11_DAT) U8temp=1;
		while(DHT11_DAT);
	   	
		   U8comdata<<=1;
	   	   U8comdata+=U8temp;        //0
	     }//rof
	return  U8comdata;
}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== U8T_data_H------
	//----�¶ȵ�8λ== U8T_data_L------
	//----ʪ�ȸ�8λ== U8RH_data_H-----
	//----ʪ�ȵ�8λ== U8RH_data_L-----
	//----У�� 8λ == U8checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay10us();,DHT11_COM(); 
	//--------------------------------
u8 check(void)
{ u8  FLAG;
          FLAG=2;
	 while((!DHT11_DAT)&&(FLAG++));
	  if(FLAG==1)
	       return 0;
	  else
	  {   FLAG=2; 
	       while((DHT11_DAT)&&(FLAG++));
	       if(FLAG==1)
	             return 0;
	       else
		     return 1;
	  }
}
void RH_SEND(void)
{
	u8  U8temp1;
   	uint  tmp,tmp1,tmp2,tmp3,tmp4;   
   u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;	  
 //��������18ms���� 
            DHT11_DAT=1;
           Delay10us();
           DHT11_DAT=0;
	   DelayXms(20);
	  DHT11_DAT=1;
	 //������������������ ������ʱ20us-40us
	   Delay10us();
           Delay10us();
           Delay10us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
      if(check()==1)
      {  
	 //���ݽ���״̬		 
	   U8RH_data_H_temp=DHT11_COM();
	   U8RH_data_L_temp=DHT11_COM();
	   U8T_data_H_temp=DHT11_COM();
	   U8T_data_L_temp=DHT11_COM();
	   U8checkdata_temp=DHT11_COM();
	   DHT11_DAT=1;
	 //����У�� 
	 
	  U8temp1=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	  if(U8temp1==U8checkdata_temp)
	  {
	   	  RH_DATA[0]=U8RH_data_H_temp;    //ʪ������
	   	  RH_DATA[1]=U8RH_data_L_temp;    //ʪ��С��
		  RH_DATA[2]=U8T_data_H_temp;      //�¶�����
	   	  RH_DATA[3]=U8T_data_L_temp;      //�¶�С��
	   	  RH_DATA[4]=U8checkdata_temp;    //У����
	  }
       }  
       else
	{
	          PutStr(2,0,"DHT22����Ӧ");
	 }

  	 tmp=RH_DATA[0]*256+RH_DATA[1];
	 tmp1=tmp/10;
	 tmp2=tmp%10;
	 if(RH_DATA[2]<128)
	 {
	   tmp=RH_DATA[2]*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(SEND_HT,"{\"temperature\":%2d.%1d%,\"humidity\":%2d.%1d}\r\n",tmp3,tmp4,tmp1,tmp2);
	 }				   
	 else
	 {
	   tmp=(RH_DATA[2]-128)*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(SEND_HT,"{\"humidity\":%2d.%1d%,\"temperature\":-%2d.%1d}\r\n",tmp1,tmp2,tmp3,tmp4);	
	 }
	 Delay1ms();
}
void RH(void)
{
   u8  U8temp1;
   	uint  tmp,tmp1,tmp2,tmp3,tmp4;   
   u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;	  
 //��������18ms���� 
            DHT11_DAT=1;
           Delay10us();
           DHT11_DAT=0;
	   DelayXms(20);
	  DHT11_DAT=1;
	 //������������������ ������ʱ20us-40us
	   Delay10us();
           Delay10us();
           Delay10us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
      if(check()==1)
      {  
	 //���ݽ���״̬		 
	   U8RH_data_H_temp=DHT11_COM();
	   U8RH_data_L_temp=DHT11_COM();
	   U8T_data_H_temp=DHT11_COM();
	   U8T_data_L_temp=DHT11_COM();
	   U8checkdata_temp=DHT11_COM();
	   DHT11_DAT=1;
	 //����У�� 
	 
	  U8temp1=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	  if(U8temp1==U8checkdata_temp)
	  {
	   	  RH_DATA[0]=U8RH_data_H_temp;    //ʪ������
	   	  RH_DATA[1]=U8RH_data_L_temp;    //ʪ��С��
		  RH_DATA[2]=U8T_data_H_temp;      //�¶�����
	   	  RH_DATA[3]=U8T_data_L_temp;      //�¶�С��
	   	  RH_DATA[4]=U8checkdata_temp;    //У����
	  }
       }  
       else
	{
	        //  PutStr(2,0,"DHT22����Ӧ");
	 }

  	 tmp=RH_DATA[0]*256+RH_DATA[1];
	 tmp1=tmp/10;
	 tmp2=tmp%10;
	 if(RH_DATA[2]<128)
	 {
	   tmp=RH_DATA[2]*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(SHOW_HT,"H=%2d.%1d%% T=%2d.%1dC",tmp1,tmp2,tmp3,tmp4);
	 }				   
	 else
	 {
	   tmp=(RH_DATA[2]-128)*256+RH_DATA[3];
	   tmp3=tmp/10;
	   tmp4=tmp%10;
	   sprintf(SHOW_HT,"H=%2d.%1d% T=-%2d.%1d",tmp1,tmp2,tmp3,tmp4);
	 }
	 Delay1ms();
}