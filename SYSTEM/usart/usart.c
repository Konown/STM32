#include "sys.h"
#include "usart.h"	  
#include "delay.h"
#include "led.h"
#include "key.h"
//C��
#include <stdarg.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
        if(ch =='\n')  
        {  
            USART_SendData(USART1, 0x0D);  
            while (!(USART1->SR & USART_FLAG_TXE)); 
            USART_SendData(USART1, 0x0A);  
            while (!(USART1->SR & USART_FLAG_TXE));  
        }  
        else  
        {  
            USART_SendData(USART1, (unsigned char)ch);  
            while (!(USART1->SR & USART_FLAG_TXE));   
        }  
	return ch;
}
#endif 


 
/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{
 
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				//��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);				//��USART1��ʱ��
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//����Ϊ����ģʽ
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;						//��ʼ��Pin9
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//���ص����Ƶ��
	GPIO_Init(GPIOA, &gpioInitStruct);												//��ʼ��GPIOA
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;				//����Ϊ��������
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;						//��ʼ��Pin10
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//���ص����Ƶ��
	GPIO_Init(GPIOA, &gpioInitStruct);												//��ʼ��GPIOA
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;					//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;				//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;				//8λ����λ
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);					//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;					//usart1�жϺ�
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;					//�ж�ͨ��ʹ��
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;				//��ռ�ж����ȼ�(ֵԽС���ȼ�Խ��)
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;					//���ж����ȼ�(ֵԽС���ȼ�Խ��)
	NVIC_Init(&nvicInitStruct);														//��ʼ��NVIC
 
}
 
/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{
 
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;					//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;				//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;				//8λ����λ
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
 
}
 
 
/*
************************************************************
*	�������ƣ�	Usart3_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PB10	RX-PB11
************************************************************
*/
void Usart3_Init(unsigned int baud)
{
 
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//USART1_TX   GPIOB.10
        gpioInitStruct.GPIO_Pin = GPIO_Pin_10; 				        //PB.10
        gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;			        //�����������
        GPIO_Init(GPIOB, &gpioInitStruct);					//��ʼ��GPIOB.10
   
        //USART1_RX	  GPIOB.11��ʼ��
        gpioInitStruct.GPIO_Pin = GPIO_Pin_11;				        //PB.11
        gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;		        //��������
        GPIO_Init(GPIOB, &gpioInitStruct);					//��ʼ��GPIOB.11 
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;						//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;					//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;					//8λ����λ
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);						//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
 
}
/*
************************************************************
*	�������ƣ�	uart4_Init
*
*	�������ܣ�	����4��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PC10	RX-PC11
************************************************************
*/

void uart4_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure; //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;//���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;//�����ж����ýṹ�����
	//ʹ�� UART4 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴��ڸ���ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��
  
	//UART4_TX   GPIOC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�趨IO�ڵ�����ٶ�Ϊ50MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10
   
  	//UART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10  

 	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baud;//���ڲ�����Ϊ115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽʹ��
	USART_Init(UART4, &USART_InitStructure); //��ʼ������4
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  
	USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���4 
  
 	 //�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(UART4, USART_FLAG_TC);       //�崮��4���ͱ�־
}

/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
 
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
 
	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);						//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}
 
}
 
/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{
 
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsprintf((char *)UsartPrintfBuf, fmt, ap);				//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
 
}
 
char usart1Buf[64];
char usart1Len;
/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	����1�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART1_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//�����ж�
	{
		if(usart1Len >= 64)									//��ֹ���ݹ��࣬�����ڴ����
			usart1Len = 0;
		usart1Buf[usart1Len++] = USART1->DR;
		
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
 
}
 
char usart2Buf[64];
char usart2Len;
/*
************************************************************
*	�������ƣ�	USART2_IRQHandler
*
*	�������ܣ�	����2�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART2_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	//�����ж�
	{
		if(usart2Len >= 64)									//��ֹ���ݹ��࣬�����ڴ����
			usart2Len = 0;
		usart2Buf[usart2Len++] = USART2->DR;
		
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}

char usart3Buf[64];
char usart3Len;
/*
************************************************************
*	�������ƣ�	USART3_IRQHandler
*
*	�������ܣ�	����3�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART3_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//�����ж�
	{
		if(usart3Len >= 64)									//��ֹ���ݹ��࣬�����ڴ����
			usart3Len = 0;
		usart3Buf[usart3Len++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}

/*
************************************************************
*	�������ƣ�	USART4_IRQHandler
*
*	�������ܣ�	����4�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/

void UART4_IRQHandler(void)			   //����4ȫ���жϷ�����
{
	u8 com_data;
  	//�����ж�
	if( USART_GetITStatus(UART4,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//����жϱ�־
		com_data = UART4->DR;
		//Openmv_Receive_Data(com_data);//openmv���ݴ�����
	}
}


