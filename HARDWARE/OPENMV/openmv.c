#include "openmv.h"
#include "pid.h"

u16 x,y,x_1=0,y_1=0;

void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 openmv[5];	//存取数据
	static u8 state = 0;	
	static u8 bit_number=0,i;	
	
	if(state==0&&data==0x2C)
	{
		state=1;
		openmv[bit_number++]=data;
	}
	else if(state==1&&data==0x18)
	{
		state=2;
		openmv[bit_number++]=data;
	}
	else if(state==2)
	{
		openmv[bit_number++]=data;
		if(bit_number>=4)
		{
			state=3;
		}
	}
	else if(state==3)		//检测是否接受到结束标志
	{
		if(data == 0x5B)
		{
			state = 0;
			openmv[bit_number++]=data;
			x=openmv[2];
			y=openmv[3];
			x_1=x;
			y_1=y;
			bit_number=0;
		}
		else if(data != 0x5B)
		{
			state = 0;
			bit_number=0;
			for(i=0;i<5;i++)
			{
				openmv[i]=0x00;
			}           
		}
	}    
	else
	{
		state = 0;
		bit_number=0;
		for(i=0;i<5;i++)
		{
			openmv[i]=0x00;
		}
	}
}
