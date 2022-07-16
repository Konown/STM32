#include "hmi.h"

u8 mode=0,Sv1,Sv2,Sv3,Sv4;
void HMI_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 hmi_mode[4];	//存取数据
	static u8 hmi_mode1_date[4];
	static u8 hmi_mode2_date[7];
	static u8 state = 0;	
	static u8 bit_number=0,i;	
	if(state==0&& (data==0x0a||data==0x01) )
	{
		state=1;
		hmi_mode[bit_number++]=data;
	}
	else if(state==1&& (data==0x0b||data==0x0a))
	{
		state=2;
		hmi_mode[bit_number++]=data;
	}
	else if(state==2)
	{
		
		if(hmi_mode[0]==0x0a && hmi_mode[1]==0x0b)	//模式1
		{
			hmi_mode1_date[bit_number++]=data;
			if(bit_number>=3)
			{
				state=3;
			}
		}
		else if(hmi_mode[0]==0x01 && hmi_mode[1]==0x0a)	//模式2
		{
			hmi_mode2_date[bit_number++]=data;
			if(bit_number>=6)
			{
				state=3;
			}
		}
		
	}
	else if(state==3)		//检测是否接受到结束标志
	{
		if(hmi_mode[0]==0x0a && hmi_mode[1]==0x0b)	//模式1
		{
			if(data == 0x0c)
			{
				state = 0;
				hmi_mode1_date[bit_number++]=data;
				mode=hmi_mode1_date[2]%16;
				bit_number=0;
			}
			else if(data != 0x0b)
			{
				state = 0;
				bit_number=0;
				for(i=0;i<4;i++)
				{
					hmi_mode1_date[i]=0x00;
				}           
			}
		}
		else if(hmi_mode[0]==0x01 && hmi_mode[1]==0x0a)	//模式2
		{
			if(data == 0x0c)
			{
				state = 0;
				hmi_mode2_date[bit_number++]=data;
				Sv1=hmi_mode2_date[2]%16;
				Sv2=hmi_mode2_date[3]%16;
				Sv3=hmi_mode2_date[4]%16;
				Sv4=hmi_mode2_date[5]%16;
				bit_number=0;
			}
			else if(data != 0x0c)
			{
				state = 0;
				bit_number=0;
				for(i=0;i<7;i++)
				{
					hmi_mode2_date[i]=0x00;
				}           
			}
		}
		
	}    
	else
	{
		state = 0;
		bit_number=0;
		for(i=0;i<4;i++)
		{
			hmi_mode[i]=0x00;
		}
		for(i=0;i<4;i++)
		{
			hmi_mode1_date[i]=0x00;
		}
		for(i=0;i<7;i++)
		{
			hmi_mode2_date[i]=0x00;
		}
	}
}


