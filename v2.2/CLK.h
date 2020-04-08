#include <stdint.h>
#include "stm32f10x.h"



 //Functions available for public use

// Initialize the Cortex M3 clock using the RCC registers
  void clockInit(void);
// A general purpose countdown timer delay routine
  void delay(uint32_t delay);
