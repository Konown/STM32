#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 

//#define KEY2 PBin(14)   	
//#define KEY3 PBin(15)	 
//#define KEY4 PCin(7)	
//#define KEY5 PCin(6)
 

#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����0
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����1
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ����2 
#define KEY5  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
 

#define KEY2_PRES	2		//KEY0  
#define KEY3_PRES	3		//KEY1 
#define KEY4_PRES	4		//WK_UP
#define KEY5_PRES 5

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
