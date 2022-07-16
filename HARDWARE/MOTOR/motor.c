#include "motor.h"
#include "pid.h"
#include "systick.h"
#include "encoder.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

void go(void)
{
	IN1=0 ;
	IN2=1 ;
}

void stop(void)
{
	IN1=0;
	IN2=0;
}

void back(void)
{
	IN1=1;
	IN2=0;
}

void Stby_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);
}


//电机调速和方向控制
void motor(float pwm)
{
	pwm=limit(pwm);
	if(pwm>0||pwm==0)	
		{
		  go();
			TIM_SetCompare4(TIM2,pwm);	
		}
		if(pwm<0)
		{
			back();
			TIM_SetCompare4(TIM2,-pwm);	
		}
}

float limit(float pwm)
{
	if(pwm>4999)  pwm=4799;
	if(pwm<-4999) pwm=-4799;
 	if((pwm<550&&pwm>0)||(pwm<0&&pwm>-550)) 
	{
		if(pwm<0) pwm=-550;
		if(pwm>0) pwm=550;
 	}
	return pwm;
}


