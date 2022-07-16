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
	//��װ����HCLKƽ�ʳ���1000=72k��
	SysTick_Config ( cnts );
	SysTick_CLKSourceConfig ( SysTick_CLKSource_HCLK );
	//�ж�ʱ����1ms
}
void sys_time()
{
	systime_ms++;
}
//�δ�ʱ���ж�
//д����жϺ�����ʱ��Ҫ��stm32f1xx_it.c����ĸ��жϷ�������ע����
//ÿһms����һ���ж�
void SysTick_Handler(void)
{
	sysTickUptime++;
	sys_time();
}

//��ȡʱ��
u32 SysTick_GetTick(void)
{
	return systime_ms;
}
//��ȡʱ�� ��us�ĵ�λ��
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

//us��ʱ
void delay_us ( uint32_t us )
{
	uint32_t now = GetSysTime_us();
	while ( GetSysTime_us() - now < us );
}
//ms��ʱ
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
	//��ʼ�������
	for(index=0;index < TASK_NUM;index++)
	{
		//����ÿ���������ʱ������
		//��Ƶ��ת�������ڣ���λ��ms
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz;
		//�������Ϊ1��Ҳ����1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}
//��������ŵ�main������while(1)�У���ͣ�ж��Ƿ����߳�Ӧ��ִ��
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��
	for(index=0;index < TASK_NUM;index++)
	{
		//��ȡϵͳ��ǰʱ�䣬��λMS
		uint32_t tnow = SysTick_GetTick();
		//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			//�����̵߳�ִ��ʱ�䣬������һ���ж�
			sched_tasks[index].last_run = tnow;
			//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
			sched_tasks[index].task_func();
		}	 
	}
}


