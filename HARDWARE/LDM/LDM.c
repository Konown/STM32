#include "ldm.h"

float distance_LDM;

void Ldm_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 ldm[8];	//存取数据
	static u8 state = 0;	
	static u8 bit_number=0,i;	
	
	if(state==0&&data==0xB4)
	{
		state=1;
		ldm[bit_number++]=data;
	}
	else if(state==1&&data==0x69)
	{
		state=2;
		ldm[bit_number++]=data;
	}
	else if(state==2&&data==0x04)
	{
		state=3;
		ldm[bit_number++]=data;
	}
	else if(state==3)
	{
		ldm[bit_number++]=data;
		if(bit_number>=7)
		{
			state=4;
		}
	}
	else if(state==4)		//检测是否接受到结束标志
	{
		ldm[bit_number++]=data;
		distance_LDM=ldm[5]*256+ldm[6];
	}    
	else
	{
		state = 0;
		bit_number=0;
		for(i=0;i<8;i++)
		{
			ldm[i]=0x00;
		}
	}
}


