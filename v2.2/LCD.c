#include "CLK.h"
#include "LCD.h"
#include "stm32f10x.h"
#include <string.h>

// SWITCH AND LCD I/O FUNCTIONS

void lcd_IO_init (void)
{
    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN
        | RCC_APB2ENR_IOPAEN ;
		//set RS, R/~W and E as output push and pull 50MHz
		GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5;
		GPIOB->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;
		//set Port C pin 0 ~ 7 as output push and pull 50MHz
		GPIOC->CRL = 0x33333333;
}

void LCD_init(void)
{
	lcd_IO_init();
	delay(300000);//50ms
	Cmd2LCD(0x38);
	delay(25200);//4.2ms
	Cmd2LCD(0x38);
	delay(1200);//200us
	Cmd2LCD(0x38);
	delay(30000);
	Cmd2LCD(0x0F);
	delay(30000);//5ms
	Cmd2LCD(0x01);
	delay(1200000);//200ms
	Cmd2LCD(0x06);
	delay(30000);//5ms
}

void Cmd2LCD(uint8_t data)
{
GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
// GPIOC->ODR = data; //BAD: may affect upper bits on port C
GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
delay(8000);
GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
delay(80000);
}
void Data2LCD(uint8_t data)
{
	if (data == '\n'){Cmd2LCD(0xC0);}
	GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
	// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_DM_DIS; //RS low, E low
	delay(80000);
}

void String2LCD(char * message)	//each line 14
{
	int i, toNewLine = 40;
	uint16_t messageLength = strlen(message);
	for (i=0; i<messageLength; i++)
	{
		if( messageLength > 16)
		{
			if(message[i] == ' ')
			{
				if (i <= 16)
				{
					toNewLine = i;
				}
			}
		}
		else
		{
			toNewLine = 40;
		}
	}
	for (i=0; i<messageLength; ++i)
	{
		if (i == (toNewLine + 1)){Cmd2LCD(0xC0);}
		Data2LCD(*message);
		++message;
	}
}

uint16_t Hex2Asc(uint8_t Hex)
{
	uint16_t Asc;
	if (Hex < 0xA)
	{
		Asc = Hex + 0x30;
	}
	else
	{
		Asc = Hex + 0x37;
	}
	return Asc;
}
uint16_t Hex2Dec(uint16_t Hex)
{
	uint16_t Dec = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			Dec |= (Hex % 10);
		}
		else
		{
			Hex = Hex /10;
			Dec |= (Hex % 10) << (i * 4);
		}
	}
	return Dec;
}