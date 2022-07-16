#include "exti.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "pid.h"


void EXTIX_Init(void)
{
	
	EXTI_InitTypeDef EXTI_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	KEY_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//KEY4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);//PC7
	
	EXTI_InitStrue.EXTI_Line = EXTI_Line7;
	EXTI_InitStrue.EXTI_LineCmd = ENABLE;
	EXTI_InitStrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStrue);
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStrue);
	
	//KEY5
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);//PC6
	
	EXTI_InitStrue.EXTI_Line = EXTI_Line6;
	EXTI_InitStrue.EXTI_LineCmd = ENABLE;
	EXTI_InitStrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStrue);
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStrue);
	
	//KEY3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//PB15
	
	EXTI_InitStrue.EXTI_Line = EXTI_Line15;
	EXTI_InitStrue.EXTI_LineCmd = ENABLE;
	EXTI_InitStrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStrue);
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStrue);
	
	//KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//PB14
	
	EXTI_InitStrue.EXTI_Line = EXTI_Line14;
	EXTI_InitStrue.EXTI_LineCmd = ENABLE;
	EXTI_InitStrue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStrue);
	
	NVIC_InitStrue.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStrue);
}

void EXTI9_5_IRQHandler(void)
{
	if(KEY4==0)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	else if(KEY5==0)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(KEY2==1)
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	else if(KEY3==1)
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
