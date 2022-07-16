#ifndef __LOBOT_USART_H
#define __LOBOT_USART_H

#include "stdio.h"	
#include "sys.h" 
#include "bool.h"

void uartNVICInit(void);
void uartInit(u32 bound);
void uartWriteBuf(uint8_t *buf, uint8_t len);
void USARTL_IRQHandler(void);
bool isRxCompleted(void);

#endif
