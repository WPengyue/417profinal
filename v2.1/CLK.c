 #include "stm32f10x.h"
 #include "CLK.h"

// CLOCK AND TIMING FUNCTIONS

/*
* Name:         void clockInit()
* Paramaters:   none
* Description: This function will initialize the device internal
               clock to 24 Mhz
*/
void clockInit(void)
{
    uint32_t temp = 0x00;
    //If you hover over the RCC you can go to the definition and then
    //see it is a structure of all the RCC registers.  Then you can
    //simply assign a value.
    RCC->CFGR = 0x00050002;     //24MHz system clock

    RCC->CR =  0x01010081;      // Turn on PLL, HSE, HSI

    while (temp != 0x02000000)  // Wait for the PLL to stabilize
    {
        temp = RCC->CR & 0x02000000; //Check to see if the PLL lock bit is set
    }

    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_TIM1EN;
		//RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;//reset 
		//RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    // Write a 0xB ( 1011b ) into the configuration and mode bits for PA8 (AFIO)
    GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 ;
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0 ;
		// Write a 0xB ( 1011b ) into the configuration and mode bits for PB10 (AFIO)//UART3
    GPIOB->CRH |= GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10_1 | GPIO_CRH_MODE10_0 ;
    GPIOB->CRH &= ~GPIO_CRH_CNF10_0 ;
		// Write a 0xB ( 1011b ) into the configuration and mode bits for PB11 (AFIO)//UART3
    //GPIOB->CRH |= GPIO_CRH_CNF11_1 | GPIO_CRH_MODE11_1 | GPIO_CRH_MODE11_0 ;
   // GPIOB->CRH &= ~GPIO_CRH_CNF11_0 ;
		GPIOB->CRH |= 0x4; //floating input 
		//Port A pin 0 as input
		GPIOA->CRL |= 0x4;
}

/*
* Name:         void delay()
* Paramaters:   32 bit delay value, ( a value of 6000
                gives approximately 1 mS of delay)
* Description:  This function creates a delay
*/
void delay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}

