/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include "Temp_ADC.h"

void ADC_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= 0xffffff0f;
	ADC1->CR2 = ADC_CR2_ADON;
}
uint16_t ADC_READ(uint8_t Channel)
{
	uint16_t temp;
	ADC1->SQR3 = Channel;
	ADC1->CR2 = ADC_CR2_ADON;
	while ((ADC1->SR & ADC_SR_EOC)!= ADC_SR_EOC)
	{ }
	temp = ADC1->DR;
	for(uint8_t n = 10; n > 0; n--){
		ADC1->CR2 = ADC_CR2_ADON;
		while ((ADC1->SR & ADC_SR_EOC)!= ADC_SR_EOC)
		{ }
		temp = (temp > ADC1->DR)? temp : ADC1->DR;
	}
	return (temp);
}
