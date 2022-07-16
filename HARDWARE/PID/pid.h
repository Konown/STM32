#ifndef __PID_H
#define __PID_H

#include "sys.h"

typedef struct
{
	float Sv;	//�û��趨ֵ
	float Pv;
	
	float Kp;
	float T;	//pid��������--��������
	float Ki;
	float Kd;
	
	float Ek;	//����ƫ��
	float Ek_1;	//�ϴ�ƫ��
	float Ek_2;	//���ϴ�ƫ��
	float SEk;	//��ʷƫ��֮��
	
	float OUT0;
	
	float OUT;
	
	float currentpwm;
	
	u16 Count_ms;
	
	s32 PwmCycle;	//pwm����
	
}PID;

extern PID pid;

void pid_Init(void);

void pid_Calc(void);


#endif
