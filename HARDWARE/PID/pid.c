#include "pid.h"
#include "motor.h"
#include "encoder.h"

PID pid;	//���pid�㷨����Ҫ������

void pid_Init(void)
{
	pid.Sv=0;
	pid.Pv=0;
	pid.Ek_1=0;
	pid.Kp=0;	
	pid.Ki=0;	
	pid.Kd=0;	
	pid.PwmCycle=5000;	//pwm����
	pid.OUT0 =0 ;
}

u8 flag_pid=1;
void pid_Calc(void)
{
	float DelEk;
	float Pout,Iout,Dout,out;
	
	pid.Ek=pid.Sv-pid.Pv;
	
//	if(pid.Ek> && pid.Ek< )			���ָ���
//		pid.SEk+=pid.Ek;
	
//	if(pid.SEk> )
//		pid.SEk= ;								�����ֱ���
//	else if(pid.SEk< )
//		pid.SEk= ;
	
	DelEk=pid.Ek-pid.Ek_1;
	
	Pout=pid.Ek*pid.Kp;
	Iout=pid.SEk*pid.Ki;
	Dout=DelEk*pid.Kd;
	out=Pout+Iout+Dout;
	
	pid.OUT=limit(out);
	
	if(flag_pid==1)			//ȥ����һ��΢�ָ���
	{
		pid.OUT=0;
		flag_pid=2;
	}
		
	pid.Ek_1=pid.Ek;
}


