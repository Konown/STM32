#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define IN1 PBout(1)
#define IN2 PBout(2)

void Motor_Init(void);

void back(void);
void stop(void);
void go(void);

void Stby_Init(void);

void motor(float pwm);

float limit(float pwm);
#endif

