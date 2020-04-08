/* Author – Jiachen Li 200345058, Jan 2020 */
/*Final Project: Anemometer*/

#include "stm32f10x.h"
#include <stdint.h>
#include <string.h>

#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2

#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

void LCD_INIT(void);
void stringToLCD(char * message);
void CMD2LCD(uint8_t data);
void DAT2LCD(uint8_t data);
