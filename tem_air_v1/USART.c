/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include "USART.h"

void USART_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	GPIOB->CRH &= ~0x0000ff00;
	GPIOB->CRH |= 0x0000BB00;
	USART3->CR1 |= USART_CR1_UE;
	USART3->BRR = 0x9c4;
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;
}
