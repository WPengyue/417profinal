/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include "LCD_Displayer.h"
#include "delay.h"

void LCD_INIT(void)
{
	RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN;//Enable Port B & C
  GPIOB->CRL &= 0xff0fff00;
	GPIOB->CRL |= 0x00300033;  //Configure PB5,1,0 to output
  GPIOC->CRL = 0x33333333;	//Configure PC7-0 to output
	delay(90000);
	CMD2LCD(LCD_8B2L);
	delay(30000);
	CMD2LCD(LCD_8B2L);
	delay(30000);
	CMD2LCD(LCD_8B2L);
	delay(30000);	
	CMD2LCD(LCD_8B2L);
	delay(30000);
	CMD2LCD(LCD_DCB);
	delay(30000);
	CMD2LCD(LCD_CLR);
	delay(30000);
	CMD2LCD(LCD_MCR);
	delay(30000);
}

void CMD2LCD(uint8_t data)
{
	GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
	// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
	delay(80000);
}
void DAT2LCD(uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
	// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_DM_DIS; //RS low, E low
	delay(80000);
}

void stringToLCD(char * message)
{
	int i=0;
	uint16_t messageLength = strlen(message);
	for (i=0; i<messageLength; ++i)
	{
		DAT2LCD(*message);
		++message;
	}
}
