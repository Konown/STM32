#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"

#define uint unsigned int
#define TRIG_Send PBout(8)
#define ECHO_Reci PBin(9)

extern u16 ledpwmval;

void CH_SR04_Init(void);  //超声波模块相关配置初始化
float Senor_Using(void);  //测距函数，返回值即为距离

void TIM4_IRQHandler(void);

void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);

void TIM3_Int_Init(u16 arr,u16 psc);


#endif
