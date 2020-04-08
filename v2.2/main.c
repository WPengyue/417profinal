#include "CLK.h"
#include "UART.h"
#include "LCD.h"
#include "Xbee.h"
#include "stm32f10x.h"
#include <string.h>
#include <stdint.h>

int main(void)
{
	//char s[3] = {'A','T',0x00};
	char r[256] = {' ','R','S','1', '1', 'E',' '};
	char *str ; //10 = "-- a b c-- "
	//char xbee_in[14];      // receive data
	//char *xbee_buff;
	int len;

	clockInit();
	UART_init();
	LCD_init(); 
	XBEE_API_FRAME xbeet;
	
	xbeet.StartDelimiter = XBEE_API_FRAME_STARTDELIMITER_TX;
	len=strlen(str);
	xbeet.wLength = len;
	xbeet.frameData= str;
	
	
	str =r;
	
while(1)
{
	/*------------------------------------------------------------------------
	UART_read_a(xbee_in);
	for(int i = 0; xbee_in[i] != 0x00; i++)
	{
		Data2LCD(r[i]);	
		xbee_buff = &xbee_in[i];
	}
	
		for(int i = 0; xbee_in[i] != 0x00; i++)
	{
		Data2LCD(xbee_in[i]); 
	}
------------------------------------------------------------------------*/	


	
	int i = 0;
		/*------------------------------------------------------------------------

	while(*(xbeet.frameData+i) != 0x00)
	{
		UART_send_a(xbeet.frameData+i);
		UART_read_a(r+i);
		i++;
	}
	
	
	------------------------------------------------------------------------*/
	
		while(*(str+i) != 0x00)
	{
		UART_send_a(str+i);
		i++;
	}
	delay(6000000);
}	
	//UART_send_c(0x00);//sent string teminate char 0x00

	//UART_read_a(r+i);


	
/*------------------------------------------------------------------------
	for(i = 0; r[i] != 0x00; i++)
	{
		Data2LCD(r[i]);
	}
----------------------------------------------------------------------*/
//	String2LCD("123456789abcdefghij123456789a2cdefgh");//28

	return 0;
}