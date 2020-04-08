/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include "Anemometer.h"

uint8_t cur_pul_state = 0;
uint8_t ten_periods = 1;
uint32_t unit_of_period = 1; // 10us(100KHz)
uint8_t start_counting = 0;
uint32_t half_second;
extern uint32_t freq;

void Systick_init(void)
{
		GPIOA->CRL &= 0xfff0ffff;
		GPIOA->CRL |= 0x00040000;// PA 4 Detects a pulse sigal from magnet sensor
		SysTick->CTRL = 0x00;
		SysTick->VAL = 0x00;
		//24MHz=42ns
		SysTick->LOAD = 240;// 100KHz
		SysTick->CTRL = 0x07;
}
void SysTick_Handler(void)
{
	if(half_second > 49999){
		unit_of_period = 1;
		start_counting = 0;
		ten_periods = 0;
		freq = 0;
		half_second = 0 ;
	}
	uint8_t state = ((GPIOA->IDR & GPIO_IDR_IDR4) >> 4 ) & 0x1;
	if((cur_pul_state != state) && state == 0){ // Detect rising edge signal; periduecy < 10KHz; periduency > 5Hz)
		start_counting = 1;
		if((unit_of_period > 99 && ten_periods > 9)){
			freq = 1000000/unit_of_period;// perid(Hz) = 1/10*(unit_of_period * 10 us)
			unit_of_period = 0;
			ten_periods = 0;
		}
		half_second = 0;
		ten_periods += 1;
	}
	if(start_counting){
		unit_of_period += 1;
	}
	half_second += 1;
	cur_pul_state = state;
}
