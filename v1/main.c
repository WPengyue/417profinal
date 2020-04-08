#include "CLK.h"
#include "UART.h"
#include "LCD.h"
#include "Xbee.h"
#include "stm32f10x.h"
#include <string.h>
int main(void)
{
	//char s[3] = {'A','T',0x00};
	char r[40];
	char *str = "hello xbee"; //12
	char xbee_in[14];      // receive data
	char *xbee_buff;
	clockInit();
	UART_init();
	//LCD_init(); 


	int i = 0;
	while(*(str+i) != 0x00)
	{
		UART_send_a(str+i);
		//UART_read_a(r+i);
		i++;
	}
	UART_send_c(0x00);//sent string teminate char 0x00
	//UART_read_a(r+i);
//	for(i = 0; r[i] != 0x00; i++)
//	{
//		Data2LCD(r[i]);
//	}
//	
//	String2LCD("123456789abcdefghij123456789a2cdefgh");//28

	return 0;
}