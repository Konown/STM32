#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "sys.h"

#define TICK_PER_SECOND	1000
#define TICK_US	(1000000/TICK_PER_SECOND)

typedef struct
{
	u8 init_flag;
	u32 old;
	u32 now;
	u32 dT;

}	_get_dT_st;

extern  RCC_ClocksTypeDef  rcc_clocks;
extern  u32 systime_ms;

void  SysTick_Configuration ( void );
uint32_t GetSysTime_us ( void );
u32 SysTick_GetTick(void);

void delay_us ( uint32_t us );
void delay_ms ( uint32_t ms );

typedef struct
{
	void(*task_func)(void);
	uint16_t rate_hz;
	uint16_t interval_ticks;
	uint32_t last_run;
}sched_task_t;

void Scheduler_Setup(void);
void Scheduler_Run(void);

#endif


