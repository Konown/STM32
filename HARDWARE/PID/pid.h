#ifndef __PID_H
#define __PID_H

#include "sys.h"

typedef struct
{
	float Sv;	//用户设定值
	float Pv;
	
	float Kp;
	float T;	//pid计算周期--采样周期
	float Ki;
	float Kd;
	
	float Ek;	//本次偏差
	float Ek_1;	//上次偏差
	float Ek_2;	//上上次偏差
	float SEk;	//历史偏差之和
	
	float OUT0;
	
	float OUT;
	
	float currentpwm;
	
	u16 Count_ms;
	
	s32 PwmCycle;	//pwm周期
	
}PID;

extern PID pid;

void pid_Init(void);

void pid_Calc(void);


#endif
