/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/
#include "main.h"
#include "delay.h"
#include "LCD_Displayer.h"
#include "Temp_ADC.h"
#include "Anemometer.h"
#include "USART.h"

uint32_t freq = 0;

int main ()
{ 
	uint8_t a,b,i,j;
	uint32_t temp; 

	char print_temp[4];
	char print_freq[5];
	char rxne_msg;
	char * txe_msg; 
	clockInit();
	ADC_init();
	LCD_INIT();
	Systick_init();
	USART_init();
	
	while(1)
	{
		//number of the characters of the strings(Temperature/Wind Speed)
		a = 0; 
		i = 0;
		//number of the characters of each line of LCD displayer
		b = 16;
		j = 16;
		temp = ADC_READ(1);
		temp = temp *3300/0xfff;
		print_temp[0] = temp/1000;
		print_temp[1] = (temp - 1000*(temp/1000))/100;
		print_temp[2] = (temp - 100*(temp/100))/10;
		print_temp[3] = temp - 10*(temp/10);
		
		print_freq[0] = freq/10000;
		print_freq[1] = (freq - 10000*(freq/10000))/1000;
		print_freq[2] = (freq - 1000*(freq/1000))/100;
		print_freq[3] = (freq - 100*(freq/100))/10;
		print_freq[4] = freq - 10*(freq/10);
		while(print_freq[a] == 0)
		{
			a++;
		}
		while(print_temp[i] == 0)
		{
			i++;
		}
		CMD2LCD(LCD_LN1);
		stringToLCD("Temp:");
		j -= 5;
		if( i > 3 )
		{
			DAT2LCD('0');
		}
		else{
			while(i<3)
			{
				DAT2LCD(print_temp[i]+0x30);
				i++;
				j-=1;
			}	
		}
		if(print_temp[3])
		{
			DAT2LCD('.');
			DAT2LCD(print_temp[3]+0x30);
			j-=2;
		}
		DAT2LCD(0xDF);
		j-=1;
		while(j!=0)
		{
			DAT2LCD(' ');
			j-=1;
		}
		
		CMD2LCD(LCD_LN2);
		stringToLCD("AirFlow:");
		if( a > 4 )
		{
			DAT2LCD('0');
		}
		else{
			
			while(a<5)
			{
				DAT2LCD(print_freq[a]+0x30);
				a++;
				b-=1;
			}
		}
		stringToLCD("Hz") ;
		b-=2;
		while(b!=0)
		{
			DAT2LCD(' ');
			b-=1;
		}
	}
}
