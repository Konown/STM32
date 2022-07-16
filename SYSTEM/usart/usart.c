#include "sys.h"
#include "usart.h"	  
#include "delay.h"
#include "led.h"
#include "key.h"
//C库
#include <stdarg.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
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
*	函数名称：	Usart1_Init
*
*	函数功能：	串口1初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{
 
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				//打开GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);				//打开USART1的时钟
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//设置为复用模式
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;						//初始化Pin9
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//承载的最大频率
	GPIO_Init(GPIOA, &gpioInitStruct);												//初始化GPIOA
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;				//设置为浮空输入
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;						//初始化Pin10
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;					//承载的最大频率
	GPIO_Init(GPIOA, &gpioInitStruct);												//初始化GPIOA
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;					//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;				//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;				//8位数据位
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//使能串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);					//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;					//usart1中断号
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;					//中断通道使能
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;				//抢占中断优先级(值越小优先级越高)
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;					//子中断优先级(值越小优先级越高)
	NVIC_Init(&nvicInitStruct);														//初始化NVIC
 
}
 
/*
************************************************************
*	函数名称：	Usart2_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA2		RX-PA3
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
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;					//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;				//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;				//8位数据位
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//使能串口
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
 
}
 
 
/*
************************************************************
*	函数名称：	Usart3_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PB10	RX-PB11
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
        gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;			        //复用推挽输出
        GPIO_Init(GPIOB, &gpioInitStruct);					//初始化GPIOB.10
   
        //USART1_RX	  GPIOB.11初始化
        gpioInitStruct.GPIO_Pin = GPIO_Pin_11;				        //PB.11
        gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;		        //浮空输入
        GPIO_Init(GPIOB, &gpioInitStruct);					//初始化GPIOB.11 
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;						//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;					//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;					//8位数据位
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														//使能串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);						//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
 
}
/*
************************************************************
*	函数名称：	uart4_Init
*
*	函数功能：	串口4初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PC10	RX-PC11
************************************************************
*/

void uart4_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure; //串口端口配置结构体变量
	USART_InitTypeDef USART_InitStructure;//串口参数配置结构体变量
	NVIC_InitTypeDef NVIC_InitStructure;//串口中断配置结构体变量
	//使能 UART4 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//打开串口复用时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //打开PC端口时钟
  
	//UART4_TX   GPIOC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设定IO口的输出速度为50MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.10
   
  	//UART4_RX	  GPIOC.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.10  

 	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
  	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = baud;//串口波特率为115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式使能
	USART_Init(UART4, &USART_InitStructure); //初始化串口4
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
  
	USART_Cmd(UART4, ENABLE);                    //使能串口4 
  
 	 //如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(UART4, USART_FLAG_TC);       //清串口4发送标志
}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
 
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
 
	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);						//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}
 
}
 
/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{
 
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsprintf((char *)UsartPrintfBuf, fmt, ap);				//格式化
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
*	函数名称：	USART1_IRQHandler
*
*	函数功能：	串口1收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART1_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//接收中断
	{
		if(usart1Len >= 64)									//防止数据过多，导致内存溢出
			usart1Len = 0;
		usart1Buf[usart1Len++] = USART1->DR;
		
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
 
}
 
char usart2Buf[64];
char usart2Len;
/*
************************************************************
*	函数名称：	USART2_IRQHandler
*
*	函数功能：	串口2收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART2_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	//接收中断
	{
		if(usart2Len >= 64)									//防止数据过多，导致内存溢出
			usart2Len = 0;
		usart2Buf[usart2Len++] = USART2->DR;
		
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}

char usart3Buf[64];
char usart3Len;
/*
************************************************************
*	函数名称：	USART3_IRQHandler
*
*	函数功能：	串口3收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART3_IRQHandler(void)
{
 
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//接收中断
	{
		if(usart3Len >= 64)									//防止数据过多，导致内存溢出
			usart3Len = 0;
		usart3Buf[usart3Len++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}

/*
************************************************************
*	函数名称：	USART4_IRQHandler
*
*	函数功能：	串口4收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/

void UART4_IRQHandler(void)			   //串口4全局中断服务函数
{
	u8 com_data;
  	//接收中断
	if( USART_GetITStatus(UART4,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//清除中断标志
		com_data = UART4->DR;
		//Openmv_Receive_Data(com_data);//openmv数据处理函数
	}
}


