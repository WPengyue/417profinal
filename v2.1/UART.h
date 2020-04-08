#include <stdint.h>
#include "stm32f10x.h"
void UART_init(void);
void UART_send_s(char *string);
void UART_send_c(char);
void UART_read_c(char);
void UART_send_a(char *c);//array
void UART_read_a(char *c);//array