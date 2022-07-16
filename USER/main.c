#include "led.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "key.h"    
#include "timer.h"
#include "encoder.h"
#include "motor.h"
#include "pid.h"
#include "systick.h"
#include "exti.h"
#include "dma_adc.h"

//	PA0-7	DMA的8个ADC1通道
//	PA8-11	TIM1的4个PWM通道

 int main(void)
{	 
	SysTick_Configuration();
	Scheduler_Setup();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	adc_dma_init();
	Usart2_Init(115200);
	while(1)
	{
		Scheduler_Run();
	}
  
}


