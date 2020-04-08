/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include <string.h>
#include "USART.h"

void UART_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	
// Write a 0xB ( 1011b ) into the configuration and mode bits for PB10 (AFIO)//UART3
  GPIOB->CRH |= GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10_1 | GPIO_CRH_MODE10_0 ;
  GPIOB->CRH &= ~GPIO_CRH_CNF10_0 ;
// Write a 0x4 ( 0100b ) into the configuration and mode bits for PB11 (AFIO)//UART3
	GPIOB->CRH |= 0x4; //floating input 
	
	USART3->CR1 |= USART_CR1_UE;
	USART3->BRR = 0x9c4;
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