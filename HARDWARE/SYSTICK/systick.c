#include "systick.h"
#include "usart.h"
#include "led.h"
#include "pid.h"
#include "encoder.h"
#include "oled.h"
#include "motor.h"


RCC_ClocksTypeDef rcc_clocks;
u32 systime_ms;
volatile uint32_t sysTickUptime = 0;

void  SysTick_Configuration ( void )
{
	uint32_t cnts;

	RCC_GetClocksFreq ( &rcc_clocks );
  
	cnts = ( uint32_t ) rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts ;
	//重装载是HCLK平率除以1000=72k次
	SysTick_Config ( cnts );
	SysTick_CLKSourceConfig ( SysTick_CLKSource_HCLK );
	//中断时间间隔1ms
}
void sys_time()
{
	systime_ms++;
}
//滴答定时器中断
//写这个中断函数的时候要把stm32f1xx_it.c里面的该中断服务函数给注释了
//每一ms进入一次中断
void SysTick_Handler(void)
{
	sysTickUptime++;
	sys_time();
}

//获取时间
u32 SysTick_GetTick(void)
{
	return systime_ms;
}
//获取时间 （us的单位）
uint32_t GetSysTime_us ( void )
{
  register uint32_t ms;
  u32 value;
	
	do
	{
    ms = sysTickUptime;
    value = ms * TICK_US + ( SysTick->LOAD - SysTick->VAL ) * TICK_US / SysTick->LOAD;
	}while(ms != sysTickUptime);
	
	return value;
}

//us延时
void delay_us ( uint32_t us )
{
	uint32_t now = GetSysTime_us();
	while ( GetSysTime_us() - now < us );
}
//ms延时
void delay_ms ( uint32_t ms )
{
	while ( ms-- )
		delay_us(1000);
}



#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Loop_1000Hz(void)
{
	
}


void Loop_500Hz(void)
{
	
}


void Loop_200Hz(void)
{
	
}

void Loop_100Hz(void)
{
	
}


void Loop_50Hz(void)
{
	
}

void Loop_10Hz(void)
{
	
}

void Loop_2Hz(void)
{
}

void Loop_1Hz(void)
{
	
}

static sched_task_t sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_200Hz , 200,  0, 0},
	{Loop_100Hz , 100,  0, 0},
	{Loop_50Hz  ,  50,  0, 0},
	{Loop_10Hz  ,  10,  0, 0},
	{Loop_2Hz   ,   2,  0, 0},
	{Loop_1Hz   ,   1,  0, 0},
};

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	//初始化任务表
	for(index=0;index < TASK_NUM;index++)
	{
		//计算每个任务的延时周期数
		//把频率转换成周期，单位是ms
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz;
		//最短周期为1，也就是1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}
//这个函数放到main函数的while(1)中，不停判断是否有线程应该执行
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//循环判断所有线程，是否应该执行
	for(index=0;index < TASK_NUM;index++)
	{
		//获取系统当前时间，单位MS
		uint32_t tnow = SysTick_GetTick();
		//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			//更新线程的执行时间，用于下一次判断
			sched_tasks[index].last_run = tnow;
			//执行线程函数，使用的是函数指针
			sched_tasks[index].task_func();
		}	 
	}
}


