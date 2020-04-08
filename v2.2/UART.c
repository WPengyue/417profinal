#include "UART.h"
#include <string.h>
void UART_init(void)
{
	USART3->CR1 |= USART_CR1_UE;
	USART3->BRR = 0x9C4;
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;
}
void UART_send_s(char *message)//string
{
	uint16_t messageLength = strlen(message);
	for (int i=0; i<messageLength; i++)
	{
		for (i=0; i<messageLength; ++i)
		{
			UART_send_c(*message);
			++message;
		}
	}
}
void UART_send_c(char c)//char
{
	while((USART3->SR & USART_SR_TXE) == 0)
		{
		}
		if ((USART3->SR & USART_SR_TXE) != 0)
				{USART3->DR = c;}
}
void UART_read_c(char c)//char
{
	while((USART3->SR & USART_SR_RXNE) == 0)
	{
	}
	if ((USART3->SR & USART_SR_RXNE) != 0)
			{c = USART3->DR;}
}

void UART_send_a(char *c)//array
{
	while((USART3->SR & USART_SR_TXE) == 0)
		{
		}
		if ((USART3->SR & USART_SR_TXE) != 0)
				{USART3->DR = *c;}
}
void UART_read_a(char *c)//array
{
	while((USART3->SR & USART_SR_RXNE) == 0)
		{
		}
		if ((USART3->SR & USART_SR_RXNE) != 0)
				{*c = USART3->DR;}
}