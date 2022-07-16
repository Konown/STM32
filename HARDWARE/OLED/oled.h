#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
#define OLED_MODE 0
		    						  
//-----------------OLED端口定义----------------  					   
#define OLED_CS PCout(8)
#define OLED_RST  PBout(12)//在MINISTM32上直接接到了STM32的复位脚！	

#define OLED_SCLK PAout(5)
#define OLED_SDIN PAout(7)
		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	 

void ShowScreen(void);
void Compare_Pwm(void);
void ShowDistance(void);

void OLED_ShowIntegerNumber(u8 x,u8 y,int num,u8 size);

#endif  
	 



