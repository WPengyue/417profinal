/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"

void Systick_init(void);
uint16_t ADC_READ(uint8_t Channel);
