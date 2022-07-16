#ifndef __EXTI_H
#define __EXTI_H
#include "sys.h"

extern u32 Alarm_Distance1;
extern u32 Alarm_Distance2;

void EXTIX_Init(void);

void EXTI15_10_IRQHandler(void);

#endif
