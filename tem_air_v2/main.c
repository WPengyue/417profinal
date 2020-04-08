/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/
#include "main.h"
#include "delay.h"
#include "LCD_Displayer.h"
#include "Temp_ADC.h"
#include "Anemometer.h"
#include "USART.h"
#include <string.h>
#include <stdio.h>


uint32_t freq = 0;

int main ()
{ 
	uint8_t a,b,i,j;
//	uint8_t c;
	uint32_t temp; 
	uint16_t wind_speed; // less than 100 (accuracy: maximum 9.9m/s)
	uint32_t volume_flow_velocity;
	char print_temp[4];
//	char print_freq[5];
//	char print_w_s[3]; //accuracy 0.5-9.9m/s
	char print_flow[5]; //accuracy 0.5-9.9m/s
	char temp_air[15];

	char r[15];
	clockInit();
	ADC_init();
	LCD_INIT();
	Systick_init();
	UART_init();
	

	char *str ; //
	
	str =temp_air;

	while(1)
	{
	char temp_val[9]= "-SR T";//second regi
	char air_val[7]= " A";
		
		//number of the characters of the strings(Temperature/Wind Speed)
		a = 0; 
		i = 0;
		//number of the characters of each line of LCD displayer
		b = 16;
		j = 16;
		
//		c = 0;

		temp = ADC_READ(3);
		temp = temp *3300/0xfff;
		print_temp[0] = temp/1000;
		print_temp[1] = (temp - 1000*(temp/1000))/100;
		print_temp[2] = (temp - 100*(temp/100))/10;
		print_temp[3] = temp - 10*(temp/10);
		for(int t=0;t<4;t++)
		{
			print_temp[t]+=0x30;
		}

//		print_freq[0] = freq/10000;
//		print_freq[1] = (freq - 10000*(freq/10000))/1000;
//		print_freq[2] = (freq - 1000*(freq/1000))/100;
//		print_freq[3] = (freq - 100*(freq/100))/10;
//		print_freq[4] = freq - 10*(freq/10);
		
		wind_speed = 0.978+(0.58*freq)-(0.001*freq*freq);//(actual wind speed value * 10)
//		print_w_s[0] = wind_speed/100;
//		print_w_s[1] = (wind_speed - 100*(wind_speed/100))/10;
//		print_w_s[2] = wind_speed - 10*(wind_speed/10);
		
		volume_flow_velocity = wind_speed*108;//area of air register 0.06*0.008*15/4 = 0.0018 m^2
		// 0.0018*60 = 0.108m^3/min
		// maximum 9.9*0.108=1.0692m^3/min	
		// print 5 digitals for flow velocity (9.9*10)*(0.108*1000)=wind_speed(maximum)*108
		print_flow[0] = volume_flow_velocity/10000;
		print_flow[1] = (volume_flow_velocity - 10000*(volume_flow_velocity/10000))/1000;
		print_flow[2] = (volume_flow_velocity - 1000*(volume_flow_velocity/1000))/100;
		print_flow[3] = (volume_flow_velocity - 100*(volume_flow_velocity/100))/10;
		print_flow[4] = volume_flow_velocity - 10*(volume_flow_velocity/10);
		
		for(int af=0;af<5;af++)
		{
			print_flow[af]+=0x30;
		}		
		
//		while(print_freq[a] == 0)
//		{
//			a++;
//		}
//		c+=1;
		while(print_flow[a] == 0x30)
		{
			a++;
		}
		while(print_temp[i] == 0x30)
		{
			i++;
		}
		CMD2LCD(LCD_LN1);
		stringToLCD("Temp:");
		j -= 5;
		if( i > 3 )
		{
			DAT2LCD('0');
			i-=1;
		}
		else{
			while(i<3)
			{
				DAT2LCD(print_temp[i]);
				i++;
				j-=1;
			}	
		}
		if(print_temp[3])
		{
			DAT2LCD('.');
			DAT2LCD(print_temp[3]);
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
		stringToLCD("F:");
		b-=2;
		if( a > 4 )
		{
			DAT2LCD('0');
			b-=1;
		}
		else{
			DAT2LCD(print_flow[0]);
			a = 1;
			stringToLCD(".");
			b-=2;
			while(a < 5)
			{
				DAT2LCD(print_flow[a]);
				a++;
				b-=1;
			}
		}
		while(b>7)
		{
			DAT2LCD(' ');
			b-=1;
		}
		stringToLCD("m^3/min");
		b-=7;	
/*		
//		stringToLCD("F:") ;
//		b-=2;
//		if( a > 4 )
//		{
//			DAT2LCD('0');
//			b-=1;
//		}
//		else{
//			
//			while(a<5)
//			{
//				DAT2LCD(print_freq[a]+0x30);
//				a++;
//				b-=1;
//			}
//		}
//		
//		stringToLCD("Hz") ;
//		b-=2;
//		while(b>8){
//			stringToLCD(" ") ;
//			b-=1;
//		}
//		stringToLCD("w:") ;
//		b-=2;
//		if( c > 2 )
//		{
//			stringToLCD("0.0") ;
//			b-=1;
//		}
//		else{
//			
//			while(c<3)
//			{
//				if(c==2){
//					stringToLCD(".");
//					b-=1;
//				}
//				DAT2LCD(print_w_s[c]+0x30);
//				c++;
//				b-=1;
//			}
//		}
//		stringToLCD("m/s");
//		b-=3;
//		
//		while(b!=0)
//		{
//			DAT2LCD(' ');
//			b-=1;
//		}
*/

	int arr_p ;
	strcat(temp_val, print_temp);
	strncpy(r, temp_val,9);

	strcat(air_val, print_flow);
	
	 //strlen(r);

	
	//strncpy(r, temp_val,9);
	strncat(r, air_val,8);
	
	//strcat(temp_air, print_flow);
	strncpy(temp_air, r,16);
	//str= air_val;
	
		//while(*(str+arr_p) != 0x00)
	for(arr_p=0;arr_p<16;arr_p++)
	{
		UART_send_a(str+arr_p);
		//arr_p++;
		
		
	}
	

	memset(r, 0, sizeof r);	
	memset(temp_val, 0, sizeof temp_val);	
	memset(air_val, 0, sizeof air_val);	

	delay(6000000);


	}
}
